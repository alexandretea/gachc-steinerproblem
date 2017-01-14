// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/TraditionalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-10 05:40:08
// Modified: 2017-01-14 02:23:36

#ifndef TRADITIONALGA_H
#define TRADITIONALGA_H

#include <vector>
#include "NotImplemented.hpp"
#include "random.hpp"

namespace ga {

// TODO template constraint
//
// IndividualType should implement:
//     - static void generateRandomPopulation(unsigned int p_size,
//                                            std::vector<Candidate>& p)
//     - virtual unsigned int computeFitness(IndividualType const& const)
template <typename IndividualType>
class TraditionalGA
{
    public:
        struct Candidate
        {
            IndividualType  individual;
            unsigned int             fitness;
        };

    protected:  // TraditionalGA cannot be instanciated without being inherited
        TraditionalGA(unsigned int p_size) : _p_size(p_size)
        {
            // set vector capacity to population size as it is fixed
            // used a vector instead of an array so it is reusable when the
            // class is inherited and the algorithm derived
            _population.reserve(p_size);
        }

    public:
        virtual ~TraditionalGA()
        {
        }

        TraditionalGA(TraditionalGA const& other) = delete;
        TraditionalGA& operator=(TraditionalGA const& other) = delete;

    public:
        void
        run()
        {
            IndividualType::generateRandomPopulation(_p_size, _population);
            while (true) {    // TODO put real condition

                // compute fitness of individuals
                for (Candidate& c: _population) {
                    c.fitness = computeFitness(c.individual);
                }
            }
        }

    protected:
        // TODO array of iterators for selected ?
        virtual void
        selection()
        {
            std::vector<Candidate const*>      candidates(_population);

            for (Candidate const& c: _population)
                candidates.push_back(&c);

            for (unsigned int i = 0; i < _nb_selected; ++i) {
                std::vector<unsigned int>   intervals(candidates.size());
                unsigned int                tmp = 0;

                // init intervals
                for (Candidate const& c: _population) {
                    tmp += c.fitness;
                    intervals.push_back(tmp);
                }

                // TODO use generate for interval and found selected with find first blabal
                utils::GenerateIntegerNumber(0, intervals.last());
                // TODO remove selected form candidates and push to selected candidates container
            }
        }

        // functions to implement when inherited
        virtual unsigned int
        computeFitness(IndividualType const&) const
        {
            throw exceptions::NotImplemented("computeFitness()");
        }

    protected:
        std::vector<Candidate>  _population;
        unsigned int            _p_size;
        unsigned int            _nb_selected;
};

} // end namespace ga

#endif /* end of include guard: TRADITIONALGA_H */
