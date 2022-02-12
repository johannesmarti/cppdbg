#include <algorithm>
#include <numeric>
#include <iostream>
#include <memory>
#include <unordered_set>

#include "question.hpp"

Question::Question(unsigned dom_size) :
    antichain(),
    size(dom_size)
{
    antichain.reserve(dom_size);
    for (unsigned i = 0; i < dom_size; i++) {
        std::unique_ptr<Set> ptr = std::make_unique<Set>(singleton(dom_size, i));
        antichain.insert(std::move(ptr));
    }
    assert (check_coherence());
}

std::ostream& operator<<(std::ostream& os, const Question& q)
{
    for (const std::unique_ptr<Set> &m : q.maximal_propositions()) {
        os << *m << '\n';
    }
    return os;
}

bool Question::add(std::unique_ptr<Set> proposition)
{
    if (covers(*proposition))
        return false;
    else {
        add_uncovered(std::move(proposition)); 
        return true;
    }
}

void Question::add_uncovered(std::unique_ptr<Set> proposition)
{
    assert(! covers(*proposition));

    std::erase_if(antichain, [&proposition] (const std::unique_ptr<Set>& a) {
        return a->is_subset_of(*proposition);
    });

    antichain.insert(std::move(proposition));
    
    assert(check_coherence());
}

bool Question::check_coherence() const
{
    return covers_whole_domain() && is_antichain();
}

bool Question::covers_whole_domain() const
{
    auto xunioner = [](Set a, const std::unique_ptr<Set>& b) {
        return a | *b;
    };
    Set uni = std::accumulate(antichain.begin(), antichain.end(),
                              empty_proposition(), xunioner);
    return uni.all();
}

bool Question::is_antichain() const
{
    for (const std::unique_ptr<Set>& first : antichain)
        for (const std::unique_ptr<Set>& second : antichain)
            if (first->is_proper_subset_of(*second))
                return false;
    return true;
}
