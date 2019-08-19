#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(compute_sqrt());
	}

private:
	double n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	double compute_sqrt() {
		/*
		TODO: Calculati sqrt(n) cu o precizie de 0.001
		Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x
		*/

		double left = 0;
		double right = max(1.0, n);
		double result;
		for (int i = 0; i < 50; i++) {
			double midValue = (left + right) / 2;
			result = midValue;
			if (abs(result * result - n) < 1e-6)
				return result;
			if (result * result > n)
				right = midValue;
			else
				left = midValue;
		}

		return result;
	}

	void print_output(double result) {
		ofstream fout("out");
		fout << setprecision(4) << fixed << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
