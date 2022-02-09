#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_set>

#include "question.hpp"

Question::Question(unsigned dom_size) :
    antichain(),
    domain_size(dom_size)
{
    antichain.reserve(dom_size);
    for (unsigned i = 0; i < dom_size; i++) {
        antichain.insert(singleton(dom_size, i));
    }
    assert (check_coherence());
}

std::ostream& operator<<(std::ostream& os, const Question& q)
{
    std::copy(q.antichain.begin(), q.antichain.end(),
              std::ostream_iterator<Set>(os, "\n"));
    return os;
}

bool Question::add(Set& proposition)
{
    if (covers(proposition))
        return false;
    else {
        add_uncovered(proposition); 
        return true;
    }
}

void Question::add_uncovered(Set& proposition)
{
    assert(! covers(proposition));

    /*
    std::erase_if(antichain, [&proposition] (Set a) {
        return a.is_subset_of(proposition);
    });
    */

    antichain.insert(proposition);
    
    assert(check_coherence());
}

bool Question::check_coherence() const
{
    return covers_whole_domain();
}

bool Question::covers_whole_domain() const
{
    return true;
}
