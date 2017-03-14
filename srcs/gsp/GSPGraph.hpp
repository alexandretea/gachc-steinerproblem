// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/Edge.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-03-05 14:53:28
// Modified: 2017-03-14 16:02:15

#ifndef GSPGRAPH_HPP_
#define GSPGRAPH_HPP_

#include <functional>
#include <vector>
#include <stdexcept>
#include <utility>
#include <map>
#include <unordered_map>
#include <fstream>
#include "vendors/json.hpp"

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
            bool    operator<(Node const& rhs) const { return id < rhs.id;  }
        };

        using NodePair = std::pair<Node, Node>;

        struct NodePairHasher
        {
            size_t
            operator()(NodePair const& path) const
            {
                std::hash<std::string> hasher;

                return hasher(id_to_string(path.first.id)
                              + id_to_string(path.second.id));
            }
        };

        using EdgeContainer = std::map<NodePair, unsigned int>;
        // Needs to be ordered as it will be represented as FixedBinaryString
        using PathReqs =
            std::unordered_map<NodePair, unsigned int, NodePairHasher>;
        // TODO see usage and check if std::map would be better

    /*
    ** Constructors/Destructor
    */
    public:
        Graph()
        {
        }

        ~Graph()
        {
        }

        Graph(Graph<IDType> const& other)
            : _nodes(other._nodes), _edges(other._edges),
              _pathreqs(other._pathreqs)
        {
        }

        Graph<IDType>&
        operator=(Graph<IDType>const& other)
        {
            if (&other != this) {
                _nodes(other._nodes);
                _edges(other.edges);
                _pathreqs(other._pathreqs);
            }
            return *this;
        }

    /*
    ** Public member functions
    */
    public:
        void
        load_from_json(std::istream& json_stream)
        {
            nlohmann::json j;

            json_stream >> j;
            for (auto id: j["nodes"]["steiner"])
                add_node(Node::STEINER, id.get<IDType>());
            for (auto id: j["nodes"]["terminal"])
                add_node(Node::TERMINAL, id.get<IDType>());
            for (auto edge: j["edges"])
                add_edge(edge["src"].get<IDType>(),
                         edge["dest"].get<IDType>(),
                         edge["cost"].get<unsigned int>());
            for (auto pathreq: j["requirements"])
                add_path_requirement(pathreq["src"].get<IDType>(),
                                     pathreq["dest"].get<IDType>(),
                                     pathreq["min"].get<unsigned int>());
        }

        void
        load_from_json(std::string const& json_filepath)
        {
            std::ifstream   jsonstream(json_filepath);

            load_from_json(jsonstream);
        }

        Node const*
        add_node(typename Node::Type type, IDType const& id)
        {
            // TODO check duplicate? unordered_map?
            _nodes.push_back({ id, type });
            return &_nodes.back();
        }

        void
        add_edge(IDType const& src_id, IDType const& dest_id, unsigned int cost)
        {
            Node&       src = get_node(src_id);
            Node&       dest = get_node(dest_id);
            NodePair    p = std::make_pair(src, dest);
            NodePair    reverse = std::make_pair(dest, src);
            auto        it = _edges.find(reverse);

            if (it != _edges.end()) {
                it->second = cost;
            } else {
                _edges[p] = cost;
            }
            _total_cost += cost;
        }

        void
        add_path_requirement(IDType const& id_a, IDType const& id_b,
                             unsigned int min_paths)
        {
            Node&       node_a = get_node(id_a);
            Node&       node_b = get_node(id_b);
            NodePair    p = std::make_pair(node_a, node_b);
            NodePair    reverse = std::make_pair(node_b, node_a);
            auto        it = _pathreqs.find(reverse);

            if (it != _pathreqs.end()) {
                it->second = min_paths;
            } else {
                _pathreqs[p] = min_paths;
            }
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

        unsigned int
        get_pathreq(IDType const& id_a, IDType const& id_b) const
        {
            Node&   node_a = get_node(id_a);
            Node&   node_b = get_node(id_b);
            NodePair    p = std::make_pair(node_a, node_b);
            auto    it = _pathreqs.find(p);

            if (it == _pathreqs.end()) {
                p = std::make_pair(node_b, node_a);
                if ((it = _pathreqs.find(p)) == _pathreqs.end())
                    throw std::runtime_error("Path " + id_to_string(id_a)
                                             + "-" + id_to_string(id_b)
                                             + " was not found");
            }
            return it->second;
        }

        unsigned int
        get_total_cost() const
        {
            return _total_cost;
        }

        /*
        ** Iterator getters
        ** begin()/end() makes the class Graph iterable on its nodes
        ** e.g.     for (auto node: graph) { ... }
        */
        typename std::vector<Node>::const_iterator
        begin() const
        {
            return _nodes.begin();
        }

        typename std::vector<Node>::const_iterator
        end() const
        {
            return _nodes.end();
        }

        typename EdgeContainer::const_iterator
        edges_begin() const
        {
            return _edges.begin();
        }

        typename EdgeContainer::const_iterator
        edges_end() const
        {
            return _edges.end();
        }

        typename PathReqs::const_iterator
        pathreqs_begin() const
        {
            return _pathreqs.begin();
        }

        typename PathReqs::const_iterator
        pathreqs_end() const
        {
            return _pathreqs.end();
        }

        static std::string
        id_to_string(IDType const& id) // TODO only use to_string?
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

            if (node == _nodes.end())
                throw std::runtime_error("Node " + id_to_string(id)
                                         + " was not found");
            return *node;
        }

    protected:
        std::vector<Node>       _nodes;
        EdgeContainer           _edges;
        PathReqs                _pathreqs;
        unsigned int            _total_cost;
};

template <>
std::string
Graph<std::string>::id_to_string(std::string const& id)
{
    return id;
}

}

#endif /* end of include guard: GSPGRAPH_HPP_ */
