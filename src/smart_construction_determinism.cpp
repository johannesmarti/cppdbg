#include <memory>
#include <vector>

#include "construction_determinism.hpp"
#include "labeled_bitgraph.hpp"
#include "smart_question.hpp"

std::unique_ptr<Question> deterministic_question(const LabeledBitGraph& lbg)
{
    std::unique_ptr<Question> q = std::make_unique<Question>(lbg.size());
    
    // TODO: There might be a smarter impementation!
    restart:
    for (const auto& q0 : q->maximal_propositions()) {
        for (const auto& q1 : q->maximal_propositions()) {
            Set suc0 = lbg.graph_of_label(Zero).image(*q0);
            Set suc1 = lbg.graph_of_label( One).image(*q1);
            auto intersection = std::make_unique<Set> (suc0 & suc1);
            if (q->add(std::move(intersection))) // true if intersection is added.
                goto restart;
        }
    }
    
    return q;
}

std::unique_ptr<Question> other_deterministic_question(const LabeledBitGraph& lbg)
{
    std::unique_ptr<Question> q = std::make_unique<Question>(lbg.size());
    std::vector<std::unique_ptr<Set>> to_add;
    
    do {
        to_add.clear();
        for (const auto& q0 : q->maximal_propositions()) {
            for (const auto& q1 : q->maximal_propositions()) {
                Set suc0 = lbg.graph_of_label(Zero).image(*q0);
                Set suc1 = lbg.graph_of_label( One).image(*q1);
                auto intersection = std::make_unique<Set> (suc0 & suc1);
                if (! q->covers(*intersection)) // true if intersection is added.
                    to_add.push_back(std::move(intersection));
            }
        }

        for (auto& p : to_add) {
            q->add(std::move(p));
        }
    } while (to_add.size() > 0);
    
    return q;
}

bool is_construction_deterministic(const LabeledBitGraph& lbg)
{
    return !deterministic_question(lbg)->is_total();
    //return !other_deterministic_question(lbg)->is_total();
}
