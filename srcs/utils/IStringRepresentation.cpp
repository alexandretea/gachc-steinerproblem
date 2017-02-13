// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/IStringRepresentation.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-02-13 15:18:03
// Modified: 2017-02-13 15:40:52

#include "IStringRepresentation.hpp"

namespace ga {

std::ostream&
operator<<(std::ostream& s, utils::IStringRepresentation const& o)
{
    return (s << o.to_string());
}

}
