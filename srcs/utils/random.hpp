// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/random.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-14 01:36:25
// Modified: 2017-03-14 18:13:00

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace utils {

template <typename NumberType,
          typename Distribution,
          typename Generator = std::mt19937>
NumberType
generate_number(NumberType min, NumberType max)
{
    static std::random_device  rd;
    static Generator           mt(rd());
    static Distribution        dist(min, max);

    return dist(mt);
}

// generate number with no decimal point
template <typename IntegerType>
IntegerType
generate_integer_number(IntegerType min, IntegerType max)
{
    return generate_number<IntegerType,
           std::uniform_int_distribution<IntegerType>>(min, max);
}

// generate number with a decimal point
// partially specialised this template function so it can only accept
// doubles and floats
template <typename RealType>
RealType
generate_real_number(RealType min, RealType max);

// generate random bit
template <typename BitType = bool,
          typename Generator = std::mt19937>
BitType
generate_random_bit(double prob = 0.5)
{
    static std::random_device           rd;
    static Generator                    mt(rd());
    static std::bernoulli_distribution  dist(prob);

    return dist(mt);
}

// generate random bitset
template <size_t S>
std::bitset<S>
generate_random_bitset(double prob = 0.5)
{
    std::bitset<S> res;

    for (unsigned int i = 0; i < S; ++i) {
        res[i] = generate_random_bit(prob);
    }
    return res;
}

}

#endif /* end of include guard: RANDOM_H */
