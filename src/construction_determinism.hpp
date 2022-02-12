#ifndef CONSTRUCTION_DETERMINISM_HPP_
#define CONSTRUCTION_DETERMINISM_HPP_

#include "labeled_bitgraph.hpp"

// Checks whether the graph in the argument is construction
// deterministic. This notion is defined in the 'det.pdf'
bool is_construction_deterministic(const LabeledBitGraph&);

#endif // CONSTRUCTION_DETERMINISM_HPP_
