#include <cstdio>

int ii(int x, int y) {
    int stride_x = 1;
    int stride_y = 14;
    return y * stride_y + x;
}

int main() {
    int x, y;
    for (y = 0; y < 6; ++y) {
        for (x = 0; x < 14; ++x) {
            printf("(%2d,%2d) -> %2d \n", x, y, ii(x, y));
        }
    }
    return 0;
}

