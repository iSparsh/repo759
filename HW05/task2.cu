#include <cuda.h>
#include <iostream>
#include <random>

__global__ void linearAdd(int *dA, int a) {
  int x = threadIdx.x;
  int y = blockIdx.x;
  int idx = y * blockDim.x + x;
  dA[idx] = a * x + y;
}

int main() {
  const int N = 16;
  const int bytes = N * sizeof(int);

  int *dA;
  cudaMalloc((void **)&dA, bytes);

  // generating random integer a
  std::random_device entropy_source;
  std::mt19937 generator(entropy_source());
  std::uniform_int_distribution<int> dist(0, 512);
  int a = dist(generator);

  // launch kernel w/ 2 blocks 8 thread each
  linearAdd<<<2, 8>>>(dA, a);

  int hA[N];
  cudaMemcpy(hA, dA, bytes, cudaMemcpyDeviceToHost);
  std::cout << hA[0];
  for (int i = 1; i < N; ++i) {
    std::cout << " " << hA[i];
  }
  std::cout << '\n';
  cudaFree(dA);
  return 0;
}
