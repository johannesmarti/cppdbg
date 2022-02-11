#define BOOST_TEST_DYN_LINK
//#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>

#include "../src/construction_determinism.hpp"
#include "../src/examples.hpp"

BOOST_AUTO_TEST_SUITE(construction_determinism_test)

BOOST_AUTO_TEST_CASE(construction_deterministic_examples)
{
    BOOST_CHECK(is_construction_deterministic(hamburger));
}

BOOST_AUTO_TEST_CASE(not_construction_deterministic_examples)
{
    BOOST_CHECK(! is_construction_deterministic(force3d));
    BOOST_CHECK(! is_construction_deterministic(force4d));
    BOOST_CHECK(! is_construction_deterministic(force5d));
    BOOST_CHECK(! is_construction_deterministic(no_path));
    BOOST_CHECK(! is_construction_deterministic(dbg2));
}

BOOST_AUTO_TEST_SUITE_END()
