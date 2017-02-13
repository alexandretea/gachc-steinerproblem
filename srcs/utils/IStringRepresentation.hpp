// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/IStringRepresentation.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-19 16:41:41
// Modified: 2017-02-13 15:18:13

#ifndef ISTRINGREPRESENTATION_H
#define ISTRINGREPRESENTATION_H

#include <sstream>
#include <string>

namespace utils {

class IStringRepresentation
{
    public:
        virtual ~IStringRepresentation() {}
        virtual std::string to_string() const = 0;
};

}


#endif /* end of include guard: ISTRINGREPRESENTATION_H */
