// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/random.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-14 01:36:25
// Modified: 2017-01-17 14:57:47

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace utils {

template <typename NumberType,
          typename Distribution,
          typename Generator = std::mt19937>
NumberType
generateNumber(NumberType min, NumberType max)
{
    static std::random_device  rd;
    static Generator           mt(rd());
    static Distribution        dist(min, max);

    return dist(mt);
}

// generate number with no decimal point
template <typename IntegerType>
IntegerType
generateIntegerNumber(IntegerType min, IntegerType max)
{
    return generateNumber<IntegerType,
           std::uniform_int_distribution<IntegerType>>(min, max);
}

// generate number with a decimal point
// partially specialised this template function so it can only accept
// doubles and floats
template <typename RealType>
RealType
generateRealNumber(RealType min, RealType max);

template <>
double
generateRealNumber(double min, double max)
{
    return generateNumber<double,
           std::uniform_real_distribution<double>>(min, max);
}

template <>
float
generateRealNumber(float min, float max)
{
    return generateNumber<float,
           std::uniform_real_distribution<float>>(min, max);
}

}

#endif /* end of include guard: RANDOM_H */
