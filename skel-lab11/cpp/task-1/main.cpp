#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

const int kNmax = 1005;

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
    int C[kNmax][kNmax];
    vector<int> p;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		memset(C, 0, sizeof C);
		for (int i = 1, x, y, z; i <= m; i++) {
			fin >> x >> y >> z;
			adj[x].push_back(y);
			adj[y].push_back(x);
      C[x][y] += z;
		}
		fin.close();
	}

    void bfs(int source) {
        for(int i = 1; i <= n; i++) {
            p[i] = -1;
        }
		queue<int> q;
        vector<int> visited(n + 1, 0);
        visited[source] = 1;
		q.push(source);
        int u;
		while(!q.empty()) {
			u = q.front();
			q.pop();
			for(auto v : adj[u]) {
				if(visited[v] == 0 && C[u][v] > 0) {
                    visited[v] = 1;
					p[v] = u;
					q.push(v);
				}
			}
		}
	}

    // int flow = 0;
    // void dfs(int start, int finish, int min) {
    //     if (start == finish) {
    //         flow += min;
    //         int i = finish;
    //         while (p[i] != -1) {
    //             C[p[i]][i] -= min;
    //             C[i][p[i]] += min;
    //         }
    //         return;
    //     }
    //     for (int i = 1; i <= n; i++) {
    //         if (C[start][i] != 0) {
    //             if (min > C[start][i]) {
    //                 min = C[start][i];
    //             }
    //             p[i] = start;
    //             dfs(i, finish, min);
    //         }
    //     }
    // }
	int get_result() {
		/*
		TODO: Calculati fluxul maxim pe graful orientat dat.
		Sursa este nodul 1.
		destinationinatia este nodul n.

		In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
		arcelor, iar in C sunt stocate capacitatile arcelor.
		De exemplu, un arc (x, y) de capacitate z va fi tinut astfel:
		C[x][y] = z, adj[x] contine y, adj[y] contine x.
		*/
        p.resize(n + 1);

        int flow = 0;
		int source = 1;
		int destination = n;
		while(true) {
			bfs(source);
			if(p[destination] == -1)
				break;
			int aux = destination;
            int j = p[destination];
            int minim = 99999;
			while(j != -1) {
				minim = min(minim, C[j][aux]);
				aux = j;
				j = p[aux];
			}

            flow += minim;

			aux = destination;
			j = p[destination];
			while(j != -1) {
				C[j][aux] -= minim;
				C[aux][j] += minim;
				aux = j;
				j = p[aux];
			}
		}
		return flow;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
