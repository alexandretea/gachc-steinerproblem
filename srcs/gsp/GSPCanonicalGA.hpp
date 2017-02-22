// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/CanonicalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-20 13:21:03
// Modified: 2017-02-21 23:46:15

#ifndef GSPCANONICALGA_HPP_
#define GSPCANONICALGA_HPP_

#include "CanonicalGA.hpp"
#include "FixedBinaryString.hpp"

namespace gsp {

class CanonicalGA : public ga::CanonicalGA<ga::FixedBinaryString>
{
    public:
        using CandidateSolution = ga::FixedBinaryString;
        using TGA = ga::CanonicalGA<CandidateSolution>;

    public:
        // TODO let user choose reproduction operator or ..?
        // OR MULTIPLE CONSTRUCTORS OR DEFAULT VALUE
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
                  &CandidateSolution::flip_random, p_mut) // TODO flipRandom>
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
            return 0;
        }

        virtual bool
        should_run() const
        {
            return true;
        }
};

}

#endif /* end of include guard: GSPCANONICALGA_HPP_ */
