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
	vector<int> adjt[kNmax];
    int index = 0;
    vector<int> idx;
    vector<int> lowlink;
    vector<int> stack;
    vector<int> inStack;
    vector<vector<int>> sol;
    int nrComp = 0;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

	vector<vector<int>> get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.

		Atentie: graful transpus este stocat in adjt.
		*/

        idx.resize(n + 1);
        lowlink.resize(n + 1);
        inStack.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            idx[i] = -1;
            inStack[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            if (idx[i] == -1) {
                tarjan(i);
            }
        }
        // fprintf(stderr, "nrComp: %d\n", nrComp);

        // for (int i = 0; i < nrComp - 1; i++) {
        //     for (int j = 0; j < sol[i].size(); j++) {
        //         fprintf(stderr, "%d ", sol[i][j]);
        //     }
        //     fprintf(stderr, "\n");
        // }
		return sol;
	}

    void tarjan(int v) {
        idx[v] = index;
        lowlink[v] = index;
        index++;
        stack.push_back(v);
        inStack[v] = 1;
        // fprintf(stderr, "In stack: \n");
        // for (int i = 1; i < inStack.size(); i++) {
        //     fprintf(stderr, "%d ", inStack[i]);
        // }
        // fprintf(stderr, "\n");
        // fprintf(stderr, "Za stack: \n" );
        // for (int i = 0; i < stack.size(); i++) {
        //     fprintf(stderr, "%d ", stack[i]);
        // }
        // fprintf(stderr, "\n");
        for (auto u : adj[v]) {
            if (idx[u] == -1) {
                tarjan(u);
                lowlink[v] = min(lowlink[v], lowlink[u]);
            } else if (inStack[u]) {
                lowlink[v] = min(lowlink[v], idx[u]);
            }
        }

        if (lowlink[v] == idx[v]) {
            // printf("Punte: %d\n", v);
            sol.resize(nrComp + 1);
            int u;
            do {
                u = stack.back();
                stack.pop_back();
                inStack[u] = 0;
                sol[nrComp].push_back(u);
                // fprintf(stderr, "adaug: %d\n", u);
            } while (u != v);
            nrComp++;

        }
    }

	void print_output(vector<vector<int>> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
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
