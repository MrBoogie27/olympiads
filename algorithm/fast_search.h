#include <bits/extc++.h>

int binary_search(const std::vector<int>& array, int find) {
  int l = 0, r = array.size();
  while (r - l > 1) {
    int m = l + (r - l) / 2;
    if (array[m] <= find) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

int ternary_search_min(const std::vector<int>& array) {
  int l = 0, r = array.size();
  while (r - l > 2) {
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;

    if (array[m1] > array[m2]) {
      l = m1 + 1;
    } else {
      r = m2;
    }
  }

  int minim = l;
  if (l + 1 < r && array[l + 1] < array[minim]) {
    minim = l + 1;
  }
  return minim;
}

double ternary_search_double_min(std::function<double(double)> f, double left, double right) {
  const double EPS = 1e-9;

  while (right - left > EPS) {
    double m1 = left + (right - left) / 3.0;
    double m2 = right - (right - left) / 3.0;

    if (f(m1) > f(m2)) {
      left = m1;
    } else {
      right = m2;
    }
  }

  return (left + right) / 2.0;
}
