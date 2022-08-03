#include <iostream>
#include <stdlib.h>
#include "keys.h"
#include "editor.h"

using std::cin;

int handle_escape()
{
    char seq[3];
    for (int i = 0; i < 2; i++) // read three times
        cin >> seq[i];

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
    cin >> c;

    if (c == '\x1b')
        return handle_escape();

    return c;
}

void process_key(int c, Editor& ed)
{
    switch (c) {
        case 'q':
            exit(0);
            break;
        case LEFT:
        case RIGHT:
        case DOWN:
        case UP:
            move_cursor(ed, c);
    }
}
