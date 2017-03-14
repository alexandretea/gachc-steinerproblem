// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/random.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-02-13 15:11:42
// Modified: 2017-03-14 18:13:28

#include "random.hpp"

namespace utils {

template <>
double
generate_real_number(double min, double max)
{
    return generate_number<double,
           std::uniform_real_distribution<double>>(min, max);
}

template <>
float
generate_real_number(float min, float max)
{
    return generate_number<float,
           std::uniform_real_distribution<float>>(min, max);
}

}
