// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/Edge.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-03-05 14:53:28
// Modified: 2017-03-13 18:04:16

#ifndef GSPGRAPH_HPP_
#define GSPGRAPH_HPP_

#include <functional>
#include <vector>
#include <stdexcept>
#include <utility>
#include <unordered_map>

namespace gsp {

template <typename IDType>
class Graph
{
    /*
    ** Data structures
    */
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

            bool    operator==(Node const& rhs) const { return id == rhs.id; }
        };

        struct Edge
        {
            Node&           src;
            Node&           dest;
            unsigned int    cost;
        };

        using EdgeContainer = std::vector<const Edge>;

        // Path data structure
        using Path = std::pair<Node, Node>;

        struct PathHasher
        {
            size_t
            operator()(Path const& path) const
            {
                std::hash<std::string> hasher;

                return hasher(id_to_string(path.first.id)
                              + id_to_string(path.second.id));
            }
        };

        using PathReqs = std::unordered_map<Path, unsigned int, PathHasher>;

    /*
    ** Public member functions
    */
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
            Node&   src = get_node(src_id);
            Node&   dest = get_node(dest_id);

            _edges.push_back({ src, dest, cost });
        }

        void
        add_path_requirement(IDType const& id_a, IDType const& id_b,
                             unsigned int min_paths)
        {
            Node&   node_a = get_node(id_a);
            Node&   node_b = get_node(id_b);
            Path    p = std::make_pair(node_a, node_b);

            _path_requirements[p] = min_paths;
        }

        // TODO removal functions

        EdgeContainer const&
        get_edges() const
        {
            return _edges;
        }

        Node const&
        get_node(IDType const& id) const
        {
            return get_node(id);
        }

        static std::string
        id_to_string(IDType const& id)
        {
            return std::to_string(id);
        }

    /*
    ** Protected member functions
    */
    protected:
        Node&
        get_node(IDType const& id)
        {
            auto node = std::find_if(_nodes.begin(), _nodes.end(),
                                     [&id](Node const& node)
                                     { return node.id == id; });

            if (node == _edges.end())
                throw std::runtime_error("Node " + id_to_string(node.id)
                                         + " was not found");
            return *node;
        }

    protected:
        std::vector<Node>       _nodes;
        EdgeContainer           _edges;
        PathReqs                _path_requirements;
};

template <>
std::string
Graph<std::string>::id_to_string(std::string const& id)
{
    return id;
}

}

#endif /* end of include guard: GSPGRAPH_HPP_ */
