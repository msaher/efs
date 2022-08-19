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
    capacity = cap;
    array = (T*) malloc(cap*sizeof(T));
    left = 0;
    right = cap;
    rlen = 0;
}

template <>
GapBuff<char>::GapBuff(string str)
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


template <typename T>
bool GapBuff<T>::move_left()
{
    if (left == 0)
        return false;

    array[--right] = array[--left];
    rlen++;

    return true;
}

template <typename T>
bool GapBuff<T>::move_right()
{
    if (rlen == 0)
        return false;

    array[left++] = array[right++];
    rlen--;

    return true;
}

template <typename T>
void GapBuff<T>::insert(T c)
{
    array[left++] = c;

    if (right == left)
        grow();
}

template <typename T>
void GapBuff<T>::grow()
{
    // double the array capacity everytime we grow()
    // If we're doubling the capacity, the new gap
    // length is going to be equal to capacity
    const size_t glen = capacity;
    capacity *= 2;
    array = (T*) realloc(array, capacity*sizeof(T));
    if (array == nullptr)
        throw std::bad_alloc(); 

    for (size_t i = right; i < right + rlen; i++)
        array[i+glen] = array[i];

    right += glen;
}

template <typename T>
bool GapBuff<T>::remove()
{
    if(left == 0)
        return false;
    left--;
    return true;
}

template <typename T>
void GapBuff<T>::set_pos(size_t pos)
{
    if (pos == left) // no need to move
        return;

    bool (GapBuff::*move)();
    if (left < pos)
        move = &GapBuff<T>::move_right;
    else
        move = &GapBuff<T>::move_left;

    while (pos != left)
        (this->*move)();
}

template <typename T>
GapBuff<T>::~GapBuff()
{
    free(array);
}

template <>
string GapBuff<char>::gap_string() // for testing
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

template <>
string GapBuff<char>::left_string()
{
    string s {};
    for (size_t i = 0; i < left; i++)
        s += (array[i]);
    return s;
}

template <>
string GapBuff<char>::right_string()
{
    string s {};
    for (size_t i = right; i < right + rlen; i++)
        s += array[i];
    return s;
}

template <typename T>
void GapBuff<T>::goto_end()
{
    while (rlen != 0)
        move_right();
}

template <>
void GapBuff<char>::append(string str)
{
    goto_end(); // position the gap at the end
    for (auto c : str)
        insert(c);
}

template<typename T>
void GapBuff<T>::right_remove()
{
    right = capacity;
    rlen = 0;
}

template <>
string GapBuff<char>::to_string()
{
    return left_string() + right_string();
}

template<typename T>
size_t GapBuff<T>::size()
{
    return left+rlen;
}

template<typename T>
bool GapBuff<T>::empty()
{
    return this->size() == 0;
}

template class GapBuff<char>;
