#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE gapbuff
#include <boost/test/unit_test.hpp>
#include "../src/gapbuff.h"
#include <string>

using std::string;

BOOST_AUTO_TEST_CASE(leftright)
{
    GapBuff<char> buf{10};
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');
    buf.insert('d');
    buf.insert('e');
    buf.insert('f');
    buf.insert('g');
    BOOST_CHECK(buf.left() == true);
    BOOST_CHECK(buf.right() == true);
    BOOST_CHECK(buf.right() == false);
    BOOST_CHECK(buf.size() == 7);
}

BOOST_AUTO_TEST_CASE(strconst)
{
    string s = "this is a piece of text";
    GapBuff<char> buf {s};
    BOOST_CHECK(buf.gap_string() == "_" + s);
}
