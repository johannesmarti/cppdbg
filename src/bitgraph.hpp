#ifndef BITGRAPH_HPP_
#define BITGRAPH_HPP_

#include <iostream>
#include <boost/dynamic_bitset.hpp>

#include "bit_tricks.hpp"

typedef unsigned int Node;
typedef Node Size;

// Implementation of an unlabeled graph as an adjacency matrix. The
// adjacency matrix is implemented by a dynamic bitset. The nodes of the
// graph are assumed to be the numbers from 0 to 'num_nodes - 1', and
// function as indices into the matrix.
class BitGraph
{
public:
    BitGraph(Size s) :
        num_nodes(s),
        bits(s*s) { }

    template <typename T>
    BitGraph(Size s, T bits_as_int) :
        num_nodes(s),
        bits(s*s, bits_as_int)
    {
        assert(subset<T>(bits_as_int,ones<T>(s*s)));
    }

/*
    // copy constructor with logging
    BitGraph(const BitGraph& bg) :
        num_nodes(bg.num_nodes),
        bits(bg.bits) {
        std::cerr << "executing copy constructor of BitGraph\n";
    }

    // move constructor with logging
    BitGraph(BitGraph&& bg) :
        num_nodes(bg.num_nodes),
        bits(bg.bits) {
        std::cerr << "executing move constructor of BitGraph\n";
    }

    // destructor with logging
    ~BitGraph() {
        std::cerr << "executing destructor of BitGraph\n";
    }
*/

    Size size() const {
        return num_nodes;
    }

    bool has_edge(Node v, Node u) const {
        return bits[offset_of_edge(v,u)];
    }

    void add_edge(Node v, Node u) {
        bits[offset_of_edge(v,u)] = 1;
    }

    void remove_edge(Node v, Node u) {
        bits[offset_of_edge(v,u)] = 0;
    }

    unsigned long to_ulong() const {
        const Size s = size();
        assert(num_bits<unsigned long> >= s*s);
        return bits.to_ulong();
    }

    boost::dynamic_bitset<> successors_of(Node v) const {
        assert(this->contains_node(v));

        // I am not sure what is the right way of implementing this!
        const Size s = this->size();
        boost::dynamic_bitset<> res(s);
        const Size offset = v * num_nodes;
        for (unsigned i = 0; i < s; i++) {
            res[i] = bits[offset + i];
        }
        /*
        // This code is less efficient, probabely because it allocates
        // too much memory.
        boost::dynamic_bitset<> res = bits >> (v * num_nodes);
        res.resize(num_nodes);
        */

        return res;
    }

    boost::dynamic_bitset<> image(const boost::dynamic_bitset<> set) const;

    friend bool operator==(const BitGraph &bg1, const BitGraph &bg2);
private:
    Size num_nodes; // the number of nodes in the graph
    // 'bits' is the bitset that represent the adjacency matrix. It
    // is assumed to have a size that is equal to 'num_nodes * num_nodes'.
    boost::dynamic_bitset<> bits;

    bool contains_node(Node v) const {
        return v < num_nodes;
    }

    // This function computes the position of the bit corresponding
    // to the edge (v,u) in the bitset.
    boost::dynamic_bitset<>::size_type offset_of_edge(Node v, Node u) const {
        // We perform boundchecking just here, to not have to repeat
        // it in all other methods that index the bitset.
        assert(this->contains_node(v));
        assert(this->contains_node(u));
        return v * num_nodes + u;
    }
};

inline bool operator==(const BitGraph &bg1, const BitGraph &bg2) {
    return bg1.bits == bg2.bits;
}

// This function prints the graph to a stream. It provides a bit more
// customization than the shift operator.
void stream_graph(std::ostream& os, const char* relation_symbol, const BitGraph& bg);

// This function provides a neat string representation of the relation.
inline std::ostream& operator<<(std::ostream& os, const BitGraph& bg)
{
    stream_graph(os, "=>", bg);
    return os;
}

// Composition of two relations. For efficiency reasons it is assumed
// that the complier si smart enough not to copy the return value.
BitGraph compose(const BitGraph& a, const BitGraph& b);

BitGraph diagonal(Size s);

#endif // BITGRAPH_HPP_
