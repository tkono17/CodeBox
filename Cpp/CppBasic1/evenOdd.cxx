#include <iostream>
#include <cmath>
#include <cstdlib>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <number>" << std::endl;
    return -1;
  }

  int a = std::atoi(argv[1]);
  int r = a % 2;

  if (r == 0) {
    std::cout << "Number " << a << " is even" << std::endl;
  } else {
    std::cout << "Number " << a << " is odd" << std::endl;
  }

  return 0;
}
