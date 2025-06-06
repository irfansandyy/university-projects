#include <stdio.h>
#include <string.h>
#define MAX_ISLANDS 50
#define MAX_FARMS_IN_ISLAND 5

typedef struct {
    char name[40];
    int farmRate;
} Farm;

typedef struct {
    char name[40];
    int x;
    int y;
    int farmCount;
    Farm farms[MAX_FARMS_IN_ISLAND];
} Island;

int main() {
    Island islands[MAX_ISLANDS];
    int islandCount = 0;
    char cmd[20];
    while(1) {
        scanf("%s", cmd);
        if(strcmp(cmd, "ADD_ISLAND") == 0) {
            char islandNameTemp[40];
            int xTemp;
            int yTemp;
            scanf("%s", islandNameTemp);
            scanf("%d", &xTemp);
            scanf("%d", &yTemp);
            if(islandCount >= MAX_ISLANDS) {
                printf("CANNOT ADD MORE ISLAND\n");  
                continue;
            }
            islandCount++;
            strcpy(islands[islandCount-1].name, islandNameTemp);
            islands[islandCount-1].x = xTemp;
            islands[islandCount-1].y = yTemp;
            printf("ISLAND ADDED\n");
        } else if(strcmp(cmd, "ADD_FARM") == 0) {
            char destinationIslandTemp[40];
            char farmNameTemp[40];
            int farmRateTemp;
            int islandKey = -1;
            scanf("%s", farmNameTemp);
            scanf("%s", destinationIslandTemp);
            scanf("%d", &farmRateTemp);
            for(int i = 0; i < islandCount; i++) {
                if(strcmp(islands[i].name, destinationIslandTemp) == 0) {
                    islandKey = i;
                    break;
                }
            }
            if(islandKey != -1) {
                if(islands[islandKey].farmCount >= MAX_FARMS_IN_ISLAND) {
                    printf("ISLAND IS FULL CANNOT ADD FARM\n");  
                    continue;
                }
                islands[islandKey].farmCount++;
                strcpy(islands[islandKey].farms[islands[islandKey].farmCount-1].name, farmNameTemp);
                islands[islandKey].farms[islands[islandKey].farmCount-1].farmRate = farmRateTemp;
                printf("FARM ADDED\n");
                continue;
            }
            printf("ISLAND NOT FOUND CANNOT ADD FARM\n");
        } else if(strcmp(cmd, "VIEW_ALL") == 0) {
            for(int i = 0; i < islandCount; i++) {
                printf("ISLAND %s has %d farms:\n", islands[i].name, islands[i].farmCount);
                for(int j = 0; j < islands[i].farmCount; j++) {
                    printf("FARM %s %d\n", islands[i].farms[j].name, islands[i].farms[j].farmRate);
                }
            }
        } else {
            printf("INVALID COMMAND, BYE!");
            break;
        }
    }
}