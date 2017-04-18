// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/ga/FixedBinaryString.cpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-02-13 14:11:43
// Modified: 2017-04-18 14:11:30

#include <iostream>
#include <bitset>
#include "FixedBinaryString.hpp"

namespace ga {

FixedBinaryString::FixedBinaryString() : _rep_size(0)
{
}

FixedBinaryString::FixedBinaryString(size_t s) : _rep_size(s), _rep(s)
{
}

FixedBinaryString::FixedBinaryString(DynamicBitset const& bitset)
    : _rep_size(bitset.size()), _rep(bitset)
{
}

FixedBinaryString::~FixedBinaryString()
{
}

FixedBinaryString::FixedBinaryString(FixedBinaryString const& o)
    : _rep_size(o._rep_size), _rep(o._rep)
{
}

FixedBinaryString&
FixedBinaryString::operator=(FixedBinaryString const& o)
{
    if (&o != this) {
        _rep_size = o._rep_size;
        _rep = o._rep;
    }
    return *this;
}

void
FixedBinaryString::flip(unsigned int index)
{
    _rep.at(index) = !_rep.at(index);
}

bool
FixedBinaryString::test(unsigned int index) const
{
    return _rep.at(index);
}

bool
FixedBinaryString::operator[](unsigned int index) const
{
    return _rep.at(index);
}

size_t
FixedBinaryString::size() const
{
    return _rep_size;
}

FixedBinaryString::ChildPair
FixedBinaryString::crossover_singlepoint(FixedBinaryString const& rhs) const
{
    FixedBinaryString   child_a(_rep_size);
    FixedBinaryString   child_b(_rep_size);
    unsigned int        point =
        utils::generate_integer_number<unsigned int>(1, _rep_size - 1);
    // crossover is ineffective if point is 0 or _rep_size - 1

    for (unsigned int i = 0; i < _rep_size; ++i) {
        if (i < point) {
            child_a._rep[i] = _rep[i];
            child_b._rep[i] = rhs._rep[i];
        } else {
            child_a._rep[i] = rhs._rep[i];
            child_b._rep[i] = _rep[i];
        }
    }
    return std::make_pair(child_a, child_b);
}

FixedBinaryString::ChildPair
FixedBinaryString::crossover_twopoint(FixedBinaryString const& rhs) const
{
    FixedBinaryString   child_a(_rep_size);
    FixedBinaryString   child_b(_rep_size);
    unsigned int        first_point =
        utils::generate_integer_number<unsigned int>(1, _rep_size - 1);
    unsigned int        second_point =
        utils::generate_integer_number<unsigned int>(1, _rep_size - 1);
    // crossover is singlepoint if point is 0 or S

    if (second_point < first_point)
        std::swap(first_point, second_point);
    for (unsigned int i = 0; i < _rep_size; ++i) {
        if (i < first_point or i > second_point) {
            child_a._rep[i] = _rep[i];
            child_b._rep[i] = rhs._rep[i];
        } else {
            child_a._rep[i] = rhs._rep[i];
            child_b._rep[i] = _rep[i];
        }
    }
    return std::make_pair(child_a, child_b);
}

void
FixedBinaryString::flip_all()
{
    _rep.flip();
}

void
FixedBinaryString::flip_random()
{
    for (auto bit: _rep) {
        if (utils::generate_integer_number<unsigned int>(1, _rep_size) == 1) {
            bit = !bit;
        }
    }
}

FixedBinaryString
FixedBinaryString::random(const size_t size)
{
    FixedBinaryString   res(size);

    for (auto bit: res) {
        bit = utils::generate_random_bit();
    }
    return res;
}

std::string
FixedBinaryString::to_string() const // TODO use std::to_string()
{
    std::string res;

    for (bool bit: _rep)
        res += (bit ? "1" : "0");
    return res;
}

FixedBinaryString::DynamicBitset::const_iterator
FixedBinaryString::begin() const
{
    return _rep.begin();
}

FixedBinaryString::DynamicBitset::const_iterator
FixedBinaryString::end() const
{
    return _rep.end();
}

FixedBinaryString::DynamicBitset::iterator
FixedBinaryString::begin()
{
    return _rep.begin();
}

FixedBinaryString::DynamicBitset::iterator
FixedBinaryString::end()
{
    return _rep.end();
}

}
