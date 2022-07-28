#include <vector>
#include <cstddef>
#include <iostream>

class GapBuff {
    char* arr; // dynamic array
    std::size_t capacity;

    std::size_t l; // index of the first gap position
    std::size_t r; // index of the first valid position after the gap
                   // Invarient: r > l

    std::size_t rlen; // length after the gap

    static const std::size_t DEFAULT_GAP_LEN = 5;

    public:
    friend std::ostream& operator<<(std::ostream& out, GapBuff& gb);
    GapBuff();
    ~GapBuff();
    bool left();
    bool right();
    void grow();
    void insert(char);
    bool remove(void);

    /* std::size_t size(); */
};
