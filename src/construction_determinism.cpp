#include <memory>
#include <vector>

#include "construction_determinism.hpp"
#include "labeled_bitgraph.hpp"
#include "question.hpp"

std::unique_ptr<Question> deterministic_question(const LabeledBitGraph& lbg)
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

std::unique_ptr<Question> other_deterministic_question(const LabeledBitGraph& lbg)
{
    std::unique_ptr<Question> q = std::make_unique<Question>(lbg.size());
    std::vector<Set> to_add;
    
    do {
        to_add.clear();
        for (Set q0 : q->maximal_propositions()) {
            for (Set q1 : q->maximal_propositions()) {
                Set suc0 = lbg.graph_of_label(Zero).image(q0);
                Set suc1 = lbg.graph_of_label( One).image(q1);
                Set intersection = suc0 & suc1;
                if (! q->covers(intersection)) // true if intersection is added.
                    to_add.push_back(intersection);
            }
        }

        for (Set p : to_add) {
            q->add(p);
        }
    } while (to_add.size() > 0);
    
    return q;
}

bool is_construction_deterministic(const LabeledBitGraph& lbg)
{
    return !deterministic_question(lbg)->is_total();
    //return !other_deterministic_question(lbg)->is_total();
}
