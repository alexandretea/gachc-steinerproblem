// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/IStringRepresentation.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-19 16:41:41
// Modified: 2017-01-19 16:47:57

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

std::ostream&
operator<<(std::ostream& s, IStringRepresentation const& o)
{
    return (s << o.to_string());
}

}


#endif /* end of include guard: ISTRINGREPRESENTATION_H */
