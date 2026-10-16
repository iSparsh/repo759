#include "msort.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include <random>
#include <string>

using std::cout;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    return 1;
  }

  const long long parsed_n = std::stoll(argv[1]);
  const int t = std::stoi(argv[2]);
  const long long parsed_threshold = std::stoll(argv[3]);

  if (parsed_n <= 0 || t < 1 || t > 20 || parsed_threshold <= 0) {
    return 1;
  }

  const std::size_t n = static_cast<std::size_t>(parsed_n);
  const std::size_t threshold = static_cast<std::size_t>(parsed_threshold);

  omp_set_num_threads(t);

  int *arr = new int[n];
  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(-1000, 1000);

  for (std::size_t i = 0; i < n; ++i) {
    arr[i] = distribution(generator);
  }

  const high_resolution_clock::time_point start = high_resolution_clock::now();
  msort(arr, n, threshold);
  const high_resolution_clock::time_point end = high_resolution_clock::now();

  const duration<double, std::milli> duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  cout << arr[0] << '\n';
  cout << arr[n - 1] << '\n';
  cout << duration_ms.count() << '\n';

  delete[] arr;
}
