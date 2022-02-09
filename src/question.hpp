#ifndef QUESTION_HPP_
#define QUESTION_HPP_

#include <iostream>
#include <unordered_set>

#include <boost/dynamic_bitset.hpp>
#include <boost/functional/hash.hpp>

#include "bit_tricks.hpp"

typedef boost::dynamic_bitset<> Set;

/*
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
*/

inline Set singleton(unsigned dom_size, unsigned elem) {
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
    Question(unsigned dom_size);

    // Checks whether the domain is a member of the family of sets. This
    // implies because of downwards closure that every subset of the
    // domain is covered.
    bool is_total() const {
        return antichain.size() == 1;
    }

    bool covers(Set& proposition) const {
        assert (proposition.size() == domain_size);
        return std::any_of(antichain.cbegin(), antichain.cend(),
                            [&proposition](Set a) {
                                return proposition.is_subset_of(a);
                            });
        /*
        for (auto const& e : antichain) {
            if (proposition.is_subset_of(e))
                return true;
        }
        return false;
        */  
    }

    bool add(Set& proposition);
    void add_uncovered(Set& proposition);

    friend std::ostream& operator<<(std::ostream& os, const Question& q);

private:
    std::unordered_set <Set> antichain;
    unsigned domain_size;
    Set empty_proposition() const {
        return Set(domain_size);
    }
    Set total_proposition() const {
        Set dom = empty_proposition();
        dom.set();
        return dom;
    }
    bool check_coherence() const;
    bool covers_whole_domain() const;
    bool is_antichain() const;
};

std::ostream& operator<<(std::ostream& os, const Question& q);

#endif // QUESTION_HPP_
