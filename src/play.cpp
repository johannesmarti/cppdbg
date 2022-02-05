#include <iostream>

#include "labeled_bitgraph.hpp"

using namespace std;

int main()
{
    LabeledBitGraph a(3);

    a.add_edge(Zero, 0, 0);
    a.add_edge(Zero, 0, 1);
    a.add_edge(Zero, 0, 2);
    a.add_edge(One, 1, 1);
    a.add_edge(One, 1, 2);
    a.add_edge(One, 2, 0);

    cout << a.graph_of_label(Zero) << endl;
    cout << a.graph_of_label(One) << endl;
    return 0;
}
