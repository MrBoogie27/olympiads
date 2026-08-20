#include <bits/stdc++.h>
using namespace std;

// Monotonic Stack: максимум в каждом окне
vector<int> maxInEachWindow(vector<int>& arr, int k) {
    vector<int> result;
    deque<int> dq;
    
    for (int i = 0; i < arr.size(); i++) {
        // Удалить элементы вне окна
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        
        // Удалить меньшие элементы
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    
    return result;
}

// Monotonic Stack: следующий больший элемент
vector<int> nextGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }
        
        if (!st.empty()) {
            result[i] = arr[st.top()];
        }
        
        st.push(i);
    }
    
    return result;
}

// Monotonic Stack: предыдущий больший элемент
vector<int> previousGreaterElement(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] <= arr[i]) {
            st.pop();
        }
        
        if (!st.empty()) {
            result[i] = arr[st.top()];
        }
        
        st.push(i);
    }
    
    return result;
}

// Largest Rectangle in Histogram
long long largestRectangleInHistogram(vector<int>& heights) {
    stack<int> st;
    long long maxArea = 0;
    
    for (int i = 0; i < heights.size(); i++) {
        while (!st.empty() && heights[st.top()] > heights[i]) {
            int h = heights[st.top()];
            st.pop();
            long long width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, (long long)h * width);
        }
        st.push(i);
    }
    
    while (!st.empty()) {
        int h = heights[st.top()];
        st.pop();
        long long width = st.empty() ? (long long)heights.size() : (long long)heights.size() - st.top() - 1;
        maxArea = max(maxArea, (long long)h * width);
    }
    
    return maxArea;
}

// Maximal Rectangle in Matrix
int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    
    int maxArea = 0;
    vector<int> heights(matrix[0].size(), 0);
    
    for (auto& row : matrix) {
        for (int i = 0; i < row.size(); i++) {
            heights[i] = row[i] == '1' ? heights[i] + 1 : 0;
        }
        maxArea = max(maxArea, (int)largestRectangleInHistogram(heights));
    }
    
    return maxArea;
}

// Сумма минимумов подмассивов
long long sumOfMinimums(vector<int>& arr) {
    int n = arr.size();
    long long result = 0;
    stack<pair<int, int>> st; // (value, count)
    
    for (int num : arr) {
        int count = 1;
        while (!st.empty() && st.top().first >= num) {
            count += st.top().second;
            result += (long long)st.top().first * st.top().second;
            st.pop();
        }
        
        result += (long long)num * count;
        st.push({num, count});
    }
    
    while (!st.empty()) {
        result += (long long)st.top().first * st.top().second;
        st.pop();
    }
    
    return result;
}

// Трубы (Trapping Rain Water)
int trap(vector<int>& height) {
    if (height.size() < 3) return 0;
    
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;
    
    while (left <= right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    
    return water;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Тест 1: Максимум в окне
    vector<int> arr1 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> maxWindow = maxInEachWindow(arr1, 3);
    cout << "Max in each window (k=3): ";
    for (int x : maxWindow) cout << x << " ";
    cout << "\n";
    
    // Тест 2: Следующий больший элемент
    vector<int> arr2 = {2, 7, 11, 15};
    vector<int> nge = nextGreaterElement(arr2);
    cout << "Next greater elements: ";
    for (int x : nge) cout << (x == -1 ? -1 : x) << " ";
    cout << "\n";
    
    // Тест 3: Largest rectangle in histogram
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << "Largest rectangle in histogram: " << largestRectangleInHistogram(heights) << "\n";
    
    // Тест 4: Trapping rain water
    vector<int> elevation = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Trapped water: " << trap(elevation) << "\n";
    
    return 0;
}
