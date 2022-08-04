#include "editor.h"
#include <fstream>
#include <string>
#include <iostream>
#include "keys.h"

using std::ifstream;
using std::string;

void load(Editor& ed, ifstream& file)
{
    std::string line;
    GapBuff<char>* gb;
    while (getline(file, line)) {
        gb = new GapBuff<char>(line);
        ed.buf.push_back(gb);
    }
}

void move_cursor(Editor& ed, int dir)
{
    switch (dir) {
        case LEFT:
            if (ed.cx > 0)
                ed.cx--;
            break;
        case RIGHT:
            if (ed.cx < ed.buf[ed.cy]->size())
                ed.cx++;
            break;
        case UP:
            if (ed.cy > 0)
                ed.cy--;
            break;
        case DOWN:
            if (ed.cy < ed.buf.size())
                ed.cy++;
            break;
        default:
            // TODO:
            break;
    }
}

void scroll_maybe(Editor& ed)
{
    if (ed.cy < ed.rowoff)
        ed.rowoff = ed.cy;
    else if (ed.cy >= ed.rowoff + ed.screen_rows)
        ed.rowoff = ed.cy - ed.screen_rows + 1;
}

void load(Editor& ed, string& filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
        throw std::runtime_error("Can't open file");

    load(ed, file);
    file.close();
}

Editor::~Editor()
{
    for (auto& gb : buf)
        delete gb;
}
