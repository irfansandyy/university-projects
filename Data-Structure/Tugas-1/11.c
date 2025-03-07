#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char name[101];
    float income;
    float expenses;
    float profit;
} Stall;

void bubbleSort (Stall stalls[], int n) {
    bool swap;
    do {
        swap = false;
        for (int i = 1; i < n; i++) {
            if (stalls[i].profit > stalls[i - 1].profit) {
                Stall temp = stalls[i];
                stalls[i] = stalls[i - 1];
                stalls[i - 1] = temp;
                swap = true;
            }
        }
    } while (swap);
}

int main() {
    Stall stalls[100];
    FILE *fptr = fopen("./stall-data.txt", "r");
  
    if (fptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    int count = 0;
  
    while (fscanf (fptr, "%s %f %f", stalls[count].name, &stalls[count].income, &stalls[count].expenses) != EOF) {
        stalls[count].profit = stalls[count].income - stalls[count].expenses;
        count++;
    }

    fclose(fptr);
    bubbleSort(stalls, count);

    printf("%-4s %-20s %10s\n", "No", "Name", "Profit");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-20s %10.2f\n", i + 1, stalls[i].name, stalls[i].profit);
    }
}