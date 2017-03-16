// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/utils/containers.h
// Purpose:  TODO (a one-line explanation)
// Created:  2017-03-15 17:25:01
// Modified: 2017-03-15 17:32:15

#include <iterator>

namespace utils {

template <typename T>
size_t
get_index(T const& container, typename T::iterator const& it)
{
    return std::distance(container.begin(), it);
}

template <typename T>
size_t
get_index(T const& container, typename T::const_iterator const& it)
{
    return std::distance(container.begin(), it);
}

}
