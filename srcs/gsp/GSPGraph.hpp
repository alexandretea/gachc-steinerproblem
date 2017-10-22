// C/C++ File

// Author:   Alexandre Tea <alexandre.qtea@gmail.com>
// File:     /Users/alexandretea/Work/gachc-steinerproblem/srcs/gsp/Edge.hpp
// Purpose:  TODO (a one-line explanation)
// Created:  2017-03-05 14:53:28
// Modified: 2017-10-22 20:02:58

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

                // comparison operators
                bool
                operator==(Node const& rhs) const   { return _id == rhs._id; }
                bool
                operator!=(Node const& rhs) const   { return !operator==(rhs); }
                bool
                operator<(Node const& rhs) const    { return _id < rhs._id; }

                void
                add_neighbour(Node const& n, unsigned int cost)
                {
                    _neighbours.emplace(&n, cost);
                } // TODO removal function

                IDType const&   get_id() const      { return _id; }
                Type            get_type() const    { return _type; }

                typename std::map<Node const*, unsigned int>::const_iterator
                begin() const   { return _neighbours.begin(); }
                typename std::map<Node const*, unsigned int>::const_iterator
                end() const     { return _neighbours.end(); }

            protected:
                IDType  _id;
                Type    _type;

                std::map<Node const*, unsigned int>    _neighbours;
        };

        using NodePair = std::pair<Node const*, Node const*>;

        struct NodePairHasher
        {
            // TODO get same hash if pairs are in either way (a/b = b/a)
            size_t
            operator()(NodePair const& path) const
            {
                std::hash<std::string> hasher;

                if (path.first == nullptr and path.second == nullptr)
                    throw std::runtime_error("NodePairHasher: "
                            "Can't hash because nodes are null");

                if (path.first == nullptr)
                    return hasher(id_to_string(path.second->get_id()));
                else if (path.second == nullptr)
                    return hasher(id_to_string(path.first->get_id()));
                return hasher(id_to_string(path.first->get_id())
                              + id_to_string(path.second->get_id()));
            }
        };

        // TODO rename with more explicit name
        using NodeContainer = std::unordered_map<IDType, Node>;
        using EdgeContainer = std::map<NodePair, unsigned int>; // <nodes, cost>
        // Needs to be ordered as it will be represented as FixedBinaryString
        using PathReqs =
            std::unordered_map<NodePair, unsigned int, NodePairHasher>;
        // TODO see usage and check if std::map would be better
        using NodeSet = std::set<Node const*>;
        using NodeList = std::list<Node const*>;

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
        // /!\ it will look for UNIQUE paths
        unsigned int
        count_paths(Node const& src, Node const& dest,
                    unsigned int max_nb_paths = 0,
                    ga::FixedBinaryString const* topology = nullptr) const
        {
            using VisitedBook =
                std::unordered_map<NodePair, bool, NodePairHasher>;

            unsigned int            count = 0;
            // the NodePairs used below follow this structure: <parent, node>
            std::queue<NodePair>    to_visit;
            VisitedBook             visited;

            if (topology != nullptr and _edges.size() != topology->size())
                throw std::runtime_error("Binary string has a different size "
                                         "from edges container ");

            // start node so no parent
            to_visit.push(std::make_pair(nullptr, &src));

            while (not to_visit.empty()) {
                NodePair    pair = to_visit.front();
                Node const& node = *pair.second;

                // remove from queue and mark as visited
                to_visit.pop();
                if (visited.find(pair) != visited.end())
                    continue ;
                visited[pair] = true;

                for (auto& neighbour: node) {

                    if (not is_edge_enabled(node, *neighbour.first, topology))
                        continue ;

                    NodePair    neighbour_pair =
                        std::make_pair(&node, neighbour.first);

                    // destination found
                    if (*neighbour.first == dest) {
                        ++count;
                        if (max_nb_paths > 0 and count >= max_nb_paths)
                            return count;
                    }
                    // neighbour hasn't been visited yet
                    else if (visited.find(neighbour_pair) == visited.end()) {
                        to_visit.push(neighbour_pair);
                    }
                }
            }
            return count;
        }

        // check if the given topology matches all path requirements
        bool
        is_valid_topology(ga::FixedBinaryString const& topology) const
        {
            for (auto& req: _pathreqs) {

                if (count_paths(*req.first.first, *req.first.second,
                                req.second, &topology) < req.second)
                    return false;
            }
            return true;
        }

        void
        dump_edges(ga::FixedBinaryString const& topology,
                   std::ostream& os = std::cout) const
        {
            unsigned int i = 0;

            for (auto& edge: _edges) {
                if (topology[i])
                    os  << edge.first.first->get_id() << " -> "
                        << edge.first.second->get_id()
                        << std::endl;
                ++i;
            }
        }

        unsigned int
        get_pathreq(IDType const& id_a, IDType const& id_b) const
        {
            Node&       node_a = _nodes.at(id_a);
            Node&       node_b = _nodes.at(id_b);
            NodePair    p = std::make_pair(node_a, node_b);
            auto        it = _pathreqs.find(p);

            if (it == _pathreqs.end()) {
                p = std::make_pair(node_b, node_a);
                if ((it = _pathreqs.find(p)) == _pathreqs.end())
                    throw std::runtime_error("Path " + id_to_string(id_a)
                                             + "-" + id_to_string(id_b)
                                             + " was not found");
            }
            return it->second;
        }

        Node const&
        get_node(IDType const& id) const
        { return _nodes.at(id); }

        unsigned int
        get_total_cost() const  { return _total_cost; }

        unsigned int
        get_nb_edges() const    { return _edges.size(); }

        /*
        ** Iterator getters
        ** begin()/end() makes the class Graph iterable on its nodes
        ** e.g.     for (auto node: graph) { ... }
        */
        typename std::vector<Node>::const_iterator
        begin() const           { return _nodes.begin(); }
        typename std::vector<Node>::const_iterator
        end() const             { return _nodes.end(); }

        typename EdgeContainer::const_iterator
        edges_begin() const     { return _edges.begin(); }
        typename EdgeContainer::const_iterator
        edges_end() const       { return _edges.end(); }

        typename PathReqs::const_iterator
        pathreqs_begin() const  { return _pathreqs.begin(); }
        typename PathReqs::const_iterator
        pathreqs_end() const    { return _pathreqs.end(); }

        // static tmp
        static std::string
        id_to_string(IDType const& id) { return std::to_string(id); }

    protected:
        bool
        is_edge_enabled(Node const& src, Node const& dest,
                        ga::FixedBinaryString const* topology) const
        {
            if (topology == nullptr)
                return true;

            auto    it = _edges.find(std::make_pair(&src, &dest));
            if (it == _edges.end())
                it = _edges.find(std::make_pair(&dest, &src));
            // TODO improve hasher to avoid double check

            // get index of iterator to look for edge in topology (binary str)
            // _edges is a map so it preserves the order, and these functions
            // shall not be used with unassociated graph/binary string
            // TODO force this association with type matching?
            size_t  idx = utils::get_index(_edges, it);

            return (*topology)[idx];
        }

        void
        dfs_search(Node const& src, Node const& current,
                   std::list<NodeList>& paths,
                   std::unordered_map<Node const*, bool>& visited,
                   ga::FixedBinaryString const* topology,
                   unsigned int max_nb_paths) const
        {
            // check if max_nb_paths was reached
            if (max_nb_paths > 0 and paths.size() - 1 == max_nb_paths)
                return ;

            paths.back().push_front(&current);      // add to path
            visited[&current] = true;               // mark as visited

            if (current == src) {                   // path found
                paths.push_front(paths.back());
                goto end_visit;
            }
            for (auto& neighbour: current) {
                if (is_edge_enabled(current, *neighbour.first, topology)
                    and visited.find(neighbour.first) == visited.end()) {

                    dfs_search(src, *neighbour.first, paths, visited, topology,
                               max_nb_paths);
                }
            }

        end_visit:
            // remove node from current path
            paths.back().pop_front();
            visited.erase(&current);
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
