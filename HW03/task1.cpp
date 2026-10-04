#include "matmul.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include <random>

using std::cout;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return 1;
  }

  // defining all timing variables
  high_resolution_clock::time_point start;
  high_resolution_clock::time_point end;
  duration<double, std::milli> duration_ms;

  // getting n and t from cmdargs
  const std::size_t n = std::stoi(argv[1]);
  const int t = std::stoi(argv[2]);

  if ((t < 1) || (t > 20) || n <= 0) {
    return 1;
  }

  // setting number of parallel threads = t
  omp_set_num_threads(t);

  // setting up A, B, C matrices
  float *A = new float[n * n];
  float *B = new float[n * n];
  float *C = new float[n * n]();

  // generating A, B vectors
  std::mt19937 generator(std::random_device{}());
  // distribution for A, B values
  std::uniform_real_distribution<float> dist(0.0, 1.0);

  // generating A, B values
  for (std::size_t i = 0; i < n * n; ++i) {
    A[i] = dist(generator);
    B[i] = dist(generator);
  }

  start = high_resolution_clock::now();
  mmul(A, B, C, n);
  end = high_resolution_clock::now();
  // duration in milliseconds.
  duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  cout << C[0] << '\n';
  cout << C[n * n - 1] << '\n';
  cout << duration_ms.count() << '\n';

  delete[] A;
  delete[] B;
  delete[] C;
}
