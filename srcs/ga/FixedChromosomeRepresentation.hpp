// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/FixedChromosomeRepresentation.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-15 20:57:05
// Modified: 2017-01-20 13:00:49

#ifndef FIXEDCHROMOSOMEREPRESENTATION_H
#define FIXEDCHROMOSOMEREPRESENTATION_H

#include <cstddef>
#include <bitset>
#include <utility>
#include "random.hpp"
#include "IStringRepresentation.hpp"

namespace ga {

template <std::size_t S>
class FixedChromosomeRepresentation : public utils::IStringRepresentation
{
    public:
        FixedChromosomeRepresentation()
        {
        }

        FixedChromosomeRepresentation(std::bitset<S> const& bitset)
            : _rep(bitset)
        {
        }

        virtual
        ~FixedChromosomeRepresentation()
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
        crossover_singlepoint(FixedChromosomeRepresentation<S> const& rhs) const
        {
            FixedChromosomeRepresentation<S>    child_a;
            FixedChromosomeRepresentation<S>    child_b;
            unsigned int                        point =
                utils::generateIntegerNumber<unsigned int>(1, S - 1);
            // crossover is ineffective if point is 0 or S - 1

            for (unsigned int i = 0; i < S; ++i) {
                if (i < point) {
                    child_a._rep[i] = _rep.test(i);
                    child_b._rep[i] = rhs._rep.test(i);
                } else {
                    child_a._rep[i] = rhs._rep.test(i);
                    child_b._rep[i] = _rep.test(i);
                }
            }
            return std::make_pair(child_a, child_b);
        }

        std::pair<FixedChromosomeRepresentation<S>,
                  FixedChromosomeRepresentation<S>>
        crossover_twopoint(FixedChromosomeRepresentation<S> const& rhs) const
        {
            FixedChromosomeRepresentation<S>    child_a;
            FixedChromosomeRepresentation<S>    child_b;
            unsigned int                        first_point =
                utils::generateIntegerNumber<unsigned int>(1, S - 1);
            unsigned int                        second_point =
                utils::generateIntegerNumber<unsigned int>(1, S - 1);
            // crossover is singlepoint if point is 0 or S

            if (second_point < first_point)
                std::swap(first_point, second_point);
            for (unsigned int i = 0; i < S; ++i) {
                if (i < first_point or i > second_point) {
                    child_a._rep[i] = _rep.test(i);
                    child_b._rep[i] = rhs._rep.test(i);
                } else {
                    child_a._rep[i] = rhs._rep.test(i);
                    child_b._rep[i] = _rep.test(i);
                }
            }
            return std::make_pair(child_a, child_b);
        }

        virtual std::string
        to_string() const
        {
            return _rep.to_string();
        }

    protected:
        std::bitset<S>  _rep;
};

}

#endif /* end of include guard: FIXEDCHROMOSOMEREPRESENTATION_H */
