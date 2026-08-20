#include "../inversions.h"

int main() {
  int ans = count_inversions({6, 10, 4, 8, 15, 2, 1, 3});
  if (ans != 19) {
    cerr << "ans = " << ans << " expected 19\n";
  }
}
