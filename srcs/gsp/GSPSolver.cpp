// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/GSPSolver.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-26 10:31:26
// Modified: 2017-02-22 00:36:52

#include <cstddef>
#include "GSPSolver.hpp"
#include "GSPCanonicalGA.hpp"

namespace gsp {

template <>
GraphRep
Solver<gsp::CanonicalGA>::solve()
{
    GraphRep    result;

    std::cout << "ZOBB" << std::endl;
    return result;
}

}

