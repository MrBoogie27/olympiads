#include "../aho_corasik.h"

using namespace std;

void test_aho_corasik_single_pattern() {
  cout << "Testing Aho-Corasick single pattern...\n";
  
  AutomatonBuilder builder(1);
  builder.Add("abc", 0);
  Node* root = builder.Build();
  
  // Проверяем, что конечное состояние помечено
  Node* current = root;
  for (char ch : string("abc")) {
    current = current->Next(ch, root);
  }
  assert(current->terminated_size == true);
  
  cout << "✓ Aho-Corasick single pattern PASSED\n";
}

void test_aho_corasik_multiple_patterns() {
  cout << "Testing Aho-Corasick multiple patterns...\n";
  
  AutomatonBuilder builder(3);
  builder.Add("he", 0);
  builder.Add("she", 1);
  builder.Add("her", 2);
  Node* root = builder.Build();
  
  // Проверяем 'he'
  Node* current = root;
  current = current->Next('h', root);
  current = current->Next('e', root);
  assert(current->terminated_size == true);
  
  // Проверяем 'she'
  current = root;
  current = current->Next('s', root);
  current = current->Next('h', root);
  current = current->Next('e', root);
  assert(current->terminated_size == true);
  
  // Проверяем 'her'
  current = root;
  current = current->Next('h', root);
  current = current->Next('e', root);
  current = current->Next('r', root);
  assert(current->terminated_size == true);
  
  cout << "✓ Aho-Corasick multiple patterns PASSED\n";
}

void test_aho_corasik_overlapping_patterns() {
  cout << "Testing Aho-Corasick overlapping patterns...\n";
  
  AutomatonBuilder builder(2);
  builder.Add("ab", 0);
  builder.Add("abc", 1);
  Node* root = builder.Build();
  
  // 'ab' должен быть терминальным
  Node* current = root;
  current = current->Next('a', root);
  current = current->Next('b', root);
  assert(current->terminated_size == true);
  
  // 'abc' должен быть терминальным
  current = current->Next('c', root);
  assert(current->terminated_size == true);
  
  cout << "✓ Aho-Corasick overlapping patterns PASSED\n";
}

void test_aho_corasik_prefix_patterns() {
  cout << "Testing Aho-Corasick prefix patterns...\n";
  
  AutomatonBuilder builder(2);
  builder.Add("test", 0);
  builder.Add("te", 1);
  Node* root = builder.Build();
  
  // 'te' терминален
  Node* current = root;
  current = current->Next('t', root);
  current = current->Next('e', root);
  assert(current->terminated_size == true);
  
  // Продолжаем до 'test' - он также терминален
  current = current->Next('s', root);
  current = current->Next('t', root);
  assert(current->terminated_size == true);
  
  cout << "✓ Aho-Corasick prefix patterns PASSED\n";
}

void test_aho_corasik_single_char_pattern() {
  cout << "Testing Aho-Corasick single character patterns...\n";
  
  AutomatonBuilder builder(3);
  builder.Add("a", 0);
  builder.Add("b", 1);
  builder.Add("c", 2);
  Node* root = builder.Build();
  
  // Проверяем каждый символ
  Node* current = root->Next('a', root);
  assert(current->terminated_size == true);
  
  current = root->Next('b', root);
  assert(current->terminated_size == true);
  
  current = root->Next('c', root);
  assert(current->terminated_size == true);
  
  cout << "✓ Aho-Corasick single character PASSED\n";
}

void test_aho_corasik_similar_patterns() {
  cout << "Testing Aho-Corasick similar patterns...\n";
  
  AutomatonBuilder builder(4);
  builder.Add("cat", 0);
  builder.Add("car", 1);
  builder.Add("card", 2);
  builder.Add("care", 3);
  Node* root = builder.Build();
  
  // 'cat'
  Node* current = root;
  current = current->Next('c', root);
  current = current->Next('a', root);
  current = current->Next('t', root);
  assert(current->terminated_size == true);
  
  // 'car' (общий префикс 'ca')
  current = root;
  current = current->Next('c', root);
  current = current->Next('a', root);
  current = current->Next('r', root);
  assert(current->terminated_size == true);
  
  // 'care'
  current = current->Next('e', root);
  assert(current->terminated_size == true);
  
  cout << "✓ Aho-Corasick similar patterns PASSED\n";
}

void test_aho_corasik_long_pattern() {
  cout << "Testing Aho-Corasick long pattern...\n";
  
  string pattern = "abcdefghij";
  AutomatonBuilder builder(1);
  builder.Add(pattern, 0);
  Node* root = builder.Build();
  
  // Проходим по всему паттерну
  Node* current = root;
  for (char ch : pattern) {
    current = current->Next(ch, root);
  }
  assert(current->terminated_size == true);
  
  cout << "✓ Aho-Corasick long pattern PASSED\n";
}

int main() {
  cout << "\n=== AHO_CORASIK TESTS ===\n\n";
  
  test_aho_corasik_single_pattern();
  test_aho_corasik_multiple_patterns();
  test_aho_corasik_overlapping_patterns();
  test_aho_corasik_prefix_patterns();
  test_aho_corasik_single_char_pattern();
  test_aho_corasik_similar_patterns();
  test_aho_corasik_long_pattern();
  
  cout << "\n✓✓✓ ALL AHO_CORASIK TESTS PASSED ✓✓✓\n\n";
  return 0;
}
