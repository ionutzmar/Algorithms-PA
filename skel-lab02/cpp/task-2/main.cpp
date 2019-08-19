#include <fstream>
#include <vector>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> dist;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 0, d; i < n; i++) {
			fin >> d;
			dist.push_back(d);
		}
		fin.close();
	}

	int get_result() {
        int stops = 0;
        int lastStop = 0;
        int tank = m;
        for (vector<int>::iterator it = dist.begin(); it != dist.end(); ++it) {
            if (*next(it, 1) <= tank + lastStop) {
                continue;
            } else {
                lastStop = *it;
                stops++;
            }
        }

		return stops;
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
