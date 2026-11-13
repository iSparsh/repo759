#include <cstdio>
#include <cuda.h>

// Factorial of integers from 1 to 8 in 1 block with 8 threads.
__global__ void factorialKernel() {
  int n = threadIdx.x + 1; // id 0 -> no. 1
  int result = 1;
  for (int k = 2; k <= n; k++) {
    result *= k;
  }
  std::printf("%d!=%d\n", n, result);
}

int main() {
  factorialKernel<<<1, 8>>>();
  cudaDeviceSynchronize();
  return 0;
}
