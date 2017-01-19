// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/FixedChromosomeRepresentation.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-15 20:57:05
// Modified: 2017-01-19 10:57:26

#ifndef FIXEDCHROMOSOMEREPRESENTATION_H
#define FIXEDCHROMOSOMEREPRESENTATION_H

#include <cstddef>
#include <bitset>
#include <utility>
#include "random.hpp"

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

        FixedChromosomeRepresentation(FixedChromosomeRepresentation<S> const& o)
            : _rep(o._rep)
        {
        }

        FixedChromosomeRepresentation&
        operator=(FixedChromosomeRepresentation const& o)
        {
            if (&o != this) {
                _rep = o._rep;
            }
            return *this;
        }

    public:
        std::pair<FixedChromosomeRepresentation<S>,
                  FixedChromosomeRepresentation<S>>
        crossover_singlepoint(FixedChromosomeRepresentation<S> const& rhs)
        {
            FixedChromosomeRepresentation<S>    child;
            unsigned int                        point =
                utils::generateIntegerNumber<unsigned int>(0, S);

            for (unsigned int i = 0; i < S; ++i) {
                child._rep[i] = (i < point ? _rep[i] : rhs[i]);
            }
            return make_reps_pair(child);
        }

        std::pair<FixedChromosomeRepresentation<S>,
                  FixedChromosomeRepresentation<S>>
        crossover_twopoint(FixedChromosomeRepresentation<S> const& rhs)
        {
            FixedChromosomeRepresentation<S>    child;
            unsigned int                        first_point =
                utils::generateIntegerNumber<unsigned int>(0, S);
            unsigned int                        second_point =
                utils::generateIntegerNumber<unsigned int>(0, S);

            if (second_point < first_point)
                std::swap(first_point, second_point);
            for (unsigned int i = 0; i < S; ++i) {
                child._rep[i] = (i < first_point or i > second_point
                                 ? _rep[i] : rhs[i]);
            }
            return make_reps_pair(child);
        }

        static std::pair<FixedChromosomeRepresentation<S>,
                         FixedChromosomeRepresentation<S>>
        make_reps_pair(FixedChromosomeRepresentation<S> const& rep)
        {
            FixedChromosomeRepresentation<S> other = rep;

            other.flip();
            return std::make_pair(rep, other);
        }

    protected:
        std::bitset<S>  _rep;
};

}

#endif /* end of include guard: FIXEDCHROMOSOMEREPRESENTATION_H */
