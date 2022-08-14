#ifndef EDITOR_H
#define EDITOR_H
#include "gapbuff.h"
#include <vector>
#include <string>
#include <fstream>

enum Mode {
    NORMAL,
    INSERT,
};

struct Editor {
    unsigned int cx; // actual x coordinate
    unsigned int cy; // y coordinate
    unsigned int screen_cols; // window size
    unsigned int screen_rows;
    std::string filename;
    std::vector<GapBuff<char>*> buf;
    unsigned int currow;
    unsigned int rowoff;
    unsigned int coloff;
    Mode mode;
    ~Editor();
};

void load(Editor&, std::ifstream&);
void load(Editor&, std::string&);
void move_cursor(Editor&, int);
void scroll_maybe(Editor& ed);
inline size_t numrows(const Editor&);
inline GapBuff<char>* currow(const Editor&);
GapBuff<char>* split(GapBuff<char>);
#endif
