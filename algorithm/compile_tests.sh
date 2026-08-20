#!/bin/bash

# compile_tests.sh - Автоматический запуск всех тестов в папке algorithm/tests/

set -e  # Выход при ошибке

TESTS_DIR="./tests"
BUILD_DIR="$TESTS_DIR/build"
CXX="g++"
CXXFLAGS="-std=c++17 -Wall -Wextra -O2"

# Создаём директорию build если её нет
mkdir -p "$BUILD_DIR"

echo "=========================================="
echo "🔨 Компиляция и запуск всех тестов (g++ C++17)"
echo "=========================================="
echo ""

# Цвета для вывода
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0

# Функция для запуска одного теста
run_test() {
  local test_name=$1
  local test_file=$2
  local test_executable=$3
  
  echo -e "${YELLOW}Testing: $test_name${NC}"
  
  # Удаляем старый файл перед компиляцией
  rm -f "$test_executable"
  
  # Компилируем
  if ! $CXX $CXXFLAGS "$test_file" -o "$test_executable" 2>&1; then
    echo -e "${RED}✗ COMPILATION FAILED${NC}"
    rm -f "$test_executable"  # Удалить после ошибки
    FAILED=$((FAILED + 1))
    echo ""
    return 1
  fi
  
  # Запускаем
  if ! "$test_executable" 2>&1; then
    echo -e "${RED}✗ TEST FAILED${NC}"
    rm -f "$test_executable"  # Удалить после ошибки
    FAILED=$((FAILED + 1))
    echo ""
    return 1
  fi
  
  echo -e "${GREEN}✓ PASSED${NC}"
  PASSED=$((PASSED + 1))
  echo ""
  rm -f "$test_executable"
}

# Запускаем все тесты
run_test "fast_search" "$TESTS_DIR/fast_search_test.cpp" "$BUILD_DIR/fast_search_test"
run_test "geometry" "$TESTS_DIR/geometry_test.cpp" "$BUILD_DIR/geometry_test"
run_test "fenwick_tree" "$TESTS_DIR/fenwick_tree_test.cpp" "$BUILD_DIR/fenwick_tree_test"
run_test "hanois_towers" "$TESTS_DIR/hanois_towers_test.cpp" "$BUILD_DIR/hanois_towers_test"
run_test "aho_corasik" "$TESTS_DIR/aho_corasik_test.cpp" "$BUILD_DIR/aho_corasik_test"

# Итоговый отчёт
echo "=========================================="
echo "📊 ИТОГОВЫЙ ОТЧЁТ"
echo "=========================================="
echo -e "✓ ${GREEN}Успешно: $PASSED${NC}"
echo -e "✗ ${RED}Неудачно: $FAILED${NC}"
echo "=========================================="
echo ""

if [ $FAILED -eq 0 ]; then
  echo -e "${GREEN}🎉 ВСЕ ТЕСТЫ ПРОЙДЕНЫ! 🎉${NC}"
  exit 0
else
  echo -e "${RED}❌ НЕКОТОРЫЕ ТЕСТЫ НЕ ПРОЙДЕНЫ${NC}"
  exit 1
fi
