#include <iostream>
#include <string>
#include "terminal.h"
#include "gapbuff.h"
#include "editor.h"
#include <fstream>
#include "keys.h"
#include <iostream>
#include <unistd.h>

using std::string;
using std::cerr;
using std::ifstream;

Editor ED {}; // global editor state

void handle_args(int argc, char* argv[])
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " filename" << "\n";
        exit(1);
    }

    if (access(argv[1], R_OK) != 0) {
        cerr << "Can't read file " << argv[1] << "\n";
        exit(1);
    }
    else {
        ED.filename = argv[1];
        load(ED, ED.filename);
    }
}

int main(int argc, char* argv[])
{
    handle_args(argc, argv);

    set_raw();
    atexit(cleanup_term);

    window_size(ED.screen_rows, ED.screen_cols);
    ED.screen_rows -= 2; // room for bar and messages
    ED.mode = NORMAL;

    int c;
    while (true) {
        refresh_screen(ED);
        c = read_key();
        process_key(c, ED);
    }

    return 0;
}
