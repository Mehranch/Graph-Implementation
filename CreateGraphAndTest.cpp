#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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
        getline(fin, line); // Dummy line
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
private:
    vector<Vertex*> adj;
};

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: ./CreateGraphAndTest InputGraph Queries" << endl;
        return 1;
    }
    AdjList adj(argv[1]);
    ifstream fin(argv[2]);
    int a, b;
    while (fin >> a >> b) {
        Vertex* check = adj.connection(a, b);
        cout << a << " " << b << ": ";
        if (check != NULL) {
            cout << "Connected, weight of edge is " << check->weight << endl;
        } else {
            cout << "Not connected" << endl;
        }
    }
}
