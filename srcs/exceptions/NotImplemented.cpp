// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/exceptions/NotImplemented.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:17:49
// Modified: 2017-01-13 18:42:20

#include <string>
#include <NotImplemented.hpp>

namespace exceptions {

NotImplemented::NotImplemented(std::string const& feature)
    : std::logic_error(feature + " is not implemented.")
{
}

NotImplemented::~NotImplemented() throw()
{
}

}
