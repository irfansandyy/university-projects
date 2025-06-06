#include <stdio.h>

int main() {
    int boyhp = 200;
    int goblinhp[3] = {165, 165, 165};
    int goblinatk[3] =  {3, 4, 1};
    int turn = 0, g = 0;
    while((boyhp > 0) && (goblinhp[0] > 0 || goblinhp[1] > 0 || goblinhp[2] > 0)) {
        turn++;
        if(goblinhp[g] <= 0) {
            g++;
        }

        if(turn % 3 == 0) {
            goblinhp[g] -= 20;
        } else { 
            goblinhp[g] -= 10;
        }

        if(goblinhp[g] < 0) {
            goblinhp[g] = 0;
        }
        if(boyhp < 0) {
            boyhp = 0;
        }
        
        printf("Turn %d\n", turn);
        printf("Boy attacked goblin%d for %d damage; goblin%d hp: %d\n", g+1, (turn % 3 == 0) ? 20 : 10, g+1, goblinhp[g]);

        if(goblinhp[0] > 0) {
            boyhp -= goblinatk[0];
            printf("Goblin 1 attacked boy for %d damage; boy hp: %d\n", goblinatk[0], boyhp);
        } if(goblinhp[1] > 0) {
            boyhp -= goblinatk[1];
            printf("Goblin 2 attacked boy for %d damage; boy hp: %d\n", goblinatk[1], boyhp);
        } if(goblinhp[2] > 0) {
            boyhp -= goblinatk[2];
            printf("Goblin 3 attacked boy for %d damage; boy hp: %d\n", goblinatk[2], boyhp);
        }
        printf("\n");
    }

    printf("The battle is over\n");
    if(boyhp <= 0) {
        printf("The goblins have won the battle\n");
        printf("The goblin cumulative hp: %d\n", goblinhp[0] + goblinhp[1] + goblinhp[2]);
        printf("It took %d turns for the goblins to finish the battle\n", turn);
    } else {
        printf("The boy has won the battle\n");
        printf("The boy hp: %d\n", boyhp);
        printf("It took %d turns for the boy to finish the battle\n", turn);
    }
}