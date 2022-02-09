#define BOOST_TEST_DYN_LINK
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/dynamic_bitset.hpp>

#include "../src/bitgraph.hpp"

BOOST_AUTO_TEST_SUITE(bitgraph_test)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    BitGraph a(3);

    BOOST_CHECK_EQUAL(a, BitGraph(3, 0));
    a.add_edge(0, 1);
    a.add_edge(0, 2);
    a.add_edge(1, 1);
    a.add_edge(2, 1);
    BOOST_CHECK_EQUAL(a, BitGraph(3, 0b010010110));
}

BOOST_AUTO_TEST_CASE(diagonal_test)
{
    BitGraph d = diagonal(3);
    BitGraph empty(3);
    BitGraph a(3, 508);
    BitGraph manual(3, 0b100010001);
    BOOST_CHECK_EQUAL(diagonal(3),manual);
    BOOST_CHECK_EQUAL(compose(d,empty), empty);
    BOOST_CHECK_EQUAL(compose(d,a), a);
}

BOOST_AUTO_TEST_CASE(composition_test)
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
    BOOST_CHECK(!( compose(a,b) == compose(b,a) ));
}

BOOST_AUTO_TEST_CASE(successor_test)
{
    BitGraph d = diagonal(4);
    BitGraph  a(4, 0b1100011100110001);
    BitGraph  b(4, 0b0010000010101000);
    boost::dynamic_bitset<> s0(4, 0b1);
    boost::dynamic_bitset<> s1(4, 0b10);
    boost::dynamic_bitset<> s2(4, 0b100);
    boost::dynamic_bitset<> s3(4, 0b1000);
    boost::dynamic_bitset<> s01(4, 0b11);
    boost::dynamic_bitset<> s31(4, 0b1010);

    BOOST_CHECK_EQUAL( d.successors_of(0), s0);
    BOOST_CHECK(! (d.successors_of(0) == s01));
    BOOST_CHECK_EQUAL( d.successors_of(1), s1);

    BOOST_CHECK_EQUAL( a.successors_of(1), s01);
    BOOST_CHECK_EQUAL( b.successors_of(0), s3);
}

BOOST_AUTO_TEST_CASE(image_test)
{
    BitGraph  a(4, 0b1100011100110001);
    BitGraph  b(4, 0b0010000010101000);
    BitGraph ab(4, 0b0010101010101000);
    BitGraph ba(4, 0b0011000011111100);
    boost::dynamic_bitset<> s0(4, 0b1);
    boost::dynamic_bitset<> s1(4, 0b10);
    boost::dynamic_bitset<> s2(4, 0b100);
    boost::dynamic_bitset<> s3(4, 0b1000);
    boost::dynamic_bitset<> s01(4, 0b11);
    boost::dynamic_bitset<> s31(4, 0b1010);
    BOOST_CHECK_EQUAL( b.image(s01), s31);
    BOOST_CHECK_EQUAL( a.image(b.image(s01)), ba.image(s01));
    BOOST_CHECK_EQUAL( b.image(a.image(s01)), ab.image(s01));
    BOOST_CHECK_EQUAL( a.image(b.image(s31)), ba.image(s31));
    BOOST_CHECK_EQUAL( b.image(a.image(s31)), ab.image(s31));
}

BOOST_AUTO_TEST_SUITE_END()
