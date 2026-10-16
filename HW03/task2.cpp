#include "convolution.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include <random>
#include <string>

using std::cout;
using std::chrono::duration;
using std::chrono::high_resolution_clock;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    return 1;
  }

  // Get the image dimension and number of threads from the command line.
  const long long parsed_n = std::stoll(argv[1]);
  const int t = std::stoi(argv[2]);

  if (parsed_n <= 0 || t < 1 || t > 20) {
    return 1;
  }

  const std::size_t n = static_cast<std::size_t>(parsed_n);
  constexpr std::size_t m = 3;

  omp_set_num_threads(t);

  float *image = new float[n * n];
  float *mask = new float[m * m];
  float *output = new float[n * n];

  std::mt19937 generator(std::random_device{}());
  std::uniform_real_distribution<float> image_distribution(-10.0f, 10.0f);
  std::uniform_real_distribution<float> mask_distribution(-1.0f, 1.0f);

  for (std::size_t i = 0; i < n * n; ++i) {
    image[i] = image_distribution(generator);
  }

  for (std::size_t i = 0; i < m * m; ++i) {
    mask[i] = mask_distribution(generator);
  }

  const high_resolution_clock::time_point start = high_resolution_clock::now();
  convolve(image, output, n, mask, m);
  const high_resolution_clock::time_point end = high_resolution_clock::now();

  const duration<double, std::milli> duration_ms =
      std::chrono::duration_cast<duration<double, std::milli>>(end - start);

  cout << output[0] << '\n';
  cout << output[n * n - 1] << '\n';
  cout << duration_ms.count() << '\n';

  delete[] image;
  delete[] mask;
  delete[] output;
}
