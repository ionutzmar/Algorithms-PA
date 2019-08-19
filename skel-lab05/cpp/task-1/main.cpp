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
	int n, k;
    vector<vector<int>> all;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin.close();
	}

    bool check(std::vector<int> solution) {
        return true;
    }

    void back(std::vector<int> domain, std::vector<int> solution) {
        /* dupa ce am folosit toate elementele din domeniu putem verifica daca
        am gasit o solutie */
        if (domain.size() == n - k) {
            if(check(solution)) {
                all.push_back(solution);
            }
            return;
        }

        /* incercam sa adaugam in solutie toate valorile din domeniu, pe rand */
        for (unsigned int i = 0; i < domain.size(); ++i) {
            /* cream o solutie noua si un domeniu nou care sunt identice cu cele
            de la pasul curent */
            std::vector<int> newSolution(solution), newDomain(domain);

            /* adaugam in noua solutie elementul ales din domeniu */
            newSolution.push_back(domain[i]);
            /* stergem elementul ales din noul domeniu */
            newDomain.erase(newDomain.begin() + i);

            /* apelam recursiv backtracking pe noul domeniu si noua solutie */
            back(newDomain, newSolution);
        }
    }
	vector<vector<int> > get_result() {
		/*
		TODO: Construiti toate aranjamentele de N luate cate K ale
		multimii {1, ..., N}.

		Pentru a adauga un nou aranjament:
			vector<int> aranjament;
			all.push_back(aranjament);
		*/
        std::vector<int> domain(n), solution;
        for (int i = 0; i < n; ++i) {
            domain[i] = i + 1;
        }
        /* apelam backtracking pe domeniul nostru, cautand solutia in vectorul solution */
        back(domain, solution);
		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
