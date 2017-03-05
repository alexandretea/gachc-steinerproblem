// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/Edge.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-03-05 14:53:28
// Modified: 2017-03-05 16:30:58

#ifndef GSPGRAPH_HPP_
#define GSPGRAPH_HPP_

#include <vector>
#include <stdexcept>

namespace gsp {

template <typename IDType>
class Graph
{
    public:
        struct Node
        {
            enum Type
            {
                TERMINAL,   // final destinations
                STEINER     // intermediate nodes
            };

            IDType  id;
            Type    type;
        };

        struct Edge
        {
            Node&           src;
            Node&           dest;
            unsigned int    cost;
        };

        using EdgeContainer = std::vector<const Edge>;

    public:
        Node const*
        add_node(typename Node::Type type, IDType const& id)
        {
            _nodes.push_back({ id, type });
            return &_nodes.back();
        }

        void
        add_edge(IDType const& src_id, IDType const& dest_id, unsigned int cost)
        {
            auto src = std::find_if(_nodes.begin(), _nodes.end(),
                                    [&src_id](Node const& node)
                                    { return node.id == src_id; });
            auto dest = std::find_if(_nodes.begin(), _nodes.end(),
                                     [&dest_id](Node const& node)
                                     { return node.id == dest_id; });

            if (src == _edges.end() or dest == _edges.end())
                throw std::runtime_error("Can't add edge because of "
                                         "unknown node");
            _edges.push_back({ *src, *dest, cost });
        }

        // TODO remove functions

        EdgeContainer const&
        get_edges() const
        {
            return _edges;
        }

    protected:
        std::vector<const Node>     _nodes;
        EdgeContainer               _edges;
};

}

#endif /* end of include guard: GSPGRAPH_HPP_ */
