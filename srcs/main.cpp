// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/main.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:35:57
// Modified: 2017-02-13 15:53:00

#include <cstdlib>
#include <iostream>
#include "GSPSolver.hpp"
#include "FixedBinaryString.hpp"

int
main(int /*ac*/, char** /*av*/)
{
    //gsp::Solver::GraphRep   graph;
    //gsp::Solver gsp_solver(graph);
    ga::FixedBinaryString dad({ true, true, false, true, false, false });
    ga::FixedBinaryString mom({ false, true, false, false, false, true });

    try {
        ga::FixedBinaryString::ChildPair children = dad.crossover_twopoint(mom);

        std::cout << dad << "\t" << mom << std::endl;
        std::cout << children.first << "\t" << children.second << std::endl;
    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
