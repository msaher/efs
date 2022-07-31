#include "editor.h"
#include <fstream>
#include <string>
#include <iostream>

using std::ifstream;
using std::string;

void load(Editor& ed, ifstream& file)
{
    std::string line;
    GapBuff<char>* gb;
    while (getline(file, line)) {
        gb = new GapBuff<char>(line);
        ed.buf.push_back(gb);
    }
}

void load(Editor& ed, string& filename)
{
    ifstream file;
    file.open(filename);
    if (!file.is_open())
        throw std::runtime_error("Can't open file");

    load(ed, file);
    file.close();
}

Editor::~Editor()
{
    for (auto& gb : buf)
        delete gb;
}
