#include "gapbuff.h"
#include "terminal.h"

struct Ed {
    unsigned int cx; // x coordinate
    unsigned int cy; // y coordinate
    unsigned int screen_cols; // window size
    unsigned int screen_rows;
    GapBuff<char> buf;
};
