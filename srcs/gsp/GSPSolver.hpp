// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/GSPSolver.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-24 12:33:08
// Modified: 2017-02-22 00:38:15

#ifndef GSPSOLVER_H
#define GSPSOLVER_H

#include <iostream>
#include <memory>
#include <vector>
#include "CanonicalGA.hpp"
#include "FixedBinaryString.hpp"
#include "GSPCanonicalGA.hpp"

namespace gsp {

struct Edge
{
    std::string node_a;
    std::string node_b;
};

using GraphRep = std::vector<Edge>;

template <typename GA>
class Solver
{
    public:
        Solver(GraphRep const& graph)
            : _initial_graph(graph), _algorithm(nullptr)
        {
        }

        ~Solver()
        {
        }

        Solver(Solver const& other) = delete;
        Solver&     operator=(Solver const& other) = delete;

    public:
        // TODO init which use make_unique
        GraphRep    solve();

    protected:
        GraphRep                _initial_graph;
        std::unique_ptr<GA>     _algorithm;
};

// Class 'Solver' Specialisations
template <>
GraphRep
Solver<gsp::CanonicalGA>::solve();

}

#endif /* end of include guard: GSPSOLVER_H */
