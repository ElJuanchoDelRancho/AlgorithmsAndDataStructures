/**
    AdjacencyListGraph.cpp
    Purpose: Graph implementation based in lists of adjacency

    @author: Juan Castillo
    @version: 1.0 30/06/2019
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
using std::cout;
using std::unordered_map;
using std::vector;
using std::pair;
using std::make_pair;

template<class type>
class Graph
{
private:

    class Vertex
    {
    public:
        Vertex();
        Vertex(const type& data);

        int number_edges();

        type data;
        vector< pair<Vertex*, double> > adj_list;
    };

    unordered_map<type, Vertex*> vertices;
    Vertex* find_vertex(const type& data);

public:
    Graph(bool is_directed = false);
    ~Graph();

    bool add_vertex(const type& data);
    bool remove_vertex(const type& data);

    bool add_edge(const type& from, const type& to, double cost = 1.0);
    bool remove_edge(const type& from, const type& to);

    int number_vertices();
    int number_edges();

    void print();
    void bfs();
    void bfs(type start);
    void dfs();
    void dfs(type start);

    bool is_directed;
};

template<class type>
Graph<type>::Vertex::Vertex() {

}

template<class type>
Graph<type>::Vertex::Vertex(const type& data) {
    this->data = data;
}

template<class type>
int Graph<type>::Vertex::number_edges() {
    return adj_list.size();
}

template<class type>
Graph<type>::Graph(bool is_directed) {
    this->is_directed = is_directed;
}

template<class type>
Graph<type>::~Graph() {
    for (auto x : vertices) {
        delete x.second;
    }
    vertices.clear();
}

template<class type>
typename Graph<type>::Vertex* Graph<type>::find_vertex(const type& data) {
    typename unordered_map<type, Vertex*>::const_iterator itr = vertices.find(data);
    return itr == vertices.end() ? nullptr : itr->second;
}

template<class type>
bool Graph<type>::add_vertex(const type& data) {
    if (find_vertex(data) != nullptr) {
        return false;
    }
    Vertex* new_vertex = new Vertex(data);
    vertices[data] = new_vertex;
    return true;
}

template<class type>
bool Graph<type>::remove_vertex(const type& data) {
    Vertex* node = find_vertex(data);
    if (node == nullptr) {
        return false;
    }
    for (auto x : vertices) {
        remove_edge(x.first, data);
    }
    vertices.erase(data);
    delete node;
    return true;
}

template<class type>
bool Graph<type>::add_edge(const type& from, const type& to, double cost) {
    Vertex* vxt_from = find_vertex(from);
    Vertex* vxt_to = find_vertex(to);

    if (vxt_from == nullptr || vxt_to == nullptr) {
        return false;
    }

    vxt_from->adj_list.push_back(make_pair(vxt_to, cost));
    if (is_directed == false) {
        if (vxt_from != vxt_to) {
            vxt_to->adj_list.push_back(make_pair(vxt_from, cost));
        }
    }
    return true;
}

template<class type>
bool Graph<type>::remove_edge(const type& from, const type& to) {
    Vertex* vxt_from = find_vertex(from);
    Vertex* vxt_to = find_vertex(to);

    if (vxt_from == nullptr || vxt_to == nullptr) {
        return false;
    }

    for (typename vector< pair<Vertex*, double> >::iterator itr = 
    vxt_from->adj_list.begin(); itr != vxt_from->adj_list.end(); itr++) {
        if (itr->first->data == to) {
            vxt_from->adj_list.erase(itr);
            if (is_directed == true) {
                return true;
            } else {
                break;
            }
        }
    }
    if (is_directed == false) {
        for (typename vector< pair<Vertex*, double> >::iterator itr = 
        vxt_to->adj_list.begin(); itr != vxt_to->adj_list.end(); itr++) {
            if (itr->first->data == from) {
                vxt_to->adj_list.erase(itr);
                return true;
            }
        }
    }
    return false;
}

template<class type>
int Graph<type>::number_vertices() {
    return vertices.count;
}

template<class type>
int Graph<type>::number_edges() {
    int count = 0;
    for (auto x : vertices) {
        count += x.second->number_edges();
    }
    return is_directed == true ? count : count / 2;
}

template<class type>
void Graph<type>::print() {
    for (auto x : vertices) {
        cout << x.second->data;
        for (auto y : x.second->adj_list) {
            cout << "->" << y.first->data;
        }
        cout << '\n';
    }
}

template<class type>
void Graph<type>::bfs() {
    if (vertices.size() == 0) {
        return;
    }
    bfs(vertices.begin()->first);
}

template<class type>
void Graph<type>::bfs(type start) {
    Vertex* vxt = find_vertex(start);
    if (vxt == nullptr) {
        return;
    }
    
    unordered_map<type, bool> visited;
    for (auto x : vertices) {
        visited[x.first] = false;
    }
    std::queue<Vertex*> q;
    q.push(vxt);
    visited[vxt->data] = true;
    
    while (q.empty() == false) {
        vxt = q.front();
        q.pop();
        cout << vxt->data << " - ";
        for (auto x : vxt->adj_list) {
            if (visited[x.first->data] == false) {
                q.push(x.first);
                visited[x.first->data] = true;
            }
        }
    }
    cout << '\n';
}

template<class type>
void Graph<type>::dfs() {
    if (vertices.size() == 0) {
        return;
    }
    dfs(vertices.begin()->first);
}

template<class type>
void Graph<type>::dfs(type start) {
    Vertex* vxt = find_vertex(start);
    if (vxt == nullptr) {
        return;
    }
    
    unordered_map<type, bool> visited;
    for (auto x : vertices) {
        visited[x.first] = false;
    }
    std::stack<Vertex*> stk;
    stk.push(vxt);
    visited[vxt->data] = true;
    
    while (stk.empty() == false) {
        vxt = stk.top();
        stk.pop();
        cout << vxt->data << " - ";
        for (auto x : vxt->adj_list) {
            if (visited[x.first->data] == false) {
                stk.push(x.first);
                visited[x.first->data] = true;
            }
        }
    }
    cout << '\n';
}

int main() {
    Graph<int> my_graph;

    my_graph.add_vertex(43);
    my_graph.add_vertex(21);
    my_graph.add_vertex(13);
    my_graph.add_vertex(7);
    my_graph.add_vertex(18);

    my_graph.add_edge(21, 43);
    my_graph.add_edge(21, 13);
    my_graph.add_edge(43, 7);
    my_graph.add_edge(13, 7);
    my_graph.add_edge(13, 18);
    my_graph.add_edge(7, 18);

    cout << "Graph's adjacency lists:\n";
    my_graph.print();
    cout << "Breadth first traversal:\n";
    my_graph.bfs(21);
    cout << "Depth first traversal:\n";
    my_graph.dfs(21);

    cout << "Removing vertex: 13\n";
    my_graph.remove_vertex(13);
    my_graph.print();
    cout << "Number edges: " << my_graph.number_edges();

    std::cin.get();

    return 0;
}
