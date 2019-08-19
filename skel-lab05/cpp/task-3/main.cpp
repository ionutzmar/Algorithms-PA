#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
    vector<int> sol;
    vector<int> rez;
	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

    bool successor(int k)
    {
        if (sol[k] < n)
        {
            sol[k]++;
            return true;
        }
        return false;
    }

    int abs(int a)
    {
        if (a >= 0)
            return a;
        return -a;
    }

    bool valide(int k)
    {
        bool ev = true;
        for(int i = 1; i < k; i++)
            if (abs(i - k) == abs(sol[k] - sol[i]) || sol[k] == sol[i])
                return false;
        return true;
    }

    vector<int> back(int k) {
        if(k == n + 1)
            rez = sol;
        else
        {
            // cout << "trece prin back";
            sol[k] = 0;//init(k);
            while(successor(k))
                if(valide(k))
                     back(k + 1);
        }
    }
	vector<int> get_result() {
		// vector<int> sol(n + 1, 0);
        cout << "inainte de resize";
        sol.resize(n + 1);
        cout <<"Dupa resize";
		/*
		TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
		n x n.

		Pentru a plasa o dama pe randul i, coloana j:
			sol[i] = j.
		Randurile si coloanele se indexeaza de la 1 la n.

		De exemplu, configuratia (n = 5)
		X----
		--X--
		----X
		-X---
		---X-
		se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.
		*/
        back(1);
		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i != n ? ' ' : '\n');
		}
		fout.close();
	}
};

int main() {
    cout << "Intra in main";
	Task task;
	task.solve();

	return 0;
}
