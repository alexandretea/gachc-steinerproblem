// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/TraditionalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-10 05:40:08
// Modified: 2017-01-14 22:06:11

#ifndef TRADITIONALGA_H
#define TRADITIONALGA_H

#include <algorithm>
#include <list>
#include <vector>
#include "NotImplemented.hpp"
#include "random.hpp"

namespace ga {

// TODO template constraint
//
// IndividualType should implement:
//     - static void generateRandomPopulation(unsigned int p_size,
//                                            std::vector<Candidate>& p)
//     - virtual unsigned int compute_fitness(IndividualType const& const)
template <typename IndividualType>
class TraditionalGA
{
    public:
        struct Candidate
        {
            IndividualType  individual;
            unsigned int    fitness;
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
                    c.fitness = compute_fitness(c.individual);
                }
            }
        }

    protected:
        // TODO array of iterators for selected ?
        virtual void
        selection(std::vector<Candidate*>& selected_candidates)
        {
            std::list<Candidate*>   candidates(_population.size());
            // std::list because deletion is more efficient

            if (_population.empty())
                return ; // TODO throw exception ?

            for (Candidate& c: _population)
                candidates.push_back(&c);

            for (unsigned int i = 0;
                 i < _nb_selected && !candidates.empty();
                 ++i) {

                unsigned int total_fitnesses = std::accumulate(
                        candidates.begin(), candidates.end(), 0,
                        [](unsigned int sum, Candidate const* c)
                        { return sum += c->fitness; }
                    );
                unsigned int random_value =
                    utils::generateIntegerNumber<unsigned int>(
                        0, total_fitnesses
                    );
                unsigned int tmp = 0;
                auto selected = std::find_if(
                    candidates.begin(), candidates.end(),
                    [&tmp, random_value](Candidate* c)
                    {
                        tmp += c->fitness;
                        return random_value <= tmp;
                    }
                );

                selected_candidates.push_back(*selected);
                candidates.erase(selected);
            }
        }

        // functions to implement when inherited
        virtual unsigned int
        compute_fitness(IndividualType const&) const
        {
            throw exceptions::NotImplemented("compute_fitness()");
        }

    protected:
        std::vector<Candidate>  _population;
        unsigned int            _p_size;
        unsigned int            _nb_selected;
};

} // end namespace ga

#endif /* end of include guard: TRADITIONALGA_H */
