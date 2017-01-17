// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/GACHC.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:53:53
// Modified: 2017-01-17 14:13:52

#ifndef GACHC_H
#define GACHC_H

#include "TraditionalGA.hpp"

namespace ga {

template <typename IndividualType>
class GACHC : public TraditionalGA<IndividualType>
{
    public:
        GACHC() : TraditionalGA<IndividualType>(10) // TODO
        {}

        virtual unsigned int
        compute_fitness(IndividualType const&) const { return 0; }
        virtual bool should_run() const { return true; }
};

}

#endif /* end of include guard: GACHC_H */
