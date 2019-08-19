#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
    vector<int> topsort;
    vector<int> color;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
		}
		fin.close();
	}

    void dfs(int nod) {
        for (auto neighbour : adj[nod]) {
            if (color[neighbour] == 0) {
                color[neighbour] = 1;
                dfs(neighbour);
            }
        }
        topsort.push_back(nod);
    }

	vector<int> get_result() {
		/*
		TODO: Faceti sortarea topologica a grafului stocat cu liste de
		adiacenta in adj.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
        color.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            color[i] = 0;
        }
        int start = n;
        while (start != -1) {
            start = -1;
            for (int i = 1; i <= n; i++) {
                if (color[i] == 0) {
                    start = i;
                    color[start] = 1;
                    dfs(start);
                }
            }
        }
        reverse(topsort.begin(), topsort.end());
		return topsort;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
