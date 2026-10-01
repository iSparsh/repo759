#include "scan.h"
#include <chrono>
#include <iostream>
#include <random>
#include <string>

using std::cout;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }

  high_resolution_clock::time_point start;
  high_resolution_clock::time_point end;
  duration<double, std::milli> duration_ms;

  // (i) Create an array of `n` random floats between -1.0 and 1.0.
  const std::size_t n = std::stoull(argv[1]);
  float *arr = new float[n];

  std::mt19937 generator(std::random_device{}());
  std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

  for (std::size_t i = 0; i < n; ++i) {
    arr[i] = distribution(generator);
  }

  // (ii) scanning array with the scan function
  float *output = new float[n];

  // (iii) time the scan function
  // Get the starting timestamp
  start = high_resolution_clock::now();
  scan(arr, output, n);
  end = high_resolution_clock::now();
  // printing in milliseconds
  duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);
  // Durations are converted to milliseconds already thanks to
  // std::chrono::duration_cast
  cout << duration_ms.count() << '\n';

  // (iv) Prints the first element of the output scanned array
  cout << output[0] << '\n';

  // (v) Prints the last element of the output scanned array
  cout << output[n - 1] << '\n';

  // (vi) freeing memory
  delete[] arr;
  delete[] output;

  return 0;
}
