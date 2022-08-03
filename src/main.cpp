#include <iostream>
#include <string>
#include "terminal.h"
#include "gapbuff.h"
#include "editor.h"
#include <fstream>
#include "keys.h"

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

    int c;
    while (true) {
        refresh_screen(ED);
        c = read_key();
        process_key(c, ED);

        /* cout << static_cast<char>(c) << " (" << c << ")\r\n"; */
        /* if (c == 'q') */
        /*     break; */
    }

    return 0;
}
