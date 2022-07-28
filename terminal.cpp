#include <termios.h>
#include <unistd.h>
#include <stdexcept>
	

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
