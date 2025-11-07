#include <iostream>
#include <cstdio>

void swapAxis(int **M, int rows, int cols) {

    for (int i = 0; i < rows / 2; ++i) {
        int *temp = *(M + i);
        *(M + i) = *(M + (rows - 1 - i));
        *(M + (rows - 1 - i)) = temp;
    }

    for (int i = 0; i < rows; ++i) {
        int *row = *(M + i);
        for (int j = 0; j < cols / 2; ++j) {
            int tmp = *(row + j);
            *(row + j) = *(row + (cols - 1 - j));
            *(row + (cols - 1 - j)) = tmp;
        }
    }
}

int main() {
    int **M = new int *[2];
    *(M + 0) = new int[5]{0,1,2,3,4};
    *(M + 1) = new int[5]{5,6,7,8,9};

    swapAxis(M, 2, 5);

    // print to verify (allowed to use [])
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j)
            printf("%d \n", M[i][j]);
    }

    for (int i = 0; i < 2; ++i) delete[] M[i];
    delete[] M;
}

