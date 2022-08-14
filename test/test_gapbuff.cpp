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

BOOST_AUTO_TEST_CASE(lrstr)
{
    GapBuff<char> buf;
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');
    buf.insert('d');
    buf.insert('e');
    buf.insert('f');
    buf.left();
    buf.left();
    buf.left();

    BOOST_CHECK(buf.left_string() == "abc");
    BOOST_CHECK(buf.right_string() == "def");
}

BOOST_AUTO_TEST_CASE(rremove)
{
    GapBuff<char> buf;
    buf.right_remove();
    buf.insert('a');
    buf.insert('b');
    buf.insert('c');
    buf.insert('d');
    buf.insert('e');
    buf.insert('f');
    buf.right_remove();
    BOOST_CHECK(buf.to_string() == "abcdef");

    buf.left();
    buf.left();
    buf.left();

    buf.right_remove();
    BOOST_CHECK(buf.to_string() == "abc");
    buf.insert('d');
    buf.insert('e');
    buf.insert('f');
    BOOST_CHECK(buf.to_string() == "abcdef");

    buf.left();
    buf.left();
    buf.right_remove();
    BOOST_CHECK(buf.to_string() == "abcd");
}

