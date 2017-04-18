// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/main.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:35:57
// Modified: 2017-04-18 14:17:01

#include <cstdlib>
#include <iostream>
#include "GSPSolver.hpp"
#include "FixedBinaryString.hpp"
#include "GSPCanonicalGA.hpp"
#include "GSPGraph.hpp"

int
main(int ac, char** av)
{
    if (ac < 2) {
        std::cout << "Usage: " << av[0] << " JSON_GRAPH" << std::endl;
        return EXIT_SUCCESS;
    }
    try {
        gsp::Graph<std::string>       graph;

        graph.load_from_json(av[1]);

        gsp::Solver<gsp::CanonicalGA> gsp_solver(graph);

        gsp_solver.solve();
    } catch (std::exception const& e) {
        std::cerr << "An error occured: " << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
