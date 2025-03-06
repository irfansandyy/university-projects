#include <stdio.h>
#include <math.h>

typedef struct{
    int x;
    int y;
} Point;

int main() {
    int n;
    scanf("%d", &n);
    Point flowers[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &flowers[i].x);
        scanf("%d", &flowers[i].y);
    }

    double minDistance = 999999999.999;
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            double distance = sqrt((flowers[j].x - flowers[i].x)*(flowers[j].x - flowers[i].x) + (flowers[j].y - flowers[i].y)*(flowers[j].y - flowers[i].y));
            if(distance < minDistance) {
                minDistance = distance;
            }
        }
    }
    printf("%.2lf", minDistance);
}