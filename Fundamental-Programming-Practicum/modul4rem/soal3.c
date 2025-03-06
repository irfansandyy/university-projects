#include <stdio.h>
#include <string.h>
#define MAX_STRING 1000
#define MAX_SEARCH 200

typedef struct {
    char nama[MAX_STRING];
    char ip[MAX_STRING];
    char uuid[MAX_STRING];
} Player;

int main() {
    int keyList[MAX_SEARCH];
    int n;
    scanf("%d", &n);
    Player players[n];
    for(int i = 0; i < n; i++) {
        scanf("%s", players[i].nama);
        scanf("%s", players[i].ip);
        scanf("%s", players[i].uuid);
    }
    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        char searchNama[MAX_STRING];
        scanf("%s", searchNama);
        keyList[i] = -1;
        for(int j = 0; j < n; j++) {
            if(strcmp(searchNama, players[j].nama) == 0) {
                keyList[i] = j;
            }
        }
    }
    for(int i = 0; i < m; i++) {
        if(keyList[i] != -1) {
            printf("asyik %s-%s diperbolehkan bermain\n", players[keyList[i]].uuid, players[keyList[i]].nama);
        } else {
            printf("hmm, kayaknya ada yang salah dengan datamu\n");
        }
    }
}