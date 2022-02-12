#include <iostream>

#include <boost/dynamic_bitset.hpp>

#include "bitgraph.hpp"

using namespace std;

int main()
{
    BitGraph  b(4, 0b0010000010101000);
    boost::dynamic_bitset<> s01(4, 0b11);

    cout << b.image(s01) << endl;

    return 0;
}
