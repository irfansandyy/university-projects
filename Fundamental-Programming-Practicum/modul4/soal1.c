#include <stdio.h>
#include <string.h>

typedef struct {
    char trainer[20];
    char pokemon[20];
    int hp;
    int attack;
    int defense;
    int speed;
} Pokemon;

int main() {
    int n;
    scanf("%d", &n);
    Pokemon pokemonLists[n];
    double powerLists[n];
    for(int i = 0; i < n; i++) {
        int temphp, tempattack, tempdefense, tempspeed;
        scanf("%s", pokemonLists[i].trainer);
        scanf("%s", pokemonLists[i].pokemon);
        scanf("%d", &temphp);
        scanf("%d", &tempattack);
        scanf("%d", &tempdefense);
        scanf("%d", &tempspeed);
        pokemonLists[i].hp = temphp;
        pokemonLists[i].attack = tempattack;
        pokemonLists[i].defense = tempdefense;
        pokemonLists[i].speed = tempspeed;
        powerLists[i] = (temphp+tempattack+tempdefense+tempspeed)/4;
    }

    int biggest = -1;
    int biggestIndex = -1;
    for(int i = 0; i < n; i++) {
        if(powerLists[i] > biggest) {
            biggest = powerLists[i];
            biggestIndex = i;
        }
    }

    printf("%s wins! %s said ez", pokemonLists[biggestIndex].pokemon, pokemonLists[biggestIndex].trainer);
}