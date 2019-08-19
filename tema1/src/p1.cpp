#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool myComp(int a, int b) {
    return a < b;
}

int main(int argc, char** argv) {
    ifstream fin;
    ofstream fout;
    int n;
    vector<int> vec;
    fin.open("p1.in");
    fin >> n;
    while (n > 0) {
        int num;
        fin >> num;
        vec.push_back(num);
        n--;
    }
    sort(vec.begin(), vec.end(), myComp);
    int sum1 = 0;
    int sum2 = 0;
    while (!vec.empty()) {
        sum1 += vec.back();
        vec.pop_back();
        if (!vec.empty()) {
            sum2 += vec.back();
            vec.pop_back();
        }
    }

    fout.open("p1.out");
    fout << sum1 - sum2;
    fout.close();
    fin.close();

}
