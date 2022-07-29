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
    refresh_screen(ED);

    char c;
    while (true) {
        cin >> c;
        cout << c << "\r\n";
        if (c == 'q')
            break;
    }

    return 0;
}
