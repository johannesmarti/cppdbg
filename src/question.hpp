#ifndef QUESTION_HPP_
#define QUESTION_HPP_

#include <iostream>
#include <memory>
#include <unordered_set>

#include <boost/dynamic_bitset.hpp>

#include "bit_tricks.hpp"

typedef boost::dynamic_bitset<> Set;

// Singleton subset of {0,...,dom_size-1}, encoded as a bitset. 
inline Set singleton(unsigned dom_size, unsigned elem) {
    assert (elem < dom_size);
    Set s(dom_size);
    s[elem] = 1;
    return s;
}

// Implements an inquisitive proposition or question. This is a
// downwards closed family of subsets of some domain. The domain is
// taken to be the set of numbers {0,...,i - 1}, where i is
// the return value of 'domain_size()'.
//
// Sets are represented by 'boost::dynamic_bitsets' of size
// 'domain_size()'.
//
// Internally, the family of subsets is implented as the antichain of
// its maximal elements. A set is in the question if it is a subset of
// one of the elements in the antichain.
class Question
{
public:
    Question(unsigned dom_size);

    unsigned domain_size() const {
        return size;
    }

    // Checks whether the domain is a member of the family of sets. This
    // implies because of downwards closure that every subset of the
    // domain is covered.
    bool is_total() const {
        return antichain.size() == 1;
    }

    // Returns the antichain of maximal subsets. The returned reference
    // points into the internal unordered set and lives as long as the
    // question.
    const std::unordered_set<std::unique_ptr<Set>>& maximal_propositions()
const {
        return antichain;
    }

    // Checks whether the argument set is in the question, meaning that
    // it is a subset of one of the elements of the antichain of maximal
    // elements.
    bool covers(Set& proposition) const {
        assert (proposition.size() == domain_size());
        return std::any_of(antichain.begin(), antichain.end(),
                            [&proposition](const std::unique_ptr<Set>& a) {
                                return proposition.is_subset_of(*a);
                            });
        /*
        for (auto const& e : antichain) {
            if (proposition.is_subset_of(e))
                return true;
        }
        return false;
        */  
    }

    // Adds a set to the question. If the set, or one of its supersets,
    // is alrady in the question then the question stays unchanged.
    bool add(std::unique_ptr<Set> proposition);

    // Adds an elements to the set, assuming that it is not yet covered
    // by the question (hence, no superset of the set is already in the
    // question). If this is assumption is not met then we get an
    // assertion failure.
    void add_uncovered(std::unique_ptr<Set> proposition);

    // The empty set encoded as a bitset of size domain_size().
    Set empty_proposition() const {
        return Set(domain_size());
    }
    // The domain as a bitset.
    Set domain() const {
        Set dom = empty_proposition();
        dom.set(); // set all bits to one.
        return dom;
    }

private:
    std::unordered_set<std::unique_ptr<Set>> antichain;
    unsigned size;
    // The following three methods are used for internal coherence
    // checks in assertions.
    bool check_coherence() const;
    bool covers_whole_domain() const;
    bool is_antichain() const;
};

std::ostream& operator<<(std::ostream& os, const Question& q);

#endif // QUESTION_HPP_
