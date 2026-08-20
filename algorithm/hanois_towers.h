#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct step {
  int source;
  int dest;
  int number;
};

void hanois_towers(int source, int dest, int additional, int cnt, vector<step>& steps) {
  if (cnt == 0) {
    return;
  }
  hanois_towers(source, additional, dest, cnt - 1, steps);
  steps.push_back({source, dest, cnt});
  hanois_towers(additional, dest, source, cnt - 1, steps);
}
