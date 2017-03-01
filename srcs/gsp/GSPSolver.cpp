// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/GSPSolver.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-26 10:31:26
// Modified: 2017-03-01 01:56:19

#include <cstddef>
#include "GSPSolver.hpp"
#include "GSPCanonicalGA.hpp"

namespace gsp {

template <>
void
Solver<gsp::CanonicalGA>::init_algorithm()
{
    _algorithm =
        std::make_unique<gsp::CanonicalGA>(_pop_size, _prob_rep, _prob_mut);
}

template <>
GraphRep
Solver<gsp::CanonicalGA>::solve()
{
    GraphRep    result;

    init_algorithm();
    (*_algorithm)();
    return result;
}

}

