#include <iostream>
#include <string>
#include "terminal.h"

using std::cout;
using std::cin;
using std::string;

int main()
{
    set_raw();
    refresh_screen();

    char c;
    while (true) {
        cin >> c;
        cout << c << "\r\n";
        if (c == 'q')
            break;
    }

    return 0;
}
