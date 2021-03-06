// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/CanonicalGA.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-10 05:40:08
// Modified: 2017-04-18 14:32:14

#ifndef CANONICALGA_H
#define CANONICALGA_H

#include <algorithm>
#include <list>
#include <vector>
#include <utility>
#include <stdexcept>
#include "utils/random.hpp"

namespace ga {

// CanonicalGA is a functor
//
// IndividualType should implement:
//     - virtual CandidateSolution generate_random_individual() const
//     - virtual unsigned int compute_fitness(IndividualType const& const)
//
// TODO template constraint
// TODO log
template <typename IndividualType>
class CanonicalGA
{
    public:
        using MutationOperator = void (IndividualType::*)();
        using ReproductionOperator =
            std::pair<IndividualType, IndividualType>
            (IndividualType::*)(IndividualType const& rhs) const;

        struct Candidate
        {
            IndividualType  individual;
            unsigned int    fitness;
        };

    protected:  // CanonicalGA cannot be instanciated without being inherited
        CanonicalGA(unsigned int p_size,
                ReproductionOperator const& rep_op, unsigned int p_rep,
                MutationOperator const& mut_op, unsigned int p_mut)
            : _p_size(p_size),
              _mutation_op(mut_op),_reproduction_op(rep_op),
              _mutation_prob(p_mut), _reproduction_prob(p_rep)
        {
            // set vector capacity to population size as it is fixed
            // used a vector instead of an array so it is reusable when the
            // class is inherited and the algorithm derived
            _population.reserve(p_size);
        }

    public:
        virtual ~CanonicalGA()
        {
        }

        CanonicalGA(CanonicalGA const& other) = delete;
        CanonicalGA&    operator=(CanonicalGA const& other) = delete;

    public:
        IndividualType
        operator()()
        {
            generateRandomPopulation();
            while (should_run()) {
                std::vector<Candidate const*> selected_candidates;
                std::vector<Candidate> new_generation;

                hook_cycle_begin();
                // compute fitness of individuals
                for (Candidate& c: _population) {
                    c.fitness = compute_fitness(c.individual);
                }

                selection_process(selected_candidates);
                create_new_generation(new_generation, selected_candidates);
                _population = new_generation; // TODO useless step through newg?
                hook_cycle_end();
            }

            auto it =
                std::max_element(_population.begin(), _population.end(),
                                 [](Candidate const& a, Candidate const& b)
                                 { return a.fitness < b.fitness; });
            if (it == _population.end())
                throw std::runtime_error("Population is empty");
            return it->individual;
        }

    protected:
        virtual void
        selection_process(std::vector<Candidate const*>& selection) const
        {
            if (_population.empty())
                throw std::runtime_error("Selection procedure failed:"
                                         "Population is empty");

            unsigned int total_fitnesses = std::accumulate(
                    _population.begin(), _population.end(), 0,
                    [](unsigned int sum, Candidate const& c)
                    { return sum += c.fitness; }
                );

            for (unsigned int i = 0; i < _p_size; ++i) {

                unsigned int random_value =
                    utils::generate_integer_number<unsigned int>(
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
        } // TODO check if ok

        virtual void
        create_new_generation(std::vector<Candidate>& new_generation,
                std::vector<Candidate const*> const& selection) const
        {
            // reproduction
            for (auto f = selection.begin(), m = std::next(f);
                 f != selection.end() && m != selection.end();
                 f += 2, m += 2) { // TODO check if ok

                IndividualType const& father = (*f)->individual;
                IndividualType const& mother = (*m)->individual;

                if (utils::generate_integer_number<unsigned int>(0, 100) <
                        _reproduction_prob) {

                    std::pair<IndividualType, IndividualType>   children =
                        (father.*_reproduction_op)(mother);

                    // TODO is individual valid???

                    // reproduce and make two children
                    new_generation.push_back(
                        { children.first, 0 }
                    );
                    new_generation.push_back(
                        { children.second, 0 }
                    );
                } else {
                    // if no reproduction, we keep the parents
                    new_generation.push_back({ father, 0 });
                    new_generation.push_back({ mother, 0 });
                }
            }

            // mutation
            for (Candidate& c: new_generation) {
                if (utils::generate_integer_number<unsigned int>(0, 100) <
                        _mutation_prob) {

                    (c.individual.*_mutation_op)();
                }
            }
        }

        virtual void
        generateRandomPopulation()
        {
            for (unsigned int i = 0; i < _p_size; ++i) {
                _population.push_back({ generate_random_individual(), 0 });
            }
        }

        // hook functions to overload if necessary
        virtual void    hook_cycle_begin()  {}
        virtual void    hook_cycle_end()    {}

        // functions to implement when inherited
        virtual unsigned int compute_fitness(IndividualType const&) const = 0;
        virtual bool should_run() const = 0;
        virtual IndividualType generate_random_individual() const = 0;

    protected:
        std::vector<Candidate>          _population;
        unsigned int                    _p_size;
        //unsigned int                    _no_generation; // TODO useless?
        MutationOperator                _mutation_op;
        ReproductionOperator            _reproduction_op;

        // probabilities as a percentage (ex: 70 for 70% of success)
        unsigned int                    _mutation_prob;
        unsigned int                    _reproduction_prob;
};

} // end namespace ga

#endif /* end of include guard: CANONICALGA_H */
