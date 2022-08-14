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

template <typename T>
GapBuff<T>::GapBuff(size_t cap)
{
    arrcap = cap;
    arr = (T*) malloc(cap*sizeof(T));
    l = 0;
    r = cap;
    rlen = 0;
}

template <>
GapBuff<char>::GapBuff(string str)
{
    arrcap = rlen = str.length();
    arr = (char*) malloc(arrcap*sizeof(char)+1); // +1 for the gap of
    l = 0;
    r = 1;
    memcpy((arr+1), str.c_str(), rlen);
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
void GapBuff<T>::set_pos(size_t pos)
{
    while (pos < l)
        this->left();

    while (pos > l)
        this->right();
}

template <typename T>
GapBuff<T>::~GapBuff()
{
    free(arr);
}

template <>
string GapBuff<char>::gap_string() // for testing
{
    string s {};
    for (size_t i = 0; i < l; i++)
        s += (arr[i]);

    for (size_t i = l; i < r; i++)
        s += ("_");

    for (size_t i = r; i < r + rlen; i++)
        s += arr[i];

    return s;
}

template <>
string GapBuff<char>::to_string()
{
    string s {};
    for (size_t i = 0; i < l; i++)
        s += (arr[i]);

    for (size_t i = r; i < r + rlen; i++)
        s += arr[i];

    return s;
}

template<typename T>
size_t GapBuff<T>::size()
{
    return l+rlen;
}

template class GapBuff<char>;
