// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/random.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-02-13 15:11:42
// Modified: 2017-02-13 15:12:16

#include "random.hpp"

namespace utils {

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
