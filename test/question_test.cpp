#define BOOST_TEST_DYN_LINK
//#include <boost/test/included/unit_test.hpp>
#include <memory>
#include <boost/test/unit_test.hpp>

#include "../src/question.hpp"

BOOST_AUTO_TEST_SUITE(question_test)

BOOST_AUTO_TEST_CASE(question_scenario)
{
    Question q(4);
    Set p1  (4,0b0010);
    Set p01 (4,0b0011);
    Set p12 (4,0b0110);
    Set p23 (4,0b1100);
    Set p123(4,0b1110);
    Set total = q.domain();

    BOOST_CHECK(! q.is_total());
    BOOST_CHECK(q.covers(p1));
    BOOST_CHECK(! q.covers(p01));
    BOOST_CHECK_EQUAL(4, q.maximal_propositions().size());

    BOOST_CHECK(q.add(std::make_unique<Set>(p23)));
    BOOST_CHECK(!q.add(std::make_unique<Set>(p23)));
    BOOST_CHECK(q.covers(p23));
    BOOST_CHECK(q.covers(p1));
    BOOST_CHECK(! q.covers(p12));
    BOOST_CHECK(! q.covers(p123));

    q.add_uncovered(std::make_unique<Set>(p12));
    BOOST_CHECK(q.covers(p12));
    {
        Set other(4, 0b0110);
        BOOST_CHECK(! q.add(std::make_unique<Set>(other)));
    }
    BOOST_CHECK(q.covers(p23));
    BOOST_CHECK(q.covers(p1));
    BOOST_CHECK(! q.covers(p01));
    BOOST_CHECK(! q.covers(p123));
    BOOST_CHECK(! q.add(std::make_unique<Set>(p23)));

    BOOST_CHECK(q.add(std::make_unique<Set>(p123)));
    BOOST_CHECK(q.covers(p123));
    BOOST_CHECK(q.covers(p12));
    BOOST_CHECK(q.covers(p23));
    BOOST_CHECK(q.covers(p1));
    BOOST_CHECK(! q.covers(p01));
    BOOST_CHECK(! q.is_total());
    BOOST_CHECK_EQUAL(2, q.maximal_propositions().size());

    BOOST_CHECK(q.add(std::make_unique<Set>(total)));
    BOOST_CHECK(q.covers(p123));
    BOOST_CHECK(q.covers(p12));
    BOOST_CHECK(q.covers(p23));
    BOOST_CHECK(q.covers(p1));
    BOOST_CHECK(q.covers(p01));
    BOOST_CHECK(q.is_total());
}

BOOST_AUTO_TEST_SUITE_END()
