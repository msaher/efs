#ifndef EDITOR_H
#define EDITOR_H
#include "gapbuff.h"

struct Editor {
    unsigned int cx; // x coordinate
    unsigned int cy; // y coordinate
    unsigned int screen_cols; // window size
    unsigned int screen_rows;
    GapBuff<char> buf; // 2d gap buffer
};

#endif
