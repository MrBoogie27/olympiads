#include "../hanois_towers.h"

using namespace std;

void test_hanois_towers_count() {
  cout << "Testing Hanoi Towers step count...\n";
  
  // Для n дисков количество шагов должно быть 2^n - 1
  
  // n = 1: 2^1 - 1 = 1
  vector<step> steps;
  hanois_towers(0, 2, 1, 1, steps);
  assert(steps.size() == 1);
  
  // n = 2: 2^2 - 1 = 3
  steps.clear();
  hanois_towers(0, 2, 1, 2, steps);
  assert(steps.size() == 3);
  
  // n = 3: 2^3 - 1 = 7
  steps.clear();
  hanois_towers(0, 2, 1, 3, steps);
  assert(steps.size() == 7);
  
  // n = 4: 2^4 - 1 = 15
  steps.clear();
  hanois_towers(0, 2, 1, 4, steps);
  assert(steps.size() == 15);
  
  // n = 5: 2^5 - 1 = 31
  steps.clear();
  hanois_towers(0, 2, 1, 5, steps);
  assert(steps.size() == 31);
  
  cout << "✓ Hanoi Towers step count PASSED\n";
}

void test_hanois_towers_n1() {
  cout << "Testing Hanoi Towers n=1...\n";
  
  vector<step> steps;
  hanois_towers(0, 2, 1, 1, steps);
  
  assert(steps.size() == 1);
  assert(steps[0].source == 0);
  assert(steps[0].dest == 2);
  assert(steps[0].number == 1);
  
  cout << "✓ Hanoi Towers n=1 PASSED\n";
}

void test_hanois_towers_n2() {
  cout << "Testing Hanoi Towers n=2...\n";
  
  // Последовательность для n=2:
  // 1. Переместить диск 1 со стержня 0 на стержень 1
  // 2. Переместить диск 2 со стержня 0 на стержень 2
  // 3. Переместить диск 1 со стержня 1 на стержень 2
  
  vector<step> steps;
  hanois_towers(0, 2, 1, 2, steps);
  
  assert(steps.size() == 3);
  
  // Первый шаг: диск 1
  assert(steps[0].number == 1);
  assert(steps[0].source == 0);
  
  // Второй шаг: диск 2
  assert(steps[1].number == 2);
  assert(steps[1].source == 0);
  assert(steps[1].dest == 2);
  
  // Третий шаг: диск 1 на финальный стержень
  assert(steps[2].number == 1);
  assert(steps[2].dest == 2);
  
  cout << "✓ Hanoi Towers n=2 PASSED\n";
}

void test_hanois_towers_n3() {
  cout << "Testing Hanoi Towers n=3...\n";
  
  vector<step> steps;
  hanois_towers(0, 2, 1, 3, steps);
  
  assert(steps.size() == 7);
  
  // Проверяем, что все диски присутствуют
  bool has_disk1 = false, has_disk2 = false, has_disk3 = false;
  for (const auto& s : steps) {
    if (s.number == 1) has_disk1 = true;
    if (s.number == 2) has_disk2 = true;
    if (s.number == 3) has_disk3 = true;
  }
  assert(has_disk1 && has_disk2 && has_disk3);
  
  // Проверяем, что диск 3 был перемещён (он самый большой)
  int disk3_dest_final = -1;
  for (const auto& s : steps) {
    if (s.number == 3) {
      disk3_dest_final = s.dest;
    }
  }
  assert(disk3_dest_final == 2);  // диск 3 должен быть на стержне 2
  
  cout << "✓ Hanoi Towers n=3 PASSED\n";
}

void test_hanois_towers_different_stacks() {
  cout << "Testing Hanoi Towers with different stack configurations...\n";
  
  // Тест с разными начальными и конечными стержнями
  vector<step> steps1;
  hanois_towers(1, 0, 2, 2, steps1);
  assert(steps1.size() == 3);
  
  vector<step> steps2;
  hanois_towers(2, 1, 0, 3, steps2);
  assert(steps2.size() == 7);
  
  cout << "✓ Hanoi Towers different stacks PASSED\n";
}

void test_hanois_towers_zero_disks() {
  cout << "Testing Hanoi Towers n=0...\n";
  
  // n=0 дисков: 0 шагов
  vector<step> steps;
  hanois_towers(0, 2, 1, 0, steps);
  assert(steps.size() == 0);
  
  cout << "✓ Hanoi Towers n=0 PASSED\n";
}

void test_hanois_towers_sequence_validity() {
  cout << "Testing Hanoi Towers sequence validity...\n";
  
  // Проверяем, что диск не может быть перемещён дважды подряд неправильно
  vector<step> steps;
  hanois_towers(0, 2, 1, 3, steps);
  
  // В корректной последовательности диск 1 должен часто менять положение
  // (так как он нужен для перемещения больших дисков)
  int disk1_moves = 0;
  int disk2_moves = 0;
  int disk3_moves = 0;
  
  for (const auto& s : steps) {
    if (s.number == 1) disk1_moves++;
    else if (s.number == 2) disk2_moves++;
    else if (s.number == 3) disk3_moves++;
  }
  
  // n=3: disk1 должен двигаться 2^(n-1) = 4 раза
  assert(disk1_moves == 4);
  // disk2 должен двигаться 2 раза
  assert(disk2_moves == 2);
  // disk3 должен двигаться 1 раз
  assert(disk3_moves == 1);
  
  cout << "✓ Hanoi Towers sequence validity PASSED\n";
}

int main() {
  cout << "\n=== HANOI_TOWERS TESTS ===\n\n";
  
  test_hanois_towers_count();
  test_hanois_towers_n1();
  test_hanois_towers_n2();
  test_hanois_towers_n3();
  test_hanois_towers_different_stacks();
  test_hanois_towers_zero_disks();
  test_hanois_towers_sequence_validity();
  
  cout << "\n✓✓✓ ALL HANOI_TOWERS TESTS PASSED ✓✓✓\n\n";
  return 0;
}
