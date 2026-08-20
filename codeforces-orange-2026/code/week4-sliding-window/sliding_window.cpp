#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Скользящее окно: максимум в окне размером k
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq;
    
    for (int i = 0; i < nums.size(); i++) {
        // Удаляем элементы вне окна
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        
        // Удаляем меньшие элементы
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// Скользящее окно: минимум в окне
vector<int> minSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    deque<int> dq;
    
    for (int i = 0; i < nums.size(); i++) {
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        
        while (!dq.empty() && nums[dq.back()] > nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}

// Сумма подмассива размером k (простое скользящее окно)
vector<ll> sumSlidingWindow(vector<int>& nums, int k) {
    vector<ll> result;
    ll sum = 0;
    
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }
    result.push_back(sum);
    
    for (int i = k; i < nums.size(); i++) {
        sum = sum - nums[i - k] + nums[i];
        result.push_back(sum);
    }
    
    return result;
}

// Two pointers: найти подмассив с суммой равной target
vector<pii> subarrayWithSum(vector<int>& nums, int target) {
    vector<pii> result;
    int left = 0;
    ll sum = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        while (sum > target && left <= right) {
            sum -= nums[left];
            left++;
        }
        
        if (sum == target) {
            result.push_back({left, right});
        }
    }
    
    return result;
}

// Самая длинная подстрока без повторяющихся символов
int longestSubstringWithoutRepeating(string s) {
    unordered_map<char, int> lastPos;
    int maxLen = 0;
    int left = 0;
    
    for (int right = 0; right < s.size(); right++) {
        if (lastPos.find(s[right]) != lastPos.end()) {
            left = max(left, lastPos[s[right]] + 1);
        }
        lastPos[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Тест 1: максимум в окне
    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> maxWindow = maxSlidingWindow(nums1, 3);
    cout << "Max sliding window (k=3): ";
    for (int x : maxWindow) cout << x << " ";
    cout << "\n";
    
    // Тест 2: минимум в окне
    vector<int> minWindow = minSlidingWindow(nums1, 3);
    cout << "Min sliding window (k=3): ";
    for (int x : minWindow) cout << x << " ";
    cout << "\n";
    
    // Тест 3: сумма подмассива
    vector<ll> sums = sumSlidingWindow(nums1, 3);
    cout << "Sum sliding window (k=3): ";
    for (ll x : sums) cout << x << " ";
    cout << "\n";
    
    // Тест 4: подстрока без повторений
    string s = "abcabcbb";
    cout << "Longest substring without repeating: " << longestSubstringWithoutRepeating(s) << "\n";
    
    return 0;
}
