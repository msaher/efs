#include <termios.h>
#include <unistd.h>
#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>
#include <sys/ioctl.h> // for finding window size
#include "editor.h"
#include <algorithm>

using std::cout;
using std::stringstream;
using std::string;
using std::size_t;
using std::min;

struct termios origattr;

static void reset_terminal()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &origattr) == -1)
        throw std::runtime_error("can't reset terminal\n");
}

void set_raw()
{
    if (tcgetattr(STDIN_FILENO, &origattr) == -1)
        throw std::runtime_error("can't set terminal attributes\n");

    atexit(reset_terminal); // rest terminal when quitting

    struct termios raw = origattr;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cflag |= (CS8);
    raw.c_oflag &= ~(OPOST);
    /* raw.c_cc[VMIN] = 0; */
    /* raw.c_cc[VTIME] = 1; */

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void window_size(unsigned int& screen_rows, unsigned int& screen_cols)
{

    struct winsize ws;
    if (ioctl(STDERR_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
        throw std::runtime_error("Can't find window size");

    screen_rows = ws.ws_row;
    screen_cols = ws.ws_col;
}

// draw a line that does not exceed a limit
void draw_line(stringstream& s, string&& line, size_t lim)
{
    size_t len = min(line.length(), lim);
    s.write(line.c_str(), len);
}

void draw_rows(stringstream& s, Editor& ed)
{
    size_t numrows = ed.buf.size(); // rows containing text
    size_t srows = ed.screen_rows;
    size_t scols = ed.screen_cols;

    for (size_t i = 0; i < srows; i++) {
        if (i < numrows)
            draw_line(s, ed.buf[i]->to_string(), scols);
        else
            s << "~";

        if (i != srows-1)
            s << "\r\n";
    }
}

void clear_screen()
{
    cout << "\x1b[2J"; // clear the screen
}

void refresh_screen(Editor& ed)
{
    stringstream s;
    s << "\x1b[?25l"; // hide cursor
    s << "\x1b[2J"; // clear the screen
    s << "\x1b[H"; // go to row 1 column 1

    window_size(ed.screen_rows, ed.screen_cols);
    draw_rows(s, ed);

    s << "\x1b[" << ed.cx+1 << ";" << ed.cy+1 << "H"; 
    s << "\x1b[?25h"; // unhide cursor

    cout << s.str();
}
