#include <iostream>

void initializeState(char data[], int W) {
  int i;
  data[0] = 'o';
  for (i=1; i<W; ++i) {
    data[i] = '_';
  }
}

void updateState(char data[], int W, int rule) {
  int i;
  for (i=W-1; i>=0; --i) {
    if (rule < 0) {
      if (i == 0) {
	data[i] = '_';
      } else {
	data[i] = data[i-1];
      }
    } else if (rule == 0) {
    } else if (rule == 1) {
    } else if (rule == 2) {
    }
  }
}

void printState(const char data[], int n) {
  int i;
  for (i=0; i<n; ++i) {
    //    data[i] = '?';
    std::cout << data[i];
  }
  std::cout << std::endl;
  //  n = 3;
  //  std::cout << "W inside printState: " << n << std::endl;
}

int main(int argc, char* argv[]) {
  int W = 80;
  int N = 30;
  int i, j;

  int rule=-1;
  char data[W];

  initializeState(data, W);

  printState(data, W);
  for (j=0; j<N; ++j) {
    updateState(data, W, rule);
    printState(data, W);
  }

  return 0;
}
