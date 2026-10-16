#include "msort.h"

namespace {

// Sort arr[begin:end) serially without making recursive calls.
void insertionSort(int *arr, const std::size_t begin, const std::size_t end) {
  for (std::size_t i = begin + 1; i < end; ++i) {
    const int value = arr[i];
    std::size_t j = i;

    while (j > begin && arr[j - 1] > value) {
      arr[j] = arr[j - 1];
      --j;
    }

    arr[j] = value;
  }
}

// Merge the sorted ranges arr[begin:middle) and arr[middle:end).
void merge(int *arr, int *buffer, const std::size_t begin,
           const std::size_t middle, const std::size_t end) {
  std::size_t left = begin;
  std::size_t right = middle;
  std::size_t output = begin;

  while (left < middle && right < end) {
    if (arr[left] <= arr[right]) {
      buffer[output++] = arr[left++];
    } else {
      buffer[output++] = arr[right++];
    }
  }

  while (left < middle) {
    buffer[output++] = arr[left++];
  }

  while (right < end) {
    buffer[output++] = arr[right++];
  }

  for (std::size_t i = begin; i < end; ++i) {
    arr[i] = buffer[i];
  }
}

void recursiveSort(int *arr, int *buffer, const std::size_t begin,
                   const std::size_t end, const std::size_t threshold) {
  const std::size_t length = end - begin;

  if (length <= 1) {
    return;
  }

  if (length <= threshold) {
    insertionSort(arr, begin, end);
    return;
  }

  const std::size_t middle = begin + length / 2;

#pragma omp task default(none) shared(arr, buffer)                             \
    firstprivate(begin, middle, threshold)
  recursiveSort(arr, buffer, begin, middle, threshold);

  // Keep the current thread busy sorting the other half while the left half
  // is available as a task to the rest of the team as shown in wikipedia.
  recursiveSort(arr, buffer, middle, end, threshold);

  // Both halves must be completely sorted before they can be merged.
#pragma omp taskwait
  merge(arr, buffer, begin, middle, end);
}

} // namespace

void msort(int *arr, const std::size_t n, const std::size_t threshold) {
  if (n <= 1) {
    return;
  }

  int *buffer = new int[n];
  const std::size_t effective_threshold = threshold == 0 ? 1 : threshold;

#pragma omp parallel
  {
    // Only one thread starts the recursion. Its tasks are available to all
    // threads in this parallel region.
#pragma omp single
    recursiveSort(arr, buffer, 0, n, effective_threshold);
  }

  delete[] buffer;
}
