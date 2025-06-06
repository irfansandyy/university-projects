#include <stdio.h>
#include <string.h>

typedef struct{
    char name[30];
    char assistTo[30];
    int assist;
    int goals;
    int keyPassess;
    int dribbles;
} Player;

int main() {
    int n, t;
    scanf("%d", &n);
    Player players[n];

    for(int i = 0; i < n; i++) {
        players[i].assist = 0;
        players[i].goals = 0;
        players[i].keyPassess = 0;
        players[i].dribbles = 0;
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < n; j++) {
            if(i == 0) {
                scanf("%s", players[j].name);
            } else if(i == 1) {
                char tempAssistor[30];
                char tempGoaler[30];
                int tempCount;
                scanf("%s", tempAssistor);
                scanf("%s", tempGoaler);
                scanf("%d", &tempCount);
                for(int k = 0; k < n; k++) {
                    if(strcmp(players[k].name, tempGoaler) == 0) {
                        players[k].goals += tempCount;
                    } else if(strcmp(players[k].name, tempAssistor) == 0) {
                        players[k].assist += tempCount;
                        strcpy(players[k].assistTo, tempGoaler);
                    }
                }
            } else if(i == 2) {
                char tempName[30];
                int tempKeyPassess;
                int tempDribbles;
                scanf("%s", tempName);
                scanf("%d", &tempKeyPassess);
                scanf("%d", &tempDribbles);
                for(int k = 0; k < n; k++) {
                    if(strcmp(players[k].name, tempName) == 0) {
                        players[k].keyPassess += tempKeyPassess;
                        players[k].dribbles += tempDribbles;
                    }
                }
            }
        }
    }
    scanf("%d", &t);
    char instructions[2][30];
    for(int i = 0; i < t; i++) scanf("%s", instructions[i]);
    for(int i = 0; i < t; i++) {
        if(strcmp(instructions[i], "TABLE") == 0) {
            for(int j = 0; j < n; j++) {
                printf("%s | Goals: %d | Assists: %d | Assist To: %s \n", players[j].name, players[j].goals, players[j].assist, players[j].assistTo);
            }
        } else if(strcmp(instructions[i], "MOTM") == 0) {
            double biggest = -1;
            int biggestIndex = -1;
            for(int j = 0; j < n; j++) {
                double motmscore = players[j].goals*3 + players[j].assist*2 + players[j].keyPassess + players[j].dribbles/5;
                if(motmscore > biggest) {
                    biggest = motmscore;
                    biggestIndex = j;   
                }
            }
            printf("Man of the Match: %s\n", players[biggestIndex].name);
        }
    }
}