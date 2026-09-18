#include <cstdio>
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int N = std::atoi(argv[1]);
    for (int i = 0; i <= N; i++) {
        if (i > 0) std::printf(" ");
        std::printf("%d", i);
    }
    std::printf("\n");
    for (int j = N; j >= 0; --j) {
        if (j < N) std::cout << " ";
        std::cout << j;
    }
    std::cout << "\n";

    return 0;
}
