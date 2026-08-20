#include <bits/stdc++.h>
#include <cassert>

using namespace std;

int merge_sorting(vector<int>& nums, int i, int j, int end) {
  int answer{0};

  if (i + 1 < j) {
    answer += merge_sorting(nums, i, (i + j) / 2, j);
  }

  if (j + 1 < end) {
    answer += merge_sorting(nums, j, (j + end) / 2, end);
  }

  vector<int> tmp;
  int l = i, r = j;
  while (l < j || r < end) {
    if (r == end) {
      tmp.push_back(nums[l]);
      l++;
      continue;
    }
    if (l == j) {
      tmp.push_back(nums[r]);
      r++;
      continue;
    }

    if (nums[l] <= nums[r]) {
      tmp.push_back(nums[l]);
      l++;
    } else {
      tmp.push_back(nums[r]);
      r++;
      answer += (j - l);
    }
  }
  assert(tmp.size() == end - i);
  for (int idx = 0; idx < tmp.size(); idx++) {
    nums[i + idx] = tmp[idx];
  }

  return answer;
}

int count_inversions(vector<int> nums) {
  return merge_sorting(nums, 0, nums.size() / 2, nums.size());
}
