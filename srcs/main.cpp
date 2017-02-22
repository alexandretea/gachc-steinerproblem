// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/main.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:35:57
// Modified: 2017-02-22 00:31:17

#include <cstdlib>
#include <iostream>
#include "GSPSolver.hpp"
#include "FixedBinaryString.hpp"
#include "GSPCanonicalGA.hpp"

int
main(int /*ac*/, char** /*av*/)
{
    gsp::GraphRep   graph;
    gsp::Solver<gsp::CanonicalGA> gsp_solver(graph);

    try {
    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
