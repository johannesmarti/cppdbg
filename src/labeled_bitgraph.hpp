#ifndef LABELED_BITGRAPH_HPP_
#define LABELED_BITGRAPH_HPP_

#include <iostream>

#include "bitgraph.hpp"
#include "bit_tricks.hpp"

enum Label {Zero, One};

// Implementation of a graph in which edges are labeled with elements
// from the enum 'Label'. Internally it holds a separate BitGraph for
// each label. As with BitGraph the nodes of a a LabeledBitGraph 'lbg'
// are always elements of type Node in the range from 0 to 'lbg.size() -
// 1'.
class LabeledBitGraph
{
    public:
        LabeledBitGraph(Size s) :
            zero_graph(s),
            one_graph(s) {}

        // This constructor takes a bit pattern 'bitcode' that encodes
        // the graph as follows: The edge with label lab from v to w
        // exists iff the bit at position
        //     'b * (size * size) + v * size + w'
        // is set, where 'b' is 1 if lab is One and 'b' is 0 if lab is
        // Zero.
        template <typename T>
        LabeledBitGraph(Size size, T bitcode) : 
            zero_graph(size, bitcode & ones<T>(size*size)),
            one_graph(size, bitcode >> size*size)
        {
            // Check that no bits are set that would not have a meaning
            // in the encoding.
            assert(subset<T>(bitcode,ones<T>(2*size*size)));
        }

        LabeledBitGraph(const BitGraph &zg, const BitGraph &og) :
            zero_graph(zg),
            one_graph(og) { assert(zg.size() == og.size()); }

        Size size() const {
            assert(zero_graph.size() == one_graph.size());
            return zero_graph.size();
        }

        // Returns a reference to the BitGraph of the label 'l' inside
        // the current LabeledBitGraph object (*this). The reference is
        // only valid as long as the current LabeledBitGraph object is
        // alive. We need both a mutable version and a const version of
        // this method. This is needed because the const version can
        // only return const references to object members. However,
        // there are also use cases (for example inside the method
        // 'add_edge' below) where we need a mutable reference.
        const BitGraph &graph_of_label(Label l) const {
            switch (l) {
                case Zero: return zero_graph;
                case One:  return one_graph;
            }
        }

        BitGraph &graph_of_label(Label l) {
            switch (l) {
                case Zero: return zero_graph;
                case One:  return one_graph;
            }
        }

        bool has_edge(Label l, Node v, Node u) const {
            return graph_of_label(l).has_edge(v, u);
        }

        void add_edge(Label l, Node v, Node u) {
            graph_of_label(l).add_edge(v, u);
        }

        void remove_edge(Label l, Node v, Node u) {
            graph_of_label(l).remove_edge(v, u);
        }

        // Transforms the labeled graph into a bitset description inside
        // an unsigned long int. It assumes that the '2*s*s' where 's =
        // this->size()' is less or equal to the number of bits in an
        // unsigned long. The coding is the same as the one used by the
        // constructor LabeledBitgraph(Size ssize, T bitcode).
        // Composing in either way with this constuctor yields the the
        // identity. For instance we have that for any not too large
        // LabeledBitGraph 'lbg' it holds that 'lbg ==
        // LabeledBitGraph(lbg.size(), lbg.to_bitcode())'.
        unsigned long to_bitcode() const {
            Size s = size();
            Size ssq = s*s;
            assert(2*ssq <= num_bits<unsigned long>);
            return graph_of_label(Zero).to_ulong() |
                  (graph_of_label(One).to_ulong() << ssq);
        }

    private:
        // The variable 'zero_graph' is the graph of all edges that are
        // labeled with zero. The variable 'one_graph' holds all edges
        // that are labeled with one. It is assumed as an invariant that
        // 'zero_graph.size() == one_graph.size()'.
        BitGraph zero_graph;
        BitGraph one_graph;
};

inline bool operator==(const LabeledBitGraph &lbg1, const LabeledBitGraph &lbg2) {
    return (lbg1.graph_of_label(Zero) == lbg2.graph_of_label(Zero)) &&
           (lbg1.graph_of_label(One ) == lbg2.graph_of_label(One ));
}

std::ostream& operator<<(std::ostream& os, const LabeledBitGraph& lbg);

#endif // LABELED_BITGRAPH_HPP_
