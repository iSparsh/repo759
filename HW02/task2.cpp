#include "convolution.h"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>
#include <string>

using std::cout;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return 1;
  }

  high_resolution_clock::time_point start;
  high_resolution_clock::time_point end;
  duration<double, std::milli> duration_ms;

  const std::size_t n = std::stoull(argv[1]);
  const std::size_t m = std::stoull(argv[2]);

  // (i) create nxn matrix
  float *image = new float[n * n];

  std::mt19937 generator(std::random_device{}());
  std::uniform_real_distribution<float> image_distribution(-10.0f, 10.0f);

  for (std::size_t i = 0; i < n * n; ++i) {
    image[i] = image_distribution(generator);
  }

  // (ii) create mxm matrix
  float *mask = new float[m * m];

  std::uniform_real_distribution<float> mask_distribution(-1.0f, 1.0f);

  for (std::size_t i = 0; i < m * m; ++i) {
    mask[i] = mask_distribution(generator);
  }

  // creating output matrix
  float *output = new float[n * n];

  start = high_resolution_clock::now();
  convolve(image, output, n, mask, m);
  end = high_resolution_clock::now();

  // duration in milliseconds.
  duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  // (iv) time taken by convolve function
  cout << duration_ms.count() << '\n';

  // (v) Prints the first element
  cout << output[0] << '\n';

  // (vi) Prints the last element.
  cout << output[n * n - 1] << '\n';

  // (vii) freeing memory
  delete[] image;
  delete[] mask;
  delete[] output;

  return 0;
}
