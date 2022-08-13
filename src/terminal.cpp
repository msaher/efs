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
void draw_line(stringstream& s, string&& line, size_t start, size_t lim)
{
    if (start > line.length())
        return;

    // TODO: is this efficient?
    const string subline = line.substr(start);
    s.write(subline.c_str(), min(subline.length(), lim));
}

void draw_rows(stringstream& s, Editor& ed)
{
    size_t row;
    size_t numrows = ed.buf.size();
    for (size_t i = 0; i < ed.screen_rows; i++) {
        row = i + ed.rowoff;
        if (row < numrows)
            draw_line(s, ed.buf[row]->to_string(), ed.coloff, ed.screen_cols);
        else
            s << "~";

        if (i != ed.screen_rows-1)
            s << "\r\n";
    }

}

void clear_screen()
{
    cout << "\x1b[2J"; // clear the screen
}

void refresh_screen(Editor& ed)
{
    window_size(ed.screen_rows, ed.screen_cols);
    scroll_maybe(ed);

    stringstream s;
    s << "\x1b[?25l"; // hide cursor
    s << "\x1b[2J"; // clear the screen
    s << "\x1b[H"; // go to row 1 column 1

    draw_rows(s, ed);

    s << "\x1b[" << (ed.cy-ed.rowoff)+1 << ";" << (ed.cx-ed.coloff)+1 << "H";
    s << "\x1b[?25h"; // unhide cursor

    cout << s.str();
}
