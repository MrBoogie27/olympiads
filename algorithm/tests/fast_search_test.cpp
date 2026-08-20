#include "../fast_search.h"

using namespace std;

void test_binary_search() {
  cout << "Testing binary_search()...\n";

  // Тест 1: поиск в отсортированном массиве
  vector<int> arr1 = {1, 3, 3, 3, 5, 7, 9};
  cerr << binary_search(arr1, 3) << endl;
  assert(binary_search(arr1, 3) == 3);
  assert(binary_search(arr1, 1) == 0);
  assert(binary_search(arr1, 5) == 4);

  // Тест 2: элемент не найден
  assert(binary_search(arr1, 0) == 0);
  assert(binary_search(arr1, 8) == 5);
  assert(binary_search(arr1, 10) == 6);
  
  // Тест 3: пустой массив
  vector<int> arr_empty = {};
  assert(binary_search(arr_empty, 5) == 0);
  
  // Тест 4: один элемент
  vector<int> arr_one = {5};
  assert(binary_search(arr_one, 5) == 0);
  assert(binary_search(arr_one, 3) == 0);
  assert(binary_search(arr_one, 7) == 0);
  
  // Тест 5: дубликаты
  vector<int> arr_dups = {1, 1, 1, 1, 2, 2, 3};
  assert(binary_search(arr_dups, 1) == 3);
  assert(binary_search(arr_dups, 2) == 5);
  assert(binary_search(arr_dups, 3) == 6);

  cout << "✓ binary_search PASSED\n";
}

void test_ternary_search_min() {
  cout << "Testing ternary_search_min()...\n";
  
  // Тест 1: унимодальный массив с минимумом в середине
  vector<int> arr1 = {10, 5, 2, 1, 3, 7, 15};
  int idx = ternary_search_min(arr1);
  assert(arr1[idx] == 1);
  assert(idx == 3);
  
  // Тест 2: минимум в начале
  vector<int> arr2 = {1, 2, 5, 10, 20};
  idx = ternary_search_min(arr2);
  assert(arr2[idx] == 1);
  assert(idx == 0);
  
  // Тест 3: минимум в конце
  vector<int> arr3 = {20, 10, 5, 2, 1};
  idx = ternary_search_min(arr3);
  assert(arr3[idx] == 1);
  assert(idx == 4);
  
  // Тест 4: два элемента
  vector<int> arr4 = {5, 2};
  idx = ternary_search_min(arr4);
  assert(arr4[idx] == 2);
  
  // Тест 5: один элемент
  vector<int> arr5 = {42};
  idx = ternary_search_min(arr5);
  assert(arr5[idx] == 42);
  assert(idx == 0);
  
  // Тест 6: все одинаковые
  vector<int> arr6 = {5, 5, 5, 5, 5};
  idx = ternary_search_min(arr6);
  assert(arr6[idx] == 5);
  assert(idx == 0);
  
  cout << "✓ ternary_search_min PASSED\n";
}

void test_ternary_search_double() {
  cout << "Testing ternary_search_double()...\n";
  
  // Тест 1: парабола f(x) = x^2 - 4x + 5 (минимум в x=2, f(2)=1)
  auto f1 = [](double x) { return x*x - 4*x + 5; };
  double x = ternary_search_double_min(f1, 0.0, 10.0);
  assert(abs(x - 2.0) < 0.01);
  
  // Тест 2: парабола f(x) = (x-5)^2 (минимум в x=5)
  auto f2 = [](double x) { return (x - 5.0) * (x - 5.0); };
  x = ternary_search_double_min(f2, 0.0, 10.0);
  assert(abs(x - 5.0) < 0.01);
  
  // Тест 3: кубическая функция f(x) = (x-3)^2 + 1 (минимум в x=3, f(3)=1)
  auto f3 = [](double x) { return (x - 3.0) * (x - 3.0) + 1.0; };
  x = ternary_search_double_min(f3, 0.0, 6.0);
  assert(abs(x - 3.0) < 0.01);
  
  // Тест 4: линейная функция на интервале (минимум в левой границе)
  auto f4 = [](double x) { return x; };
  x = ternary_search_double_min(f4, 0.0, 10.0);
  assert(x < 1.0);
  
  // Тест 5: функция с минимумом на краю интервала
  auto f5 = [](double x) { return x*x; };
  x = ternary_search_double_min(f5, -5.0, 5.0);
  assert(abs(x) < 0.1);
  
  cout << "✓ ternary_search_double PASSED\n";
}

int main() {
  cout << "\n=== FAST_SEARCH TESTS ===\n\n";
  
  test_binary_search();
  test_ternary_search_min();
  test_ternary_search_double();
  
  cout << "\n✓✓✓ ALL FAST_SEARCH TESTS PASSED ✓✓✓\n\n";
  return 0;
}
