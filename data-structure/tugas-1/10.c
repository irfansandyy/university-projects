#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[101];
    float distance;
} Athlete;

void bubbleSort (Athlete athletes[], int n) {
    bool swap;
    do {
        swap = false;
        for (int i = 1; i < n; i++) {
            if (athletes[i].distance > athletes[i - 1].distance) {
                Athlete temp = athletes[i];
                athletes[i] = athletes[i - 1];
                athletes[i - 1] = temp;
                swap = true;
            }
        }
    } while (swap);
}

int main() {
    Athlete athletes[1001];
    FILE *fptr = fopen("./athlete-data.txt", "r");

    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    int count = 0;
    char tempName[101];
    float tempDistance;

    while (fscanf (fptr, "%s %f", tempName, &tempDistance) != EOF) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (strcmp (athletes[i].name, tempName) == 0) { 
                if (fptr == NULL) {
                    perror("Error opening file");
                    return 1;
                }
                if (athletes[i].distance < tempDistance) athletes[i].distance = tempDistance;
                found = true;
                break;
            }
        }
        if (!found) {
            strcpy(athletes[count].name, tempName);
            athletes[count].distance = tempDistance;
            count++;
        }
    }
    fclose(fptr);
    bubbleSort(athletes, count);

    int rank = 1;
    printf("%-5s %-8s %11s\n", "Rank" , "Name", "Range");
    for (int i = 0; i < count; i++) {
        if (i >= 1 && (athletes[i].distance != athletes[i - 1].distance)) {
            rank = i + 1;
        }
        printf("%-5d %-8s %10.2f meters\n", rank, athletes[i].name, athletes[i].distance);
    }

    return 0;
}