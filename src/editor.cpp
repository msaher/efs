#include "gapbuff.h"
#include "terminal.h"
#include <vector>

using std::vector;

struct Ed {
    unsigned int cx; // x coordinate
    unsigned int cy; // y coordinate
    unsigned int screen_cols; // window size
    unsigned int screen_rows;
    vector<GapBuff<char>> buf;
};
