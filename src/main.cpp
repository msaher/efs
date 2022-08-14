#include <iostream>
#include <string>
#include "terminal.h"
#include "gapbuff.h"
#include "editor.h"
#include <fstream>
#include "keys.h"

using std::string;
using std::ifstream;

Editor ED {}; // global editor state

int main(int, char* argv[])
{
    set_raw();
    atexit(clear_screen);
    window_size(ED.screen_rows, ED.screen_cols);
    ED.screen_rows -= 2; // room for bar and messages

    if (*++argv != nullptr) {
        ED.filename = *argv;
        load(ED, ED.filename);
    }

    int c;
    while (true) {
        refresh_screen(ED);
        c = read_key();
        process_key(c, ED);
    }

    return 0;
}
