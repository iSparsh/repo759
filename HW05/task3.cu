#include "vscale.cuh"
#include <cuda.h>
#include <iostream>
#include <random>
#include <string>

// Threads per block. The assignment uses 512; the slurm sweep overrides this
// with -DTHREADS_PER_BLOCK=16 to produce the second scaling curve.
#ifndef THREADS_PER_BLOCK
#define THREADS_PER_BLOCK 512
#endif

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }
  int n = std::stoi(argv[1]);

  float *hA = new float[n];

  std::mt19937 generator(std::random_device{}());
  std::uniform_real_distribution<float> hA_dist(-10.0f, 10.0f);

  for (int i = 0; i < n; ++i) {
    hA[i] = hA_dist(generator);
  }

  float *hB = new float[n];

  std::uniform_real_distribution<float> hB_dist(0.0f, 1.0f);

  for (int i = 0; i < n; ++i) {
    hB[i] = hB_dist(generator);
  }

  // getting a, b in device
  float *dA;
  float *dB;
  const size_t bytes = n * sizeof(float);
  cudaMalloc((void **)&dA, bytes);
  cudaMemcpy(dA, hA, bytes, cudaMemcpyHostToDevice);
  cudaMalloc((void **)&dB, bytes);
  cudaMemcpy(dB, hB, bytes, cudaMemcpyHostToDevice);

  // --- timing kernel execution ---
  cudaEvent_t start;
  cudaEvent_t stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  cudaEventRecord(start);

  // 1-D config with THREADS_PER_BLOCK (512) threads per block
  vscale<<<(n + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK,
           THREADS_PER_BLOCK>>>(dA, dB, n);

  cudaEventRecord(stop);
  cudaEventSynchronize(stop);

  // Get the elapsed time in milliseconds
  float ms;
  cudaEventElapsedTime(&ms, start, stop);

  cudaMemcpy(hB, dB, bytes, cudaMemcpyDeviceToHost);

  std::cout << ms << "\n";
  std::cout << hB[0] << "\n";
  std::cout << hB[n - 1] << "\n";

  delete[] hA;
  delete[] hB;
  cudaFree(dA);
  cudaFree(dB);
  return 0;
}
