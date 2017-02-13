// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/GSPTGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-20 13:21:03
// Modified: 2017-02-13 15:34:46

#ifndef GSPTGA_H
#define GSPTGA_H

#include "ClassicalGA.hpp"
#include "FixedBinaryString.hpp"

namespace gsp {

class GSPTGA : public ga::ClassicalGA<ga::FixedBinaryString>
{
    public:
        using CandidateSolution = ga::FixedBinaryString;
        using TGA = ga::ClassicalGA<CandidateSolution>;

    public:
        GSPTGA(unsigned int p_size,
               typename TGA::ReproductionOperator const& rep_op,
               unsigned int p_rep,
               typename TGA::MutationOperator const& mut_op,
               unsigned int p_mut)
            : TGA(p_size, rep_op, p_rep, mut_op, p_mut)
        {
        }

        virtual ~GSPTGA()
        {
        }

        GSPTGA(GSPTGA const& other) = delete;
        GSPTGA& operator=(GSPTGA const& other) = delete;

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

#endif /* end of include guard: GSPTGA_H */
