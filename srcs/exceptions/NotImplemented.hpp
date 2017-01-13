// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/exceptions/NotImplemented.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-13 18:15:41
// Modified: 2017-01-13 18:42:15

#ifndef NOTIMPLEMENTED_H
#define NOTIMPLEMENTED_H

#include <string>
#include <stdexcept>

namespace exceptions {

class NotImplemented : public std::logic_error
{
    public:
        NotImplemented(std::string const& feature);
        virtual ~NotImplemented() throw();
};

}


#endif /* end of include guard: NOTIMPLEMENTED_H */
