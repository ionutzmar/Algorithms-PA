#include <fstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Object {
	int weight;
	int price;

	Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, w;
	vector<Object> objs;

	void read_input() {
		ifstream fin("in");
		fin >> n >> w;
		for (int i = 0, weight, price; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}

	double get_result() {
		sort(objs.begin(), objs.end(), compare_proportion);
		double score = 0;

		for (auto item : objs) {
			cout << item.price << "\n";
			if (item.weight <= w) {
				w -= item.weight;
				score += (double) item.price;
			} else if (w > 0) {
				score += (double) w * item.price / (double) item.weight;
				w = 0;
				break;
			}
		}

		return score;
	}

	void print_output(double result) {
		ofstream fout("out");
		fout << setprecision(4) << fixed << result;
		fout.close();
	}

	static bool compare_proportion(Object o1, Object o2) {
		return ((o1.price / (double) o1.weight) >= (o2.price/ (double) o2.weight));
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
