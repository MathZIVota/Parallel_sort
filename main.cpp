#include<thread>
#include<mutex>
#include<functional>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

void merge(vector<vector<long long>> &arr, int num_vectors) {
    ofstream out_file("output.txt", ios::out);
    int min_index = 0;
    if (out_file.is_open()) {
        while (!arr.empty()) {
            min_index = 0;
            for (int i = 0; i < num_vectors; i++) {
                if (arr[i].empty()) {
                    arr[i].assign(arr[i].begin(), arr[i].end());
                }
                if (arr[i].front() < arr[min_index].front()) {
                    min_index = i;
                }
            }
            out_file << arr[min_index].front() << "\n";
            arr[min_index].erase(arr[min_index].begin());
        }
    }
    out_file.close();
}

int func(int num) {
    long long c;
    int cnt = 0, cnt_vectors = -1;
    ifstream in_file("input1.txt");
    vector<vector<long long>> arr(1);
    while (in_file >> c) {
        if (cnt % num == 0) {
            if(cnt/num == arr.size()) arr.push_back({1});
            cnt_vectors++;
            arr[cnt_vectors].resize(num, 0);
        }
        arr[cnt_vectors][cnt%num] = c;
        cnt++;
    }
    
    sort(arr[0].begin(), arr[0].end());
    
    vector<thread> ths(cnt_vectors-1);
    for (int i = 1; i < cnt_vectors; i++) {
        ths[i].emplace_back(sort, arr[i].begin(), arr[i].end());
    }
    for (int i = 0; i < cnt_vectors; i++) ths[i].join();

    merge(arr, cnt_vectors);
    in_file.close();
    return cnt;
}

int main() {
    int num = 0;
    cout << "num of numbers: "; cin >> num;
    int cnt = 0;
    cnt = func(num);
    cout << ">" << cnt << endl;
    cout << "\nEnd\n";
    return 0;
}
