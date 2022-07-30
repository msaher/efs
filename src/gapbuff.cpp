#include <array>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include "gapbuff.h"
#include <iostream>

using std::ostream;
using std::size_t;
using std::string;

template <typename T>
GapBuff<T>::GapBuff(size_t cap)
{
    arrcap = cap;
    arr = (T*) malloc(cap);
    l = 0;
    r = cap;
    rlen = 0;
}

template <typename T>
bool GapBuff<T>::left()
{
    if (l <= 1) // 1 because we don't want a___ to be moved
        return false;

    arr[--r] = arr[--l];
    rlen++;

    return true;
}

template <typename T>
bool GapBuff<T>::right()
{
    if (r == arrcap)
        return false;

    arr[l++] = arr[r++];
    rlen--;

    return true;
}

template <typename T>
void GapBuff<T>::insert(T c)
{
    arr[l++] = c;

    if (r == l)
        grow();

    /* std::cout << *this; */
}

template <typename T>
void GapBuff<T>::grow()
{
    const size_t glen = arrcap; // gap length
    arrcap *= 2;
    arr = (T*) realloc(arr, arrcap*sizeof(T));
    if (arr == nullptr)
        throw std::bad_alloc(); 

    for (size_t i = r; i < r + rlen; i++)
        arr[i+glen] = arr[i];

    r += glen;
}

template <typename T>
bool GapBuff<T>::remove()
{
    if(l == 0)
        return false;
    l--;
    return true;
}

template <typename T>
GapBuff<T>::~GapBuff()
{
    free(arr);
}

string to_string(GapBuff<char>& buf)
{
    string s {};
    for (size_t i = 0; i < buf.l; i++)
        s += (buf.arr[i]);

    for (size_t i = buf.l; i < buf.r; i++)
        s += ("_");

    for (size_t i = buf.r; i < buf.r + buf.rlen; i++)
        s += buf.arr[i];

    return s;
}

template class GapBuff<char>;
