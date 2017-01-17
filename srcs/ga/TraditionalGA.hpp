// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/TraditionalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-10 05:40:08
// Modified: 2017-01-17 15:50:08

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
        using MutationOperator = void (IndividualType::*)();
        using ReproductionOperator =
            IndividualType (IndividualType::*)(IndividualType const& rhs) const;

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
            while (should_run()) {
                std::vector<Candidate const*> selected_candidates;
                std::vector<Candidate> new_generation;

                // compute fitness of individuals
                for (Candidate& c: _population) {
                    c.fitness = compute_fitness(c.individual);
                }

                selection_process(selected_candidates);
                create_new_generation(new_generation, selected_candidates);
                // TODO return instead of ref to improve performance ?
                _population = new_generation;
            }
        }

    protected:
        virtual void
        selection_process(std::vector<Candidate const*>& selection) const
        {
            if (_population.empty())
                return ; // TODO throw exception ?

            unsigned int total_fitnesses = std::accumulate(
                    _population.begin(), _population.end(), 0,
                    [](unsigned int sum, Candidate const& c)
                    { return sum += c.fitness; }
                );

            for (unsigned int i = 0; i < _p_size; ++i) {

                unsigned int random_value =
                    utils::generateIntegerNumber<unsigned int>(
                        0, total_fitnesses
                    );
                unsigned int tmp = 0;
                auto selected = std::find_if(
                    _population.begin(), _population.end(),
                    [&tmp, random_value](Candidate const& c)
                    {
                        tmp += c.fitness;
                        return random_value <= tmp;
                    }
                );

                selection.push_back(&(*selected));
            }
        }

        virtual void
        create_new_generation(std::vector<Candidate>& new_generation,
                std::vector<Candidate const*> const& selection) const
        {
            // reproduction
            for (auto f = selection.begin(), m = std::next(f);
                 f != selection.end() && m != selection.end();
                 ++f, ++m) {

                IndividualType const& father = (*f)->individual;
                IndividualType const& mother = (*m)->individual;

                if (utils::generateIntegerNumber<unsigned int>(0, 100) <
                        _reproduction_prob) {

                    // reproduce and make two children
                    new_generation.push_back(
                        { (father.*_reproduction_op)(mother), 0 }
                    );
                    new_generation.push_back(
                        { (mother.*_reproduction_op)(father), 0 }
                    );
                }
            }

            // mutation
            for (Candidate& c: new_generation) {
                if (utils::generateIntegerNumber<unsigned int>(0, 100) <
                        _mutation_prob) {

                    (c.individual.*_mutation_op)();
                }
            }
        }

        // functions to implement when inherited
        virtual unsigned int compute_fitness(IndividualType const&) const = 0;
        virtual bool should_run() const = 0;

    protected:
        std::vector<Candidate>          _population;
        unsigned int                    _p_size;
        unsigned int                    _no_generation;
        MutationOperator                _mutation_op;
        ReproductionOperator            _reproduction_op;

        // probabilities as a percentage (ex: 70 for 70% of success)
        unsigned int                    _mutation_prob;
        unsigned int                    _reproduction_prob;
};

} // end namespace ga

#endif /* end of include guard: TRADITIONALGA_H */
