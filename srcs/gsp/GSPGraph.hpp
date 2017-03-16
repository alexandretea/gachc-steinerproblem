// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/Edge.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-03-05 14:53:28
// Modified: 2017-03-16 21:06:02

#ifndef GSPGRAPH_HPP_
#define GSPGRAPH_HPP_

#include <queue>
#include <functional>
#include <vector>
#include <stdexcept>
#include <set>
#include <utility>
#include <map>
#include <unordered_map>
#include <fstream>
#include "vendors/json.hpp"
#include "utils/container.hpp"

namespace gsp {

template <typename IDType>
class Graph // Undirected Graph
{
    /*
    ** Data structures
    */
    public:
        class Node
        {
            public:
                enum Type
                {
                    TERMINAL,   // final destinations
                    STEINER     // intermediate nodes
                };

            public:
                Node() {}
                Node(Type type, IDType const& id)
                    : _id(id), _type(type), _neighbours() {}
                ~Node() {}
                Node(Node const& o)
                    : _id(o._id), _type(o._type), _neighbours(o._neighbours) {}

                Node&
                operator=(Node const& o)
                {
                    if (&o != this) {
                        _id = o._id;
                        _type = o._type;
                        _neighbours = o._neighbours;
                    }
                }

                bool
                operator==(Node const& rhs) const
                {
                    return _id == rhs._id;
                }

                bool
                operator!=(Node const& rhs) const
                {
                    return !operator==(rhs);
                }

                bool
                operator<(Node const& rhs) const
                {
                    return _id < rhs._id;
                }

                void
                add_neighbour(Node const& n, unsigned int cost)
                {
                    _neighbours.emplace(&n, cost);
                } // TODO removal function

                IDType const&   get_id() const      { return _id; }
                Type            get_type() const    { return _type; }

                typename std::map<Node const*, unsigned int>::const_iterator
                begin() const
                {
                    return _neighbours.begin();
                }

                typename std::map<Node const*, unsigned int>::const_iterator
                end() const
                {
                    return _neighbours.end();
                }

            protected:
                IDType  _id;
                Type    _type;

                std::map<Node const*, unsigned int>    _neighbours;
        };

        using NodePair = std::pair<Node const*, Node const*>;

        struct NodePairHasher
        {
            size_t
            operator()(NodePair const& path) const
            {
                std::hash<std::string> hasher;

                return hasher(id_to_string(path.first->get_id())
                              + id_to_string(path.second->get_id()));
            }
        };

        // TODO rename with more explicit name
        using NodeContainer = std::unordered_map<IDType, Node>;
        using EdgeContainer = std::map<NodePair, unsigned int>;
        // Needs to be ordered as it will be represented as FixedBinaryString
        using PathReqs =
            std::unordered_map<NodePair, unsigned int, NodePairHasher>;
        // TODO see usage and check if std::map would be better
        using NodeSet = std::set<Node const*>;
        using NodeList = std::list<Node const*>;
        using VisitedNodes = std::unordered_map<Node const*, NodeSet>;
        //                                      visited node|list of parents

    /*
    ** Constructors/Destructor
    */
    public:
        Graph() : _nodes(), _edges(), _pathreqs(), _total_cost(0)
        {
        }

        ~Graph()
        {
        }

        Graph(Graph<IDType> const& other)
            : _nodes(other._nodes), _edges(other._edges),
              _pathreqs(other._pathreqs), _total_cost(other._total_cost)
        {
        }

