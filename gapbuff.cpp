#include <array>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include "gapbuff.h"
#include <iostream>

using std::ostream;

GapBuff::GapBuff()
{
    capacity = DEFAULT_GAP_LEN;
    arr = (char*) malloc(capacity);
    l = 0;
    r = capacity;
    rlen = 0;
}

bool GapBuff::left()
{
    if (l <= 1) // 1 because we don't want a___ to be moved
        return false;

    arr[--r] = arr[--l];
    rlen++;

    return true;
}

bool GapBuff::right()
{
    if (r == capacity)
        return false;

    arr[l++] = arr[r++];
    rlen--;

    return true;
}

void GapBuff::insert(char c)
{
    arr[l++] = c;

    if (r == l)
        grow();

    /* std::cout << *this; */
}

void GapBuff::grow()
{
    const int glen = DEFAULT_GAP_LEN;
    capacity += glen;
    arr = (char*) realloc(arr, capacity*sizeof(char));
    if (arr == nullptr)
        throw std::bad_alloc(); 

    for (int i = r; i < r + rlen; i++)
        arr[i+glen] = arr[i];

    r += glen;
}

bool GapBuff::remove()
{
    if(l == 0)
        return false;
    l--;
    return true;
}

GapBuff::~GapBuff()
{
    free(arr);
}


ostream& operator<<(ostream& out, GapBuff& buf)
{
    for (int i = 0; i < buf.l; i++)
        out << buf.arr[i];

    for (int i = buf.l; i < buf.r; i++)
        out << "_";

    for (int i = buf.r; i < buf.r + buf.rlen; i++)
        out << buf.arr[i];

    out << "\n"; // TODO: remove this

    return out;
}
