#include <iostream>

#include "labeled_bitgraph.hpp"

using namespace std;

ostream& operator<<(ostream& os, const LabeledBitGraph& lbg)
{
    stream_graph(os, "0=>", lbg.graph_of_label(Zero));
    os << '\n';
    stream_graph(os, "1=>", lbg.graph_of_label(One));
    return os;
}
