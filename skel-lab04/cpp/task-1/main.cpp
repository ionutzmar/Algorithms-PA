#include <fstream>
#include <vector>
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
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		// v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		/*
		Calculati numarul de subsiruri ale lui v cu suma numerelor para si
		returnati restul impartirii numarului la 10^9 + 7.
		*/
        vector<int> pare;
        vector<int> impare;
        pare.push_back(1);
        impare.push_back(0);
        for (auto elem : v) {
            if (elem % 2 == 0) {
                pare.push_back((pare.back() * 2) % kMod);
                impare.push_back((impare.back() * 2) % kMod);
            } else {
                int lastEven = pare.back();
                pare.push_back((impare.back() + lastEven) % kMod);
                impare.push_back((impare.back() + lastEven) % kMod);
            }
        }

        return pare.back() - 1;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
