// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/GSPSolver.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-24 12:33:08
// Modified: 2017-03-14 18:35:42

#ifndef GSPSOLVER_H
#define GSPSOLVER_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "CanonicalGA.hpp"
#include "FixedBinaryString.hpp"
#include "GSPCanonicalGA.hpp"
#include "GSPGraph.hpp"

namespace gsp {

// T_GA is a class template of a functor
template <template<typename> class T_GA>
class Solver
{
    public:
        using NodeID = std::string;
        using EdgeContainer = typename gsp::Graph<NodeID>::EdgeContainer;
        using CandidateSolution = ga::FixedBinaryString;

    public:
        // TODO probabilities to floats ?
        Solver(gsp::Graph<NodeID> const& graph, unsigned int pop_size = 120,
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
        Graph<NodeID>
        solve()
        {
            Graph<NodeID>       result;
            CandidateSolution   solution;

            // TODO display config
            init_algorithm();
            solution = (*_algorithm)();
            std::cout << "Solution: " << solution.to_string() << std::endl;
            // TODO translate to graph
            return result;
        }

    protected:
        virtual void
        init_algorithm()
        {
            _algorithm = std::make_unique<T_GA<NodeID>>(
                    _initial_graph,
                    1000, // TODO
                    _pop_size, _prob_rep, _prob_mut,
                    true // TODO
                );
        }

    protected:
        Graph<NodeID>                   _initial_graph;
        std::unique_ptr<T_GA<NodeID>>   _algorithm;

        // algorithm parameters
        unsigned int    _pop_size;  // population size
        unsigned int    _prob_mut;  // probability of mutation
        unsigned int    _prob_rep;  // probability of reproduction
};

}

#endif /* end of include guard: GSPSOLVER_H */
