#include <iostream>
#include <stdlib.h>
#include "keys.h"
#include "editor.h"
#include <unistd.h>
#include <errno.h>

void normal_process_key(int, Editor&);

int handle_escape()
{
    char seq[3];
    for (int i = 0; i < 2; i++) // read three times
        if (read(STDIN_FILENO, seq+i, 1) != 1)
            return '\x1b';

    if (seq[0] == '[')
        switch (seq[1]) {
            case 'A': return UP;
            case 'B': return DOWN;
            case 'C': return RIGHT;
            case 'D': return LEFT;
            case 'H': return HOME;
            case 'F': return END;
        }

    return '\x1b';
}

int read_key()
{
    char c;
    int n;
    while ((n = read(STDIN_FILENO, &c, 1)) != 1)
        if (n == -1 && errno == EAGAIN)
            throw std::runtime_error("Can't read");

    if (c == '\x1b')
        return handle_escape();

    return c;
}

void process_key(int c, Editor& ed)
{
    switch (c) {
        case '\x1b':
            ed.mode = NORMAL;
            break;
        case 'i':
            ed.mode = INSERT;
            break;
        case LEFT:
        case RIGHT:
        case DOWN:
        case UP:
            move_cursor(ed, c);
            break;
        default:
            if (ed.mode == NORMAL)
                normal_process_key(c, ed);
    }
}

void normal_process_key(int c, Editor& ed)
{
    switch (c) {
        case 'q':
            exit(0);
            break;
        case 'h':
            move_cursor(ed, LEFT);
            break;
        case 'j':
            move_cursor(ed, DOWN);
            break;
        case 'k':
            move_cursor(ed, UP);
            break;
        case 'l':
            move_cursor(ed, RIGHT);
            break;
    }
}

void insert_process(int c, Editor& ed)
{
}

