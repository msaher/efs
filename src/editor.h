#ifndef EDITOR_H
#define EDITOR_H
#include "gapbuff.h"
#include <vector>
#include <string>
#include <fstream>

struct Editor {
    unsigned int cx; // actual x coordinate
    unsigned int cy; // y coordinate
    unsigned int screen_cols; // window size
    unsigned int screen_rows;
    std::string filename;
    std::vector<GapBuff<char>*> buf;
    ~Editor();
};

void load(Editor&, std::ifstream&);
void load(Editor&, std::string&);

#endif
