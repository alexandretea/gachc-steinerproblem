// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/TraditionalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-10 05:40:08
// Modified: 2017-01-13 18:45:10

#ifndef TRADITIONALGA_H
#define TRADITIONALGA_H

#include "NotImplemented.hpp"

namespace ga {

template <typename CandidateType>
class TraditionalGA
{
    public:
        TraditionalGA()
        {
        }

        virtual ~TraditionalGA()
        {
        }

        TraditionalGA(TraditionalGA const& other) = delete;
        TraditionalGA& operator=(TraditionalGA const& other) = delete;

    public:
        virtual int evaluateFitness(CandidateType const&) const
        {
            throw exceptions::NotImplemented("evaluateFitness()");
        }
};

} // end namespace ga

#endif /* end of include guard: TRADITIONALGA_H */
