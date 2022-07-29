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
GapBuff<T>::GapBuff()
{
    capacity = DEFAULT_GAP_LEN;
    arr = (T*) malloc(capacity);
    l = 0;
    r = capacity;
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
    if (r == capacity)
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
    const size_t glen = DEFAULT_GAP_LEN;
    capacity += glen;
    arr = (T*) realloc(arr, capacity*sizeof(T));
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


template <typename T>
string GapBuff<T>::to_string()
{
    string s {};
    for (size_t i = 0; i < l; i++)
        s.append(arr[i]);

    for (size_t i = l; i < r; i++)
        s.append("_");

    for (size_t i = r; i < r + rlen; i++)
        s.append(arr[i]);

    return s;
}

template<typename T>
ostream& operator<<(ostream& out, GapBuff<T> buf)
{
    return out << buf.to_string();
}
