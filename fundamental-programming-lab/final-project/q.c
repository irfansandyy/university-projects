#include <stdio.h>
#include <math.h>

typedef struct {
    int x;
    int y;
    int z;
} Point;

int main() {
    Point p[3];
    for(int i = 0; i < 3; i++) {
        scanf("%d", &p[i].x);
        scanf("%d", &p[i].y);
        scanf("%d", &p[i].z);
    }
    int rA, rB, RD;
    scanf("%d", &rA);
    scanf("%d", &rB);
    scanf("%d", &RD);

    double dAB, dAC, dBC;
    dAB = sqrt(pow(p[1].x - p[0].x, 2) + pow(p[1].y - p[0].y, 2) + pow(p[1].z - p[0].z, 2));
    dBC = sqrt(pow(p[2].x - p[1].x, 2) + pow(p[2].y - p[1].y, 2) + pow(p[2].z - p[1].z, 2));
    dAC = sqrt(pow(p[2].x - p[0].x, 2) + pow(p[2].y - p[0].y, 2) + pow(p[2].z - p[0].z, 2));

    if(dAC <= rA*RD) {
        printf("NAH ID WIN, NO NEED TO STOP");
    } else if(dAB + dBC <= (rA + rB)*RD) {
        printf("HHM BETTER TAKE ROCKET, STILL CAN WIN");
    } else {
        printf("GIVE UP ALREADY, MINING BETTER");
    }
}