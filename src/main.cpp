#include <iostream>
#include <string>
#include "terminal.h"
#include "gapbuff.h"
#include "editor.h"

using std::cout;
using std::cin;
using std::string;

Editor ED {}; // global editor state

int main()
{
    set_raw();

    char c;
    while (true) {
        refresh_screen(ED);
        cin >> c;
        if (c == 'q')
            break;
    }

    return 0;
}
