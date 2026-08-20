#include "../compress_array.h"

int main() {
  vector<int> answer = compress_array({-4, 8, 15, 0, 34, 2, 5, 8, -4});
  vector<int> expected = {0, 4, 5, 1, 6, 2, 3, 4, 0};

  for (int idx = 0; idx < answer.size(); idx++) {
    if (answer[idx] != expected[idx]) {
      cerr << "expected = " << expected[idx] << " answer = " << answer[idx] << "\n";
    }
  }
}
