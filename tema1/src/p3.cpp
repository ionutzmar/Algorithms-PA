#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool myComp(long a, long b) {
    return a < b;
}

int main(int argc, char** argv) {
    ifstream fin;
    ofstream fout;
    int n, i;
    vector<long> vec;
    fin.open("p3.in");
    fin >> n;
    i = n;
    while (i > 0) {
        long num;
        fin >> num;
        vec.push_back(num);
        i--;
    }
    long firstPart = 0;
    long secondPart = 0;
    long thirdPart = 0;

    vector<vector <long>> dp;
    dp.resize(n);
    for (i = 0; i < n; i++) {
        dp[i].resize(n);
    }

    long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += vec[i];
    }

    for (int i = 0; i < n; i++) {
        dp[i][i] = vec[i];
    }

    for (int i = 0; i < n - 1; i++) {
        dp[i][i + 1] = max(vec[i], vec[i + 1]);
    }

    for (int k = 2; k < n; k++) {
        for (int i = 0, j = k; j < n; j++, i++) {
            firstPart = dp[i + 2][j];
            secondPart = dp[i + 1][j - 1];
            thirdPart = dp[i][j - 2];

            long maxLeft = vec[i] + min(firstPart, secondPart);
            long maxRight = vec[j] + min(secondPart, thirdPart);

            dp[i][j] = max(maxLeft, maxRight);
        }
    }

    long diff = (dp[0][n - 1] * 2) - sum;
    fout.open("p3.out");
    fout << diff;
    fout.close();
    fin.close();

}
