// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/CHCGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:53:53
// Modified: 2017-02-08 14:59:02

#ifndef CHCGA_H
#define CHCGA_H

#include "ClassicalGA.hpp"

namespace ga {

template <typename IndividualType>
class CHCGA : public ClassicalGA<IndividualType>
{
    public:
        CHCGA() : ClassicalGA<IndividualType>(10) // TODO
        {}

        virtual unsigned int
        compute_fitness(IndividualType const&) const { return 0; }
        virtual bool should_run() const { return true; }
};

}

#endif /* end of include guard: CHCGA_H */
