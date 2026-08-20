#include <bits/stdc++.h>

using namespace std;

vector<int> compress_array(const vector<int> nums) {
  set<int> unique(nums.begin(), nums.end());
  unordered_map<int, int> mapping;
  int idx = 0;
  for (int key: unique) {
    mapping[key] = idx++;
  }

  vector<int> result;
  result.reserve(nums.size());
  for (int key: nums) {
    result.push_back(mapping[key]);
  }
  return result;
}
