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
    if (ed.buf.size() == 0) // size=0 or ed.cy > size
        return nullptr;
    return ed.buf[ed.cy];
}

void move_cursor(Editor& ed, int dir)
{
    GapBuff<char>* currow = get_currow(ed);
    if (currow == nullptr)
        return;

    switch (dir) {
        case LEFT:
            if (ed.cx != 0)
                ed.cx--;
            break;
        case RIGHT:
            if (currow != nullptr && ed.cx < currow->size())
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

	currow = get_currow(ed);
	if (currow == nullptr) {
        ed.cx = 0;
        return;
    }

    ed.cx = min<size_t>(ed.cx, currow->size());
    currow->set_pos(ed.cx);
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

void adjust_gap(Editor& ed)
{
    GapBuff<char>* currow = get_currow(ed);
    if (currow != nullptr)
        currow->set_pos(ed.cx);
}

// TODO: use me
void delete_row(Editor& ed, size_t index)
{
    ed.buf.erase(ed.buf.begin()+index);
    if (!ed.buf.empty())
        move_cursor(ed, DOWN);
}

void back_space(Editor& ed)
{
    GapBuff<char>* currow = get_currow(ed);
    if (currow == nullptr)
        return;

    if (ed.cx != 0) {
        currow->remove();
        ed.cx--;
    }
    else if (ed.cy != 0) { // join with previous line

        string rstr = currow->right_string(); // for appending
        ed.buf.erase(ed.buf.begin()+ed.cy);

        size_t len = ed.buf[--ed.cy]->size(); // for positioning cursor

        ed.buf[ed.cy]->append(rstr);
        ed.buf[ed.cy]->set_pos(ed.cx = len);
    }
}

void insert_newline(Editor& ed)
{
    GapBuff<char>* currow = get_currow(ed);
    if (currow == nullptr) {
        currow = new GapBuff<char>();
        ed.buf.push_back(currow);
    }
    string rstr = currow->right_string();
    currow->right_remove();

    GapBuff<char>* newrow = new GapBuff<char>(rstr);
    ed.buf.insert(ed.buf.begin()+ed.cy+1, newrow);

    newrow->set_pos(ed.cx = 0);
    move_cursor(ed, DOWN);
}

Editor::~Editor()
{
    for (auto& gb : buf)
        delete gb;
}
