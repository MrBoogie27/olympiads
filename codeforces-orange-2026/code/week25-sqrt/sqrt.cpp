#include <bits/stdc++.h>
using namespace std;

class SqrtDecomposition {
private:
    vector<int> arr, block;
    int block_size;
    
public:
    SqrtDecomposition(vector<int>& a) {
        arr = a;
        block_size = sqrt(a.size()) + 1;
        block.resize((a.size() + block_size - 1) / block_size, 0);
        rebuild();
    }
    
    void rebuild() {
        for (int i = 0; i < block.size(); i++) {
            block[i] = 0;
            for (int j = i * block_size; j < min((int)arr.size(), (i + 1) * block_size); j++) {
                block[i] += arr[j];
            }
        }
    }
    
    void update(int idx, int val) {
        arr[idx] = val;
        rebuild();
    }
    
    long long query(int l, int r) {
        long long sum = 0;
        for (int i = l; i <= r; i++) {
            sum += arr[i];
        }
        return sum;
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    SqrtDecomposition sd(arr);
    
    cout << "Sum [0, 4]: " << sd.query(0, 4) << "\n";
    sd.update(2, 10);
    cout << "After update [2]=10, Sum [0, 4]: " << sd.query(0, 4) << "\n";
    
    return 0;
}
