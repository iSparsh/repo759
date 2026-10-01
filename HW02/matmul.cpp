#include "matmul.h"

void mmul1(const double *A, const double *B, double *C, const unsigned int n) {
  // outer loop - rows of C
  for (unsigned int i = 0; i < n; ++i) {
    // inner loop - columns of C
    for (unsigned int j = 0; j < n; ++j) {
      // innermost loop sweeping k to carry out the dot product
      for (unsigned int k = 0; k < n; ++k) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}

void mmul2(const double *A, const double *B, double *C, const unsigned int n) {
  // three loops, but two innermost loops swapped relative to mmul1
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int k = 0; k < n; ++k) {
      for (unsigned int j = 0; j < n; ++j) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}

void mmul3(const double *A, const double *B, double *C, const unsigned int n) {
  // outermost loop of mmul1 becomes the innermost loop, and other loops don't
  // change relative positions
  for (unsigned int j = 0; j < n; ++j) {
    for (unsigned int k = 0; k < n; ++k) {
      for (unsigned int i = 0; i < n; ++i) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}

void mmul4(const std::vector<double> &A, const std::vector<double> &B,
           double *C, const unsigned int n) {
  // vector version of mmul1
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j) {
      for (unsigned int k = 0; k < n; ++k) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}
