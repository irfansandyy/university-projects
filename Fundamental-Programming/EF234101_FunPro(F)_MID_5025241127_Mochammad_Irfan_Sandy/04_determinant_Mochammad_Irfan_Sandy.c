#include <stdio.h>

int main() {
    int matrix[3][3];
    int determinant = 0;
    printf("Enter the matrix: \n");

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for(int i = 0; i < 3; i++) {
        determinant += (matrix[0][i] * matrix[1][(i + 1) % 3] * matrix[2][(i + 2) % 3]); 
        determinant -= (matrix[0][(i + 2) % 3] * matrix[1][(i + 1) % 3] * matrix[2][i]);
    }

    printf("The matrix: \n");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Matrix determinant: %d", determinant);
    if(determinant == 0) {
        printf("\nMatrix cannot be inverted");
    } else {
        printf("\nMatrix is invertible");
    }
    return 0;
}