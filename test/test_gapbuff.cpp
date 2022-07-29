#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE gapbuff
#include <boost/test/unit_test.hpp>
#include "../src/gapbuff.h"
#include <string>

using std::string;

BOOST_AUTO_TEST_CASE(gapbuff_test)
{
    BOOST_CHECK(1 + 1 == 2);

    GapBuff<char> buf{};
    buf.insert('c');
    buf.insert('d');
    BOOST_CHECK(buf.left() == true);
}
