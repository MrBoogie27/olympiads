#include <bits/stdc++.h>

using namespace std;
#define pb push_back

// typedef long long ll;
// typedef long double ld;
 
const int N = 260;
// const ld EPS = 1e-9;
// const ll INF = 1e18;
// const int MOD = 1e9 + 7;

class Node {
public:
  // vector<size_t> terminated;
  Node* suffix_link{nullptr};
  vector<pair<unsigned char, Node*>> next{};
  bool terminated_size{false};
  // map<char, Node*> automat_next;

  Node* find(unsigned char ch) {
    Node* next_it = nullptr;
    for (int i = 0; i < next.size(); i++) {
      if (next[i].first == ch) {
        next_it = next[i].second;
      }
    }
    return next_it;
  }

  Node* Next(unsigned char ch, Node* root) {
    Node* next_it = find(ch);

    if (next_it != nullptr) {
      return next_it;
    } else if (this == root) {
      return this;
    } else {
      return suffix_link->Next(ch, root);
    }
  }
};

class AutomatonBuilder {
public:
  AutomatonBuilder(int n = 4) {
    words_.reserve(n);
    nodes_.push_back(new Node());
  }

  ~AutomatonBuilder() {
    for (auto node: nodes_) {
      delete node;
    }
  }

  void Add(string string, size_t id) {
    words_.push_back(std::move(string));
    // ids_.push_back(id);
  }

  Node* Build() {
    BuildTrie();
    words_.clear();
    BuildSuffixLinks();
    BuildTerminalLinks();
    return nodes_[0];
  }

  Node* GetRoot() {
    return nodes_[0];
  }

  void BuildTrie() {
    for (size_t i = 0; i < words_.size(); ++i) {
      Node* current = nodes_[0];
      for (unsigned char ch : words_[i]) {
        Node* next_it = current->find(ch);
        if (next_it == nullptr) {
          nodes_.push_back(new Node());
          next_it = nodes_.back();
          current->next.push_back({ch, next_it});
        }
        current = next_it;
      }
      current->terminated_size = true;
    }
  }

  void BuildSuffixLinks() {
    queue<Node*> queue_of_vertexes;
    queue_of_vertexes.push(nodes_[0]);
    while (!queue_of_vertexes.empty()) {
      Node* current = queue_of_vertexes.front();
      if (current == nodes_[0]) {
        current->suffix_link = nodes_[0];
      }
      queue_of_vertexes.pop();
      for (int i = 0; i < current->next.size(); i++) {
        auto [ch, target] = current->next[i];
        queue_of_vertexes.push(target);
        if (current == nodes_[0]) {
          target->suffix_link = nodes_[0];
        } else {
          target->suffix_link = current->suffix_link->Next(ch, nodes_[0]);
        }
      }
    }
  }

  void BuildTerminalLinks() {
    queue<Node*> queue_of_vertexes;
    queue_of_vertexes.push(nodes_[0]);
    while (!queue_of_vertexes.empty()) {
      Node* current = queue_of_vertexes.front();
      queue_of_vertexes.pop();
      Node* terminal_link = nullptr;
      if (current == nodes_[0]) {
        terminal_link = nodes_[0];
      } else {
        terminal_link = current->suffix_link;
      }
      current->terminated_size |= terminal_link->terminated_size;
      for (int i = 0; i < current->next.size(); i++) {
        auto target = current->next[i].second;
        queue_of_vertexes.push(target);
      }
    }
  }

  vector<string> words_;
  vector<Node*> nodes_;
};

void solve() {
    int n;
    string s;
    getline(cin, s);
    n = atoi(s.c_str());
    AutomatonBuilder builder(n);
    for (int i = 0; i < n; i++) {
      getline(cin, s);
      // cout << s << endl;
      reverse(s.begin(), s.end());
      builder.Add(std::move(s), i);
    }
    Node* root = builder.Build();

    getline(cin, s);
    n = atoi(s.c_str());

    pair<int, int> answer = {-1, -1};
    vector<string> r(n);
    for (int i = 0; i < n; i++) {
      getline(cin, r[i]);
    }
    Node* current = root;
    for (int i = n - 1; i >= 0; i--) {
      for(int j = r[i].size() - 1; j >= 0; j--) {
        current = current->Next(r[i][j], root);
        if (current->terminated_size) {
          answer = {i + 1, j + 1};
        }
      }
    }
    if (answer.first != -1) {
      cout << answer.first << " " << answer.second << endl;
    } else {
      cout << "Passed" << endl;
    }
}
