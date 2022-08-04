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
