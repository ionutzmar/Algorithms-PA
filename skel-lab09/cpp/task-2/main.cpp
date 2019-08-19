#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
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
		folosind BellmanFord pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.

		In cazul in care exista ciclu de cost negativ, returnati un vector gol:
			return vector<int>();
		*/
        int inf = INT_MAX;
		vector<int> d(n + 1, inf);
        d[source] = 0;

        for (int i = 0; i < n - 2; i++) {
            for (int j = 1; j <= n; j++) {
                for (auto pair : adj[j]) {
                    int node = pair.first;
                    int cost = pair.second;
                    if (d[j] != inf && d[j] + cost < d[node]) {
                        d[node] = d[j] + cost;
                    }
                }
            }
        }

        for (int j = 1; j <= n; j++) {
            for (auto pair : adj[j]) {
                int node = pair.first;
                int cost = pair.second;
                if (d[j] != inf && d[j] + cost < d[node]) {
                    return vector<int>();
                }
            }
        }

        for (int i = 1; i <= n; i++)
            if (d[i] == inf) {
                d[i] = -1;
            }
		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		if (result.size() == 0) {
			fout << "Ciclu negativ!\n";
		} else {
			for (int i = 1; i <= n; i++) {
				fout << result[i] << ' ';
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
