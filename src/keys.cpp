#include <iostream>
#include <stdlib.h>
#include "keys.h"
#include "editor.h"
#include <unistd.h>
#include <errno.h>

void normal_process_key(int, Editor&);
void insert_process_key(int, Editor&);

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
    switch (ed.mode) {
        case NORMAL:
            normal_process_key(c, ed);
            break;
        case INSERT:
            insert_process_key(c, ed);
            break;
    }
}

void normal_process_key(int c, Editor& ed)
{
    switch (c) {
        case 'q':
            exit(0);
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

void insert_process_key(int c, Editor& ed)
{
    switch(c) {
        case LEFT:
        case RIGHT:
        case UP:
        case DOWN:
            move_cursor(ed, c);
            return;
        case '\x1b':
            ed.mode = NORMAL;
            return;
    }

    if (ed.buf.empty())
        ed.buf.push_back(new GapBuff<char>());

    GapBuff<char>* currow = ed.buf[ed.cy];
    currow->set_pos(ed.cx);
    currow->insert(static_cast<char>(c));
    ed.cx++;
}
