#include <iostream>
#include <string>
#include "terminal.h"

using std::cout;
using std::cin;
using std::string;

int main()
{
    set_raw();
    /* cout << "\x1b[?25l"; */

    char c;
    while (c != 'q') {
        cin >> c;
        cout << c << "\r\n";
    }

    return 0;
}
