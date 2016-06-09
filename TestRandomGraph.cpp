#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class UnionFind {
public:
    UnionFind(int N) : sz(N, 1) {
        for (int i = 0; i < N; i++) {
            un.push_back(i);
        }
    }
    
    int parent(int N) {
        if (un[N] == N)
            return N;
        return un[N] = parent(un[N]);
    }

    void unionNodes(int a, int b) {
        int ap = parent(a);
        int bp = parent(b);
        if (ap != bp) {
            if (sz[ap] < sz[bp]) {
                un[a] = b;
                sz[bp] += sz[ap];
            } else {
                un[b] = a;
                sz[ap] += sz[bp];
            }
        }
    }

    bool notConnected() {
        int cmp = parent(0);
        for (int i = 1; i < un.size(); i++) {
            if (parent(i) != cmp) return true;
        }
        return false;
    }
private:
    vector<int> un, sz;
};

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: ./TestRandomGraph NumNodes" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    UnionFind u(N);

    vector<vector<bool> > g(N, vector<bool>(N, false));

    srand(time(0));

    while (u.notConnected()) {
        int a = rand() % N;
        int b = rand() % N;
        if (a != b && !g[a][b]) {
            u.unionNodes(a, b);
            g[a][b] = true;
            g[b][a] = true;
        }
    }

    int smallest = N + 1;
    int largest = -1;
    double total = 0;
    for (int i = 0; i < N; i++) {
        int current = 0;
        for (int j = 0; j < N; j++) {
            if (g[i][j]) {
                current++;
            }
        }
        total += current;
        if (current < smallest) {
            smallest = current;
        }
        if (current > largest) {
            largest = current;
        }
    }

    cout << "Num edges: " << total / 2<< endl;
    cout << "Smallest out degree: " << smallest << endl;
    cout << "Largest out degree: " << largest << endl;
    cout << "Average out degree: " << total / N << endl;
}
