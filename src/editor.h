#ifndef EDITOR_H
#define EDITOR_H
#include "gapbuff.h"
#include <vector>

using std::vector;

struct Editor {
    unsigned int cx; // actual x coordinate
    unsigned int cy; // y coordinate
    unsigned int screen_cols; // window size
    unsigned int screen_rows;
    vector<GapBuff<char>> buf;
};
#endif
