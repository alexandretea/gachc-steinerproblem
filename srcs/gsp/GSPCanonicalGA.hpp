// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/CanonicalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-20 13:21:03
// Modified: 2017-03-05 16:31:06

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
        using EdgeContainer = typename gsp::Graph<NodeIdType>::EdgeContainer;
        using CandidateSolution = ga::FixedBinaryString;
        using TGA = ga::CanonicalGA<CandidateSolution>;

    public:
        CanonicalGA(unsigned int p_size,
                    typename TGA::ReproductionOperator const& rep_op,
                    unsigned int p_rep,
                    typename TGA::MutationOperator const& mut_op,
                    unsigned int p_mut)
            : TGA(p_size, rep_op, p_rep, mut_op, p_mut)
        {
        }

        CanonicalGA(unsigned int p_size, unsigned int p_rep, unsigned int p_mut)
            : TGA(p_size, &CandidateSolution::crossover_twopoint, p_rep,
                  &CandidateSolution::flip_random, p_mut)
        {
        }

        virtual ~CanonicalGA()
        {
        }

        CanonicalGA(CanonicalGA const& other) = delete;
        CanonicalGA& operator=(CanonicalGA const& other) = delete;

    public:
        virtual unsigned int
        compute_fitness(CandidateSolution const&) const
        {
            return 0; // TODO
        }

        virtual bool
        should_run() const
        {
            return true; // TODO
        }

        // TODO feasibility check for terminal node requirements!!!

    protected:
        EdgeContainer   _original_graph;
};

}

#endif /* end of include guard: GSPCANONICALGA_HPP_ */
