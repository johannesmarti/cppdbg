#include "bitgraph.hpp"

using namespace std;

ostream& operator<<(ostream& os, const BitGraph& bg)
{
    Size s = bg.size();
    for (Node v = 0; v < s; v++) {
        os << v << " => ";
        Node u = 0;
        while (u < s) {
            if (bg.has_edge(v,u)) {
                os << u;
                u++;
                break;
            }
            u++;
        }
        while (u < s) {
            if (bg.has_edge(v,u)) {
                os << ", " << u;
            }
            u++;
        }
        os << '\n';
    }

    return os;
}

BitGraph diagonal(Size s)
{
    BitGraph result(s);
    for (Node v = 0; v < s; v++) {
        result.add_edge(v,v);
    }
    return result;
}

BitGraph compose(const BitGraph& a, const BitGraph& b)
{
    assert(a.size() == b.size());
    Node s = a.size();
    BitGraph result(s);
    for (Node v = 0; v < s; v++) {
        for (Node u = 0; u < s; u++) {
            for (Node i = 0; i < s; i++) {
                if (a.has_edge(v,i) && b.has_edge(i, u)) {
                    result.add_edge(v,u);
                    break;
                }
            }
        }
    }
    return result;
}

