#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <limits.h>
using namespace std;

const int kNmax = 50005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source;
	vector<pair<int, int> > adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti distantele minime de la nodul source la celelalte noduri
		folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.
		*/
		vector<int> d(n + 1, INT_MAX);
        d[0] = 0;
        d[source] = 0;
        priority_queue< pair<int, int>, vector <pair<int, int>> , greater<pair<int, int>> > pq;
        pq.push(make_pair(0, source));
        vector<bool> selected(n + 1, false);

        while (!pq.empty()) {
            int node = pq.top().second;
            pq.pop();
            if (selected[node] == true)
                continue;
            selected[node] = true;
            for (auto pair : adj[node]) {
                int neighbour = pair.first;
                int cost = pair.second;
                if (!selected[neighbour] && d[neighbour] > d[node] + cost) {
                    d[neighbour] = d[node] + cost;
                    pq.push(make_pair(d[neighbour], neighbour));
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (d[i] == INT_MAX)
                d[i] = -1;
        }
        return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << " ";
		}
		fout << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
