#ifndef KEYS_H
#define KEYS_H
#include <limits.h>

enum Keys {
    BACKSPACE = 127,
    LEFT = UCHAR_MAX+1, // outside of char range
    RIGHT,
    DOWN,
    UP,
    HOME,
    END,
};

int read_key(void);
void process_key(int c);


#endif
