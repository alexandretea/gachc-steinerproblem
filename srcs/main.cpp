// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/main.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:35:57
// Modified: 2017-01-17 13:10:24

#include <cstdlib>
#include <iostream>
#include "GACHC.hpp"
#include "FixedChromosomeRepresentation.hpp"

int
main(int /*ac*/, char** /*av*/)
{
    ga::GACHC<ga::FixedChromosomeRepresentation<10>>   ga;

    try {
    } catch (std::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
