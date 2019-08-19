#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
    vector<vector<int> > all;
	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

    void back(int step, int stop, std::vector<int> domain,
            std::vector<int> solution) {

        all.push_back(solution);
        unsigned i = step > 0 ? solution[step - 1] + 1 : 0;
        for (; i < domain.size(); ++i) {
            solution.push_back(i);
            // solution[step] = i;
            back(step + 1, stop, domain, solution);
            solution.pop_back();
        }
    }
	vector<vector<int> > get_result() {


		/*
		TODO: Construiti toate submultimile multimii {1, ..., N}.

		Pentru a adaug a o noua submultime:
			vector<int> submultime;
			all.push_back(submultime);
		*/
        std::vector<int> domain(n);
        std::vector<int> solution;
        for (int i = 0; i < n; ++i) {
            domain[i] = i + 1;
        }

        back(0, n, domain, solution);
    		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
			     fout << result[i][j] + 1 <<
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
