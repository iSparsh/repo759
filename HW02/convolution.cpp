#include "convolution.h"

// Computes the result of applying a mask to an image as in the convolution
// process described in HW02.pdf. image is an nxn grid stored in row-major
// order. mask is an mxm grid stored in row-major order. Stores the result in
// output, which is an nxn grid stored in row-major order
void convolve(const float *image, float *output, std::size_t n,
              const float *mask, std::size_t m) {
  const int half = static_cast<int>(m / 2);
  const int image_size = static_cast<int>(n);

  for (std::size_t x = 0; x < n; ++x) {
    for (std::size_t y = 0; y < n; ++y) {
      float sum = 0.0f;

      for (std::size_t i = 0; i < m; ++i) {
        for (std::size_t j = 0; j < m; ++j) {
          const int row = static_cast<int>(x) + static_cast<int>(i) - half;
          const int column = static_cast<int>(y) + static_cast<int>(j) - half;

          const bool row_outside = row < 0 || row >= image_size;
          const bool column_outside = column < 0 || column >= image_size;

          float image_value;
          if (row_outside && column_outside) {
            image_value = 0.0f;
          } else if (row_outside || column_outside) {
            image_value = 1.0f;
          } else {
            const std::size_t image_index = static_cast<std::size_t>(row) * n +
                                            static_cast<std::size_t>(column);
            image_value = image[image_index];
          }

          sum += mask[i * m + j] * image_value;
        }
      }

      output[x * n + y] = sum;
    }
  }
}
