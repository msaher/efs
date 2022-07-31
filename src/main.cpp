#include <iostream>
#include <string>
#include "terminal.h"
#include "gapbuff.h"
#include "editor.h"
#include <fstream>

using std::cout;
using std::cin;
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

    char c;
    while (true) {
        refresh_screen(ED);
        cin >> c;
        if (c == 'q')
            break;
    }

    return 0;
}
