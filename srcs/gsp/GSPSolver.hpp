// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/GSPSolver.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-24 12:33:08
// Modified: 2017-02-13 14:30:39

#ifndef GSPSOLVER_H
#define GSPSOLVER_H

#include <vector>
#include "ClassicalGA.hpp"
#include "FixedBinaryString.hpp"
#include "GSPTGA.hpp"

namespace gsp {

class Solver
{
    public:
        struct Edge
        {
            std::string node_a;
            std::string node_b;
        };

        using GraphRep = std::vector<Edge>;

    public:
        Solver(GraphRep const& graph);
        ~Solver();

        Solver(Solver const& other) = delete;
        Solver&     operator=(Solver const& other) = delete;

    public:
        template <typename GA>
        GraphRep    solve();

    protected:
        GraphRep    _initial_graph;
};

}

#endif /* end of include guard: GSPSOLVER_H */
