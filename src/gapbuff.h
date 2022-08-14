#ifndef GAPBUFF_H
#define GAPBUFF_H
#include <vector>
#include <cstddef>
#include <iostream>

template <typename T>
class GapBuff {
    T* arr; // dynamic array
    std::size_t arrcap;

    std::size_t l; // index of the first gap position
    std::size_t r; // index of the first valid position after the gap
                   // Invarient: r > l

    std::size_t rlen; // length after the gap

    public:
    static const std::size_t DEFAULT_GAP_LEN = 5;
    GapBuff(std::size_t cap=DEFAULT_GAP_LEN);
    GapBuff(std::string);
    ~GapBuff();
    bool left();
    bool right();
    void grow();
    void insert(T);
    bool remove();
    void set_pos(size_t);
    std::size_t size();

    std::string gap_string();
    std::string left_string();
    std::string right_string();
    std::string to_string();
};

#endif
