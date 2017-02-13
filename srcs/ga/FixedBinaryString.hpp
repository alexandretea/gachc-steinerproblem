// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/FixedBinaryString.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-01-15 20:57:05
// Modified: 2017-02-13 15:40:38

#ifndef FIXEDBINARYSTRING_H
#define FIXEDBINARYSTRING_H

#include <cstddef>
#include <vector>
#include <utility>
#include "random.hpp"
#include "IStringRepresentation.hpp"

namespace ga {

// TODO assert _rep_size is the same when operations between two instances
class FixedBinaryString : public utils::IStringRepresentation
{
    public:
        using DynamicBitset = std::vector<bool>; // will store values as bits
        using ChildPair = std::pair<FixedBinaryString,
                                    FixedBinaryString>;

    public:
        FixedBinaryString();
        FixedBinaryString(size_t s);
        FixedBinaryString(DynamicBitset const& bitset);
        virtual ~FixedBinaryString();

        FixedBinaryString(FixedBinaryString const& o);
        FixedBinaryString& operator=(FixedBinaryString const& o);

    public:
        void        flip(unsigned int index);
        bool        test(unsigned int index) const;
        bool&       operator[](unsigned int index);

        ChildPair   crossover_singlepoint(FixedBinaryString const& rhs) const;
        ChildPair   crossover_twopoint(FixedBinaryString const& rhs) const;

    public:
        virtual std::string         to_string() const;
        static FixedBinaryString    generateRandom();

    protected:
        size_t          _rep_size;
        DynamicBitset   _rep;
};

std::ostream&
operator<<(std::ostream& s, utils::IStringRepresentation const& o);

}

#endif /* end of include guard: FIXEDBINARYSTRING_H */
