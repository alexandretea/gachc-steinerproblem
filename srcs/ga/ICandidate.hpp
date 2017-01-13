// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/ICandidate.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-10 05:29:01
// Modified: 2017-01-13 18:33:01

#ifndef ICANDIDATE_H
#define ICANDIDATE_H

namespace ga {

class ICandidate
{
    public:
        virtual int getFitnessScore() = 0;
};

}


#endif /* end of include guard: ICANDIDATE_H */
