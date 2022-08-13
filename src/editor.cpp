#include "editor.h"
#include <fstream>
#include <string>
#include <iostream>
#include "keys.h"
#include <algorithm>

using std::ifstream;
using std::string;
using std::min;

void load(Editor& ed, ifstream& file)
{
    std::string line;
    GapBuff<char>* gb;
    while (getline(file, line)) {
        gb = new GapBuff<char>(line);
        ed.buf.push_back(gb);
    }
}

inline size_t numrows(const Editor& ed)
{
    return ed.buf.size();
}

inline GapBuff<char>* currow(const Editor& ed)
{
    if (ed.buf.size() == 0)
        return NULL;
    else
        return ed.buf[ed.cy];
}

void move_cursor(Editor& ed, int dir)
{
    GapBuff<char>* row = currow(ed);

    switch (dir) {
        case LEFT:
            if (ed.cx != 0)
                ed.cx--;
            break;
        case RIGHT:
            if (row != NULL && ed.cx < ed.buf[ed.cy]->size())
                ed.cx++;
            break;
        case UP:
            if (ed.cy > 0)
                ed.cy--;
            break;
        case DOWN:
            if (ed.cy < numrows(ed))
                ed.cy++;
            break;
        default:
            // TODO:
            break;
    }

	row = currow(ed);
	if (row != NULL)
	  ed.cx = min<size_t>(ed.cx, row->size());
	else
	  ed.cx = 0;
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
