#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

class Vertex {
public:
    Vertex* next;
    int node;
    double weight;

    Vertex(int n, double w) {
        node = n;
        weight = w;
        next = NULL;
    }

    void add(Vertex* v) {
        if (next == NULL) {
            next = v;
            return;
        }
        next->add(v);
    }
};

class AdjList {
public:
    AdjList(string fname) {
        read(fname);
    }

    void read(string fname) {
        ifstream fin(fname.c_str());
        string line;
        getline(fin, line); // dummy
        while (getline(fin, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            int current;
            int node;
            double weight;
            ss >> current;
            adj.resize(adj.size() + 1);
            while (ss >> node >> weight) {
                if (adj.back() == NULL) {
                    adj.back() = new Vertex(node, weight);
                } else {
                    adj.back()->add(new Vertex(node, weight));
                }
            }
        }
    }

    Vertex* connection(int a, int b) {
        Vertex* curr = adj[a - 1];
        while (curr != NULL && curr->node != b) {
            curr = curr->next;
        }
        return curr;
    }

    Vertex* operator[](const int idx) {
        return adj[idx - 1];
    }

    int size() {
        return adj.size();
    }
private:
    vector<Vertex*> adj;
};

class Graph {
public:
    Graph(const char* fname, int n) : adj(fname) {
        start = n;
        weights = vector<double>(adj.size(), -1000);
        back_pointer = vector<int>(adj.size(), -999);
        weights[start - 1] = 0;
    }

    void dijkstra() {
        // weight, node
        priority_queue<pair<double, int> , vector<pair<double, int> >, greater<pair<double, int> > > pq;
        pq.push(pair<double, int>(0.0, start));
        vector<bool> visited(adj.size(), false);
        back_pointer[start - 1] = start - 1;
        while (!pq.empty()) {
            pair<double, int> current = pq.top();
            double current_cost = current.first;
            int current_node = current.second;
            //cout << "Inspecting: " << current_node << ": " << current_cost << endl;
            visited[current_node - 1] = true;
            pq.pop();
            Vertex* v = adj[current.second]; 
            Vertex* curr = v;
            while (curr != NULL) {
                double cost = curr->weight;
                int connection = curr->node;
                if (!visited[connection - 1]) {
                    //cout << "Comparing against: " << connection << ": " << cost << endl;
                    if (weights[connection - 1] <= -999 || current_cost + cost < weights[connection - 1]) {
                        weights[connection - 1] = current_cost + cost;
                        back_pointer[connection - 1] = current_node - 1;
                        pq.push(pair<double, int>(current_cost + cost, connection));
                        //cout << "Connection update: " << connection << ": " << current_cost + cost << endl;
                    } 
                }
                curr = curr->next;
            }
        }
    }

    double distance(int n) {
        return weights[n - 1];
    }

    vector<int> trace(int n) {
        vector<int> t;
        n = n - 1;
        while (n != start - 1 && n >= 0) {
            t.insert(t.begin(), n + 1);
            n = back_pointer[n];
        }
        return t;
    }

    int size() {
        return adj.size();
    }
private:
    AdjList adj;
    vector<double> weights;
    vector<int> back_pointer;
    int start;
};

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: ./FindPaths InputGraph Node" << endl;
        return 1;
    }
    const char* fname = argv[1];
    int node = atoi(argv[2]);
    Graph g(fname, node); 
    g.dijkstra();
    for (int i = 1; i <= g.size(); i++) {
        if (i == node) continue;
        vector<int> t = g.trace(i);
        if (g.distance(i) >= 0) {
            cout << i << ": " << node << ", ";
            for (int j = 0; j < (int) t.size(); j++) {
                cout << t[j] << ", ";
            }
            cout << "Total cost: " << g.distance(i) << endl;
        } else {
            cout << i << ": No path" << endl;
        }
    }
}
