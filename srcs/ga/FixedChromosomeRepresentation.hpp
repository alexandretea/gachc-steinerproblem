// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/FixedChromosomeRepresentation.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-15 20:57:05
// Modified: 2017-01-17 13:45:32

#ifndef FIXEDCHROMOSOMEREPRESENTATION_H
#define FIXEDCHROMOSOMEREPRESENTATION_H

#include <cstddef>
#include <bitset>

namespace ga {

template <std::size_t S>
class FixedChromosomeRepresentation
{
    public:
        FixedChromosomeRepresentation()
        {
        }

        virtual ~FixedChromosomeRepresentation()
        {
        }

    protected:
        std::bitset<S>  _rep;
};

}

#endif /* end of include guard: FIXEDCHROMOSOMEREPRESENTATION_H */
