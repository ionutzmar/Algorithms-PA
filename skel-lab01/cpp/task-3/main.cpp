#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result(n, x, y));
	}

private:
	int n, x, y;

	void read_input() {
		ifstream fin("in");
		fin >> n >> x >> y;
		fin.close();
	}

	int get_result(int n, int x, int y) {
		/*
		TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune
		2^n x 2^n
		*/
		if (x == 1 && y == 1) {
			return 1;
		}
		if (x == 1 && y == 2) {
			return 2;
		}
		if (x == 2 && y == 1) {
			return 3;
		}
		if (x == 2 && y == 2) {
			return 4;
		}
		if (x <= (int) pow(2, n - 1)) {
			if (y <= (int) pow(2, n - 1)) {
				return get_result(n - 1, x, y);
			return  (int) pow(2, n - 1) * (int) pow(2, n - 1) + get_result(n-1, x, y  - (int) pow(2, n - 1));
			}

		}
		if (y <= (int) pow(2, n - 1))
			return (int) pow(2, n - 1) * (int) pow(2, n - 1) + get_result(n-1, x - (int) pow(2, n - 1), y);
		return 3 * (int) pow(2, n - 1) * (int) pow(2, n - 1) + get_result(n-1, x  - (int) pow(2, n - 1), y - (int) pow(2, n - 1));
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
