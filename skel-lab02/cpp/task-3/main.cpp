#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}

	int get_result() {

		int result = 0;
		sort(hws.begin(), hws.end(), compareHws);

		vector<Homework>::iterator it = hws.begin();
		int deadline = (*it).deadline;

		queue<Homework> desiredHomeworks;

		while (deadline > 0 && it != hws.end()) {
			while ((*it).deadline >= deadline) {
				desiredHomeworks.push((*it));
				it++;
			}

			if (!desiredHomeworks.empty()) {
				Homework thisWeekHm = desiredHomeworks.front();
				desiredHomeworks.pop();
				result += thisWeekHm.score;
			}

			deadline--;
		}
		return result;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}

	static bool compareHws(Homework h1, Homework h2) {
		if (h1.deadline == h2.deadline) {
			return h1.score > h2.score;
		}
		return h1.deadline > h2.deadline;
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
