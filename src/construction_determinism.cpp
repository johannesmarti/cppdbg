#include <memory>

#include "construction_determinism.hpp"
#include "labeled_bitgraph.hpp"
#include "question.hpp"

std::unique_ptr<Question> deterministic_question(LabeledBitGraph& lbg)
{
    std::unique_ptr<Question> q = std::make_unique<Question>(lbg.size());
    
    // TODO: There might be a smarter impementation!
    restart:
    for (Set q0 : q->maximal_propositions()) {
        for (Set q1 : q->maximal_propositions()) {
            Set suc0 = lbg.graph_of_label(Zero).image(q0);
            Set suc1 = lbg.graph_of_label( One).image(q1);
            Set intersection = suc0 & suc1;
            if (q->add(intersection)) // true if intersection is added.
                goto restart;
        }
    }
    
    return q;
}

bool is_construction_deterministic(LabeledBitGraph& lbg)
{
    return !deterministic_question(lbg)->is_total();
}
