#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Print argument list" << std::endl;

  for (int i=0; i<argc; ++i) {
    std::cout << "Argument[" << i << "] ==> " << argv[i] << std::endl;
  }
  return 0;
}
