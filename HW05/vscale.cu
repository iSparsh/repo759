#include "vscale.cuh"
#include <cuda.h>

__global__ void vscale(const float *a, float *b, unsigned int n) {
  unsigned int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i < n) {
    b[i] = a[i] * b[i];
  }
}
