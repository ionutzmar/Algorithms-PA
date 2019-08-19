#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

const int kMod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	string expr;

	void read_input() {
		ifstream fin("in");
		fin >> n >> expr;
		// expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
		fin.close();
	}

	int get_result() {
		/*
		Calculati numarul de parantezari ale expresiei date astfel incat
		rezultatul sa dea true si returnati restul impartirii numarului
		la 10^9 + 7.
		*/

        std::vector< std::vector<int> > t;
        std::vector< std::vector<int> > f;
        int expressionLength = expr.length();
        t.resize(expressionLength);
        f.resize(expressionLength);
        for (int i = 0; i < expressionLength; i++) {
            t[i].resize(expressionLength);
            f[i].resize(expressionLength);
        }

        for (int i = 0; i < expr.length(); i++) {
            if (expr[i] == 'T') {
                t[i][i] = 1;
                f[i][i] = 0;
            } else if (expr[i] == 'F') {
                t[i][i] = 0;
                f[i][i] = 1;
            }
        }


        for (int i = 2; i < expr.lenght(); i += 2) {
            if (expr[i / 2 + 1] == '&')
                t[i][i + 2] = t[i][i] * t[i + 2][i + 2];
            if (expr[i / 2 + 1] == '^') {
                t[i][i + 2] = t[i][i] * t[i + 2][i + 2];
            }
        }
		return 0;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
