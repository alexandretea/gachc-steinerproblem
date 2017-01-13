// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/main.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:35:57
// Modified: 2017-01-13 18:56:03

#include <cstdlib>
#include <iostream>
#include "GACHC.hpp"

int     main(int /*ac*/, char** /*av*/)
{
    ga::GACHC<std::string>   ga;

    try {
        ga.evaluateFitness("ZOBB");
    }
    catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
