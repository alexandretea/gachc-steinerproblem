// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/GSPSolver.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-24 12:33:08
// Modified: 2017-03-01 01:54:47

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
        // TODO probabilities to floats ?
        Solver(GraphRep const& graph, unsigned int pop_size = 120,
               unsigned int prob_mut = 1, unsigned int prob_rep = 90)
            : _initial_graph(graph), _algorithm(nullptr), _pop_size(pop_size),
              _prob_mut(prob_mut), _prob_rep(prob_rep)
        {
        }

        ~Solver()
        {
        }

        Solver(Solver const& other) = delete;
        Solver&     operator=(Solver const& other) = delete;

    public:
        GraphRep    solve();            // need to be specialised

    protected:
        void        init_algorithm();   // need to be specialised

    protected:
        GraphRep                _initial_graph;
        std::unique_ptr<GA>     _algorithm;

        // algorithm parameters
        unsigned int    _pop_size;  // population size
        unsigned int    _prob_mut;  // probability of mutation
        unsigned int    _prob_rep;  // probability of reproduction
};

// Class 'Solver' Specialisations
template <>
void        Solver<gsp::CanonicalGA>::init_algorithm();
template <>
GraphRep    Solver<gsp::CanonicalGA>::solve();

}

#endif /* end of include guard: GSPSOLVER_H */
