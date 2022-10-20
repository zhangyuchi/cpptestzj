#include <iostream>
#include <cstddef>

struct Storage {
  char a;
  int b;
  double c;
  long long d;
};

struct alignas(std::max_align_t) AlignasStorage {
  char a;
  int b;
  double c;
  long long d;
};

int main() {
  std::cout << alignof(Storage) << "," << sizeof(Storage) << std::endl;
  std::cout << alignof(AlignasStorage) << "," << sizeof(AlignasStorage) << std::endl;
  return 0;
}