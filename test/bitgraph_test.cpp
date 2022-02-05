#define BOOST_TEST_MODULE BitgraphTest
#define BOOST_TEST_DYN_LINK 
#define BOOST_TEST_MAIN
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

#include "../src/bitgraph.hpp"

BOOST_AUTO_TEST_CASE( diagonal_test )
{
    BitGraph d = diagonal(3);
    BitGraph empty(3);
    BitGraph a(3, 982);
    BitGraph manual(3, 0b100010001);
    BOOST_CHECK_EQUAL(diagonal(3),manual);
    BOOST_CHECK_EQUAL(compose(d,empty), empty);
    BOOST_CHECK_EQUAL(compose(d,a), a);
}

BOOST_AUTO_TEST_CASE( composition_test )
{
    BitGraph d = diagonal(4);
    BitGraph z(4, 0);
    BitGraph  a(4, 0b1100011100110001);
    BitGraph  b(4, 0b0010000010101000);
    BitGraph ab(4, 0b0010101010101000);
    BitGraph ba(4, 0b0011000011111100);

    BOOST_CHECK_EQUAL( compose(a,d), a );
    BOOST_CHECK_EQUAL( compose(a,z), z );
    BOOST_CHECK_EQUAL( compose(a,b), ab );
    BOOST_CHECK_EQUAL( ba, compose(b,a) );
    BOOST_CHECK( compose(a,b) != compose(b,a) );
}
