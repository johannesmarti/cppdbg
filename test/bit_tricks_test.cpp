#define BOOST_TEST_DYN_LINK 
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

#include "../src/bit_tricks.hpp"

BOOST_AUTO_TEST_SUITE(bit_tricks_test)

BOOST_AUTO_TEST_CASE(ones_test)
{
    BOOST_CHECK_EQUAL(ones(0), 0);
    BOOST_CHECK_EQUAL(ones(1), 1);
    BOOST_CHECK_EQUAL(ones(2), 3);
    BOOST_CHECK_EQUAL(ones(4), 15);
}

BOOST_AUTO_TEST_CASE(subset_test)
{
    BOOST_CHECK(subset(0, 3));
    BOOST_CHECK(!subset(3, 0));
    BOOST_CHECK(subset(0b100101011,
                       0b101101111));
    BOOST_CHECK(!subset(0b110111011,
                        0b100101011));
    BOOST_CHECK(subset(123948, 123948));
    BOOST_CHECK(!subset(17, 1248));
}

BOOST_AUTO_TEST_SUITE_END()
