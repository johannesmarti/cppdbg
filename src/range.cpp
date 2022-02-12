#include <iostream>

#include "labeled_bitgraph.hpp"
#include "construction_determinism.hpp"

using namespace std;

unsigned long long num_labeled_graphs(Size s) {
    return 1ull << ((unsigned long long) (2*s*s));
}

void check_all(Size s, Size f)
{
    const unsigned long long bound = num_labeled_graphs(s) / f;
    unsigned long long num_nconstruction_deterministic = 0;

    for (unsigned long long i = 0; i < bound; i++) {
        LabeledBitGraph lbg(s, i);
        if (! is_construction_deterministic(lbg))
            num_nconstruction_deterministic++;
    }

    cout << num_nconstruction_deterministic << " of " << bound << endl;
}

int main()
{
    //check_all(3, 1);
    check_all(4, 1024 * 4);

    return 0;
}
