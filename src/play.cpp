#include <iostream>

#include "labeled_bitgraph.hpp"

using namespace std;

int main()
{
    LabeledBitGraph a(3);
    LabeledBitGraph b(3, 2);

    a.add_edge(Zero, 0, 0);
    a.add_edge(Zero, 0, 1);
    a.add_edge(Zero, 0, 2);
    a.add_edge(One, 1, 1);
    a.add_edge(One, 1, 2);
    a.add_edge(One, 2, 0);

    cout << a.to_bitcode() << endl;

    cout << a << endl;

    return 0;
}
