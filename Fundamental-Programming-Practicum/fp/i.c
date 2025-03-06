#include <stdio.h>
#define MAX_BOARD 7

int matrix[MAX_BOARD][MAX_BOARD];
int dikunjungi[MAX_BOARD][MAX_BOARD];
int n, m;
int jumlah_jalan = 0;

int valid(int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && !dikunjungi[x][y] && (matrix[x][y] % 2 != 0 || matrix[x][y] == 1));
}

void dfs(int x, int y) {
    if (matrix[x][y] == 1) {
        jumlah_jalan++;
        return;
    }
    dikunjungi[x][y] = 1;

    if (valid(x - 1, y)) dfs(x - 1, y);
    if (valid(x + 1, y)) dfs(x + 1, y);
    if (valid(x, y - 1)) dfs(x, y - 1);
    if (valid(x, y + 1)) dfs(x, y + 1);

    dikunjungi[x][y] = 0;
}

int main() {
    scanf("%d %d", &n, &m);
    int xAwal = -1, yAwal = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
            dikunjungi[i][j] = 0;

            if (matrix[i][j] == 0) {
                xAwal = i;
                yAwal = j;
            }
        }
    }

    dfs(xAwal, yAwal);

    if (jumlah_jalan == 0) {
        printf("Kucing oren tidak bisa pulang ke rumah :(");
    } else {
        printf("Terdapat %d jalan untuk kucing oren pulang", jumlah_jalan);
    }

    return 0;
}