        Graph<IDType>&
        operator=(Graph<IDType>const& other)
        {
            if (&other != this) {
                _nodes = other._nodes;
                _edges = other.edges;
                _pathreqs = other._pathreqs;
                _total_cost = other._total_cost;
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

        Node const&
        add_node(typename Node::Type type, IDType const& id)
        {
            // TODO check duplicate? unordered_map?
            auto ret = _nodes.emplace(id, Node(type, id));
            return ret.first->second;
        }

        void
        add_edge(IDType const& src_id, IDType const& dest_id, unsigned int cost)
        {
            Node&       src = _nodes.at(src_id);
            Node&       dest = _nodes.at(dest_id);
            NodePair    p = std::make_pair(&src, &dest);
            NodePair    reverse = std::make_pair(&dest, &src);
            auto        it = _edges.find(reverse);

            if (it != _edges.end()) {
                it->second = cost;
            } else {
                _edges[p] = cost;
            }
            src.add_neighbour(dest, cost);
            dest.add_neighbour(src, cost);
            _total_cost += cost;
        }

        void
        add_path_requirement(IDType const& id_a, IDType const& id_b,
                             unsigned int min_paths)
        {
            Node&       node_a = _nodes.at(id_a);
            Node&       node_b = _nodes.at(id_b);
            NodePair    p = std::make_pair(&node_a, &node_b);
            NodePair    reverse = std::make_pair(&node_b, &node_a);
            // TODO hash fn that gives same hash
            auto        it = _pathreqs.find(reverse);

            if (it != _pathreqs.end()) {
                it->second = min_paths;
            } else {
                _pathreqs[p] = min_paths;
            }
        }

        // TODO removal functions

        // BFS search
        // will find all paths if max_nb paths is 0
        // topology is used to find paths within a reduced-cost graph
        // TODO when find dest, check max_nb_path and stop?
        std::list<NodeList>
        find_all_paths(Node const& src, Node const& dest,
                   unsigned int max_nb_paths = 0,
                   ga::FixedBinaryString const* topology = nullptr) const
        {
            VisitedNodes                visited; // TODO name tpye breadcrumb?
            std::queue<NodePair>        to_visit;

            if (topology != nullptr and _edges.size() != topology->size())
                throw std::runtime_error("Binary string has a different size "
                                         "from edges container ");
            to_visit.emplace(&src, nullptr);
            while (not to_visit.empty()) {
                NodePair current = to_visit.front();

                to_visit.pop();

                if (is_visited_node(visited, current))
                    continue ; // TODO check if actually happen
                for (auto& pair: *current.first) {
                    Node const* neighbour = pair.first;

                    if (topology == nullptr
                        or is_edge_enabled(*current.first,
                                           *neighbour, topology)) {

                        if (*neighbour == dest) { // dest found
                            tag_node_visited(visited, &dest, current.first);
                        } else if (not is_visited_node(visited,
                                                   neighbour, current.first)) {
                            to_visit.emplace(neighbour, current.first);
                        }
                    }
                }
                tag_node_visited(visited, current);
            }
            return bfs_build_paths(src, dest, visited, max_nb_paths);
        }

        std::list<NodeList>
        find_all_paths(IDType const& src_id, IDType const& dest_id,
                   unsigned int max_nb_paths = 0,
                   ga::FixedBinaryString const* topology = nullptr) const
        {
            return find_all_paths(_nodes.at(src_id), _nodes.at(dest_id),
                              max_nb_paths, topology);
        }

        Node const&
        get_node(IDType const& id) const
        {
            return _nodes.at(id);
        }

        unsigned int
        get_pathreq(IDType const& id_a, IDType const& id_b) const
        {
            Node&   node_a = _nodes.at(id_a);
            Node&   node_b = _nodes.at(id_b);
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

        unsigned int
        get_nb_edges() const
        {
            return _edges.size();
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

    protected:
        bool
        is_edge_enabled(Node const& src, Node const& dest,
                        ga::FixedBinaryString const* topology) const
        {
            auto    it = _edges.find(std::make_pair(&src, &dest));
            size_t  idx = utils::get_index(_edges, it);

            return (*topology)[idx];
        }

        bool
        is_visited_node(VisitedNodes const& visited, NodePair const& node) const
        {
            return is_visited_node(visited, node.first, node.second);
        }

        bool
        is_visited_node(VisitedNodes const& visited,
                        Node const* current, Node const* parent) const
        {
            auto it = visited.find(current);

            if (it == visited.end())
                return false;
            return (std::find(it->second.begin(), it->second.end(),
                              parent) != it->second.end());
        }

        void
        tag_node_visited(VisitedNodes& visited, NodePair const& current) const
        {
            tag_node_visited(visited, current.first, current.second);
        }

        void
        tag_node_visited(VisitedNodes& visited,
                         Node const* current, Node const* parent) const
        {
            auto it = visited.find(current);

            if (it == visited.end()) {
                visited[current] = NodeSet();
                visited[current].insert(current);
            } else {
                it->second.insert(parent);
            }
        }

        // TODO tree instead? VisitedNodes data structure is ugly af
        std::list<NodeList>
        bfs_build_paths(Node const& src, Node const& dest,
                        VisitedNodes const& visited,
                        unsigned int max_nb_paths) const
        {
            std::list<NodeList>   paths(1);

            dfs_build_paths(src, &dest, visited, paths);
            return paths;
        }

        void
        dfs_build_paths(Node const& src, Node const* current,
                           VisitedNodes const& visited,
                           std::list<NodeList>& paths,
                           unsigned int max_nb_paths) const
        {
            NodeList& path = paths.back();

            path.push_front(current);
            if (*current == src) {      // path complete
                paths.push_front(path);
            } else {
                NodeSet parents = visited.at(current);

                for (Node const* parent: parents) {
                    if (std::find(path.begin(),         // bottleneck
                                  path.end(), parent) == path.end()) {

                        dfs_build_paths(src, parent, visited, paths);
                        path = paths.back();

                        if (path.size() > 1)
                            path.pop_front();
                    }
                }
            }
        }

    protected:
        NodeContainer   _nodes;
        EdgeContainer   _edges;
        PathReqs        _pathreqs;
        unsigned int    _total_cost;
};

template <>
std::string
Graph<std::string>::id_to_string(std::string const& id)
{
    return id;
}

}

#endif /* end of include guard: GSPGRAPH_HPP_ */
