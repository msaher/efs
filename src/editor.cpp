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

GapBuff<char>* get_currow(Editor& ed)
{
    if (ed.cy < ed.buf.size()) // size=0 or ed.cy > size
        return nullptr;
    return ed.buf[ed.cy];
}

void move_cursor(Editor& ed, int dir)
{
    GapBuff<char>* row = get_currow(ed);

    switch (dir) {
        case LEFT:
            if (ed.cx != 0)
                ed.cx--;
            break;
        case RIGHT:
            if (row != NULL && ed.cx < row->size())
                ed.cx++;
            break;
        case UP:
            if (ed.cy > 0)
                ed.cy--;
            break;
        case DOWN:
            if (ed.cy != ed.buf.size()-1)
                ed.cy++;
            break;
        default:
            // TODO:
            break;
    }
	row = get_currow(ed);
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

    if (ed.cx < ed.coloff)
      ed.coloff = ed.cx;
    else if(ed.cx >= ed.coloff + ed.screen_cols)
      ed.coloff = ed.cx - ed.screen_cols + 1;

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

GapBuff<char>* split(GapBuff<char> buf)
{
    string rightstr = buf.right_string();
    buf.right_remove();
    return new GapBuff<char>(rightstr);
}

Editor::~Editor()
{
    for (auto& gb : buf)
        delete gb;
}
