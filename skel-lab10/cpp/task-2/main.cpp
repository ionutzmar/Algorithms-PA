#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <tuple>
#include <limits.h>
#include <queue>

using namespace std;

const int kNmax = 2e5 + 10;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<pair<int, int> > adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
			adj[y].push_back(make_pair(x, w));
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Calculati costul minim al unui arbore de acoperire
		folosind algoritmul lui Prim.
		*/
        int answer = 0;

        vector<int> d(n + 1, INT_MAX);
        vector<int> p(n + 1, -1);
        int root = 1;
        d[root] = 0;
        // set<tuple<int, int, int>> heap;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> heap;

        for (auto edge : adj[root]) {
            heap.push(make_tuple(edge.second, root, edge.first));
            d[edge.first] = edge.second;
        }

        p[root] = 1;
        while (!heap.empty()) {
            int weight, first, second;
    		tie(weight, first, second) = heap.top();
            heap.pop();
            if (p[second] != -1)
                continue;
            for (auto edge : adj[second]) {
                int dest = edge.first;
                int w = edge.second;
                if (w < d[dest]) {
                    d[dest] = w;
                    heap.push(make_tuple(w, second, dest));
                }
            }
            answer += weight;
            p[second] = first;
        }
		return answer;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
