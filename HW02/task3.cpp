#include "matmul.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

using std::cout;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main() {
  // defining all timing variables
  high_resolution_clock::time_point start;
  high_resolution_clock::time_point end;
  duration<double, std::milli> duration_ms;

  // setting up A, B, C matrices
  const unsigned int n = 1024;
  double *A = new double[n * n];
  double *B = new double[n * n];
  std::vector<double> C(n * n, 0.0);

  // generating A, B vectors
  std::mt19937 generator(std::random_device{}());
  // distribution for A, B values
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  // generating A, B values
  for (unsigned int i = 0; i < n * n; ++i) {
    A[i] = dist(generator);
    B[i] = dist(generator);
  }

  // store A, B in vector form
  std::vector<double> A_vec(n * n);
  std::vector<double> B_vec(n * n);
  for (unsigned int i = 0; i < n * n; ++i) {
    A_vec[i] = A[i];
    B_vec[i] = B[i];
  }

  // print the number of rows in A, B
  cout << n << "\n";

  // mmul1
  start = high_resolution_clock::now();
  mmul1(A, B, C.data(), n);
  end = high_resolution_clock::now();
  // duration in milliseconds.
  duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  cout << duration_ms.count() << '\n';
  cout << C[n * n - 1] << '\n';

  // zeroing C
  std::fill(C.begin(), C.end(), 0.0);

  // mmul2
  start = high_resolution_clock::now();
  mmul2(A, B, C.data(), n);
  end = high_resolution_clock::now();
  // duration in milliseconds.
  duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  cout << duration_ms.count() << '\n';
  cout << C[n * n - 1] << '\n';

  // zeroing C
  std::fill(C.begin(), C.end(), 0.0);

  // mmul3
  start = high_resolution_clock::now();
  mmul3(A, B, C.data(), n);
  end = high_resolution_clock::now();
  // duration in milliseconds.
  duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  cout << duration_ms.count() << '\n';
  cout << C[n * n - 1] << '\n';

  // zeroing C
  std::fill(C.begin(), C.end(), 0.0);

  // mmul4

  start = high_resolution_clock::now();
  mmul4(A_vec, B_vec, C.data(), n);
  end = high_resolution_clock::now();
  // duration in milliseconds.
  duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  cout << duration_ms.count() << '\n';
  cout << C[n * n - 1] << '\n';

  // freeing memory
  delete[] A;
  delete[] B;
  return 0;
}
