// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/CanonicalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-20 13:21:03
// Modified: 2017-03-14 18:15:10

#ifndef GSPCANONICALGA_HPP_
#define GSPCANONICALGA_HPP_

#include <string>
#include "CanonicalGA.hpp"
#include "FixedBinaryString.hpp"
#include "GSPGraph.hpp"

namespace gsp {

template <typename NodeIdType = std::string>
class CanonicalGA : public ga::CanonicalGA<ga::FixedBinaryString>
{
    public:
        using CandidateSolution = ga::FixedBinaryString;
        using TGA = ga::CanonicalGA<CandidateSolution>;

    public:
        CanonicalGA(gsp::Graph<NodeIdType> const& graph,
                    unsigned int nb_cycles,
                    unsigned int p_size,
                    typename TGA::ReproductionOperator const& rep_op,
                    unsigned int p_rep,
                    typename TGA::MutationOperator const& mut_op,
                    unsigned int p_mut,
                    bool debug = false)
            : TGA(p_size, rep_op, p_rep, mut_op, p_mut),
              _initial_graph(graph), _nb_cycles(nb_cycles), _current_cycle(0),
              _debug(debug)
        {
        }

        CanonicalGA(gsp::Graph<NodeIdType> const& graph,
                    unsigned int nb_cycles,
                    unsigned int p_size, unsigned int p_rep, unsigned int p_mut,
                    bool debug = false)
            : TGA(p_size, &CandidateSolution::crossover_twopoint, p_rep,
                  &CandidateSolution::flip_random, p_mut),
              _initial_graph(graph), _nb_cycles(nb_cycles), _current_cycle(0),
              _debug(debug)
        {
        }

        virtual ~CanonicalGA()
        {
        }

        CanonicalGA(CanonicalGA const& other) = delete;
        CanonicalGA& operator=(CanonicalGA const& other) = delete;

    public:
        virtual unsigned int
        compute_fitness(CandidateSolution const& c) const
        {
            unsigned int idx = 0;
            unsigned int total_cost = 0;

            for (auto it = _initial_graph.edges_begin();
                 it != _initial_graph.edges_begin();
                 ++it) {

                if (c[idx])
                    total_cost += it->second;
                ++idx;
            }
            if (_initial_graph.get_total_cost() < total_cost)
                throw std::runtime_error("Initial graph cost is smaller than "
                                         "candidate cost");
            return _initial_graph.get_total_cost() - total_cost;
        }

        virtual bool
        should_run() const
        {
            return _current_cycle < _nb_cycles;
        }

        virtual CandidateSolution
        generate_random_individual() const
        {
            return CandidateSolution::random(
                        _initial_graph.get_nb_edges()
                    );
        }

        virtual void
        hook_cycle_end()
        {
            std::cout << "[debug] Cycle #" << _current_cycle
                      << "\t" << _population.size() << std::endl;
            ++_current_cycle;
        }

        // TODO feasibility check for terminal node requirements!!!

    protected:
        gsp::Graph<NodeIdType>  _initial_graph;
        unsigned int            _nb_cycles;
        unsigned int            _current_cycle;
        bool                    _debug;
};

}

#endif /* end of include guard: GSPCANONICALGA_HPP_ */
