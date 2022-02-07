#ifndef QUESTION_HPP_
#define QUESTION_HPP_

#include <iostream>
#include <unordered_set>

#include <boost/dynamic_bitset.hpp>
#include <boost/functional/hash.hpp>

#include "bit_tricks.hpp"

typedef boost::dynamic_bitset<> Set;

// Make bitsets hashable. This is copy pasted from stackoverflow.
namespace std {

    template <typename Block, typename Alloc> struct hash<boost::dynamic_bitset<Block, Alloc> > {
        size_t operator()(boost::dynamic_bitset<Block, Alloc> const& bs) const {
            size_t seed = boost::hash_value(bs.size());

            std::vector<Block> blocks(bs.num_blocks());
            boost::hash_range(seed, blocks.begin(), blocks.end());

            return seed;
        }
    };
}

Set singleton(unsigned dom_size, unsigned elem) {
    assert (elem < dom_size);
    Set s(dom_size);
    s[elem] = 1;
    return s;
}

// Implements an inquisitive proposition or question. That means it
// represents a downwards closed family of subsets of some domain D =
// {0,...,i - 1}. Alternatively we can think of it as an antichain.
class Question
{
public:
    Question(unsigned dom_size) :
        antichain(),
        domain_size(dom_size) {
            antichain.reserve(dom_size);
            for (unsigned i = 0; i < dom_size; i++) {
                antichain.insert(singleton(dom_size, i));
            }
        }

    bool covers(Set& proposition) const {
        /*return std::any_of(antichain.cbegin(), antichain.cend(),
                           [proposition](Set a){ return
proposition.is_subset_of(a)); })*/
        for (auto const& e : antichain) {
            if (proposition.is_subset_of(e))
                return true;
        }
        return false;
    }

    // Checks whether the domain is a member of the family of sets. This
    // implies because of downwards closure that every subset of the
    // domain is covered.
    bool is_total() const {
        Set dom(domain_size);
        dom.set(); // set all bits to 1
        return antichain.count(dom);
    }


private:
    std::unordered_set <Set> antichain;
    unsigned domain_size;
    //bool covers_whole_domain() const;
    //bool is_real_antichain() const;
};

#endif // QUESTION_HPP_
