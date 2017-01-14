// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/GACHC.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:53:53
// Modified: 2017-01-14 01:08:47

#ifndef GACHC_H
#define GACHC_H

#include "TraditionalGA.hpp"

namespace ga {

template <typename CandidateType>
class GACHC : public TraditionalGA<CandidateType>
{
    public:
        GACHC() : TraditionalGA<CandidateType>(10) // TODO
        {}
};

}

#endif /* end of include guard: GACHC_H */
