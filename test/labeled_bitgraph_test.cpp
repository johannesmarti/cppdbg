#define BOOST_TEST_DYN_LINK
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

#include "../src/labeled_bitgraph.hpp"

BOOST_AUTO_TEST_SUITE(labeled_bitgraph_test)

BOOST_AUTO_TEST_CASE(constructor_test)
{
    LabeledBitGraph a(3);
    BOOST_CHECK_EQUAL(a, LabeledBitGraph(3, 0));

    a.add_edge(Zero, 0, 1);
    a.add_edge(Zero, 0, 2);
    a.add_edge(Zero, 1, 1);
    a.add_edge(Zero, 2, 1);
    a.add_edge( One, 0, 0);
    a.add_edge( One, 1, 1);
    a.add_edge( One, 1, 2);
    a.add_edge( One, 2, 1);
    a.add_edge( One, 2, 2);
    BOOST_CHECK_EQUAL(a, LabeledBitGraph(3, 0b110110001010010110 ));
    BOOST_CHECK_EQUAL(a, LabeledBitGraph(BitGraph(3, 0b010010110),
                                         BitGraph(3, 0b110110001)));
}

BOOST_AUTO_TEST_CASE(to_bitcode_test)
{
    LabeledBitGraph a(3);

    a.add_edge(Zero, 0, 1);
    a.add_edge(Zero, 0, 2);
    a.add_edge(Zero, 1, 1);
    a.add_edge(Zero, 2, 1);
    a.add_edge( One, 0, 0);
    a.add_edge( One, 1, 1);
    a.add_edge( One, 1, 2);
    a.add_edge( One, 2, 1);
    a.add_edge( One, 2, 2);
    BOOST_CHECK_EQUAL(a, LabeledBitGraph(3, a.to_bitcode()));
}

BOOST_AUTO_TEST_SUITE_END()
