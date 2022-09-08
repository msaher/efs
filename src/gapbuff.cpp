#include <array>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include "gapbuff.h"
#include <iostream>
#include <string>
#include <string.h> // for memcpy

using std::ostream;
using std::size_t;
using std::string;

GapBuff::GapBuff(size_t cap)
{
    capacity = cap;
    array = (char*) malloc(cap*sizeof(char));
    left = 0;
    right = cap;
    rlen = 0;
}

GapBuff::GapBuff(string str)
{
    // _____this is a string
    size_t strlen = str.length();
    size_t gaplen = DEFAULT_GAP_LEN;
    capacity = strlen + gaplen;
    rlen = strlen;
    right = gaplen;
    left = 0;
    array = (char*) malloc(capacity+gaplen);
    memcpy(array+gaplen, str.c_str(), rlen);
}


bool GapBuff::move_left()
{
    if (left == 0)
        return false;

    array[--right] = array[--left];
    rlen++;

    return true;
}

bool GapBuff::move_right()
{
    if (rlen == 0)
        return false;

    array[left++] = array[right++];
    rlen--;

    return true;
}

void GapBuff::insert(char c)
{
    array[left++] = c;

    if (right == left)
        grow();
}

void GapBuff::grow()
{
    // double the array capacity everytime we grow()
    // If we're doubling the capacity, the new gap
    // length is going to be equal to capacity
    const size_t glen = capacity;
    capacity *= 2;
    array = (char*) realloc(array, capacity*sizeof(char));
    if (array == nullptr)
        throw std::bad_alloc();

    for (size_t i = right; i < right + rlen; i++)
        array[i+glen] = array[i];

    right += glen;
}

bool GapBuff::remove()
{
    if(left == 0)
        return false;
    left--;
    return true;
}

void GapBuff::set_pos(size_t pos)
{
    if (pos == left) // no need to move
        return;

    bool (GapBuff::*move)();
    if (left < pos)
        move = &GapBuff::move_right;
    else
        move = &GapBuff::move_left;

    while (pos != left)
        (this->*move)();
}

GapBuff::~GapBuff()
{
    free(array);
}

string GapBuff::gap_string() // for testing
{
    string s {};
    for (size_t i = 0; i < left; i++)
        s += (array[i]);

    for (size_t i = left; i < right; i++)
        s += ("_");

    for (size_t i = right; i < right + rlen; i++)
        s += array[i];

    return s;
}

string GapBuff::left_string()
{
    string s {};
    for (size_t i = 0; i < left; i++)
        s += (array[i]);
    return s;
}

string GapBuff::right_string()
{
    string s {};
    for (size_t i = right; i < right + rlen; i++)
        s += array[i];
    return s;
}

void GapBuff::goto_end()
{
    while (rlen != 0)
        move_right();
}

void GapBuff::append(string str)
{
    goto_end(); // position the gap at the end
    for (auto c : str)
        insert(c);
}

void GapBuff::right_remove()
{
    right = capacity;
    rlen = 0;
}

string GapBuff::to_string()
{
    return left_string() + right_string();
}

size_t GapBuff::size()
{
    return left+rlen;
}

bool GapBuff::empty()
{
    return this->size() == 0;
}

