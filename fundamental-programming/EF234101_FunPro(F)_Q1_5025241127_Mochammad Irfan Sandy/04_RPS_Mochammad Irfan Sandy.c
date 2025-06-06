#include <stdio.h>

int main() {
    int p1, p2;
    while(1) {
        printf("Player 1 (1. Rock, 2. Paper, 3. Scissors): ");
        scanf("%d", &p1);
        printf("Player 2 (1. Rock, 2. Paper, 3. Scissors): ");
        scanf("%d", &p2);
        if(p1 < 1 || p1 > 3 || p2 < 1 || p2 > 3) {
            printf("Your input is wrong please input again\n");
        } else {
            break;
        }
    }
    if(p1 == p2) {
        printf("Draw");
    } else if((p1 == 1 && p2 == 3) || (p1 == 2 && p2 == 1) || (p1 == 3 && p2 == 2)) {
        printf("Player 1 Wins");
    } else {
        printf("Plater 2 Wins");
    }
}