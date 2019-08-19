#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool myComp(long a, long b) {
    return a > b;
}

int main(int argc, char** argv) {
    ifstream fin;
    ofstream fout;
    int n, k, i, j;
    vector<long> vec;
    fin.open("p2.in");
    fin >> n;
    fin >> k;
    j = n;
    while (j > 0) {
        long num;
        fin >> num;
        vec.push_back(num);
        j--;
    }
    sort(vec.begin(), vec.end(), myComp);

    vector<vector <long>> dp;
    dp.resize(n + 1);
    for (i = 0; i <= n; i++) {
        dp[i].resize(k + 1);
    }

    for (i = 0; i <= k; i++) {
        dp[i][i] = 0;
    }

    for (i = 0; i <= k; i++) {
        dp[i + 1][i] = vec[0];
    }

    for (i = 0; i <= k; i++) {
        dp[i + 2][i] = dp[i + 1][i] - vec[i + 1];
    }

    for (i = 3; i <= n; i++) {
        for (j = 0; j <= min(k, i - 3); j++) {
            if (j == 0 && i % 2 == 1) {
                dp[i][j] = dp[i - 1][j] + vec[i - 1];
            } else if (j == 0 && i % 2 == 0) {
                dp[i][j] = dp[i - 1][j] - vec[i - 1];
            }
            else if (abs(i - j) % 2 == 1) {
                dp[i][j] = max(dp[i - 1][j] + vec[i - 1], dp[i - 1][j - 1]);
            } else {
                dp[i][j] = max(dp[i - 1][j] - vec[i - 1], dp[i - 1][j - 1]);
            }
        }
    }


    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }


    fout.open("p2.out");
    fout << dp[n][k];
    fout.close();
    fin.close();

}
