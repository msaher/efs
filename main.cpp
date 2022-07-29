#include <iostream>
#include <string>
#include "terminal.h"

using std::cout;
using std::cin;
using std::string;

void refresh_screen()
{
    string s;

    // hide cursor
    /* s.append("\x1b[?25l"); */
    s.append("\x1b[H");
    cout << s;
}

int main()
{
    set_raw();
    /* cout << "\x1b[?25l"; */
    refresh_screen();

    char c;
    while (c != 'q') {
        cin >> c;
        cout << c << "\r\n";
    }

    return 0;
}
