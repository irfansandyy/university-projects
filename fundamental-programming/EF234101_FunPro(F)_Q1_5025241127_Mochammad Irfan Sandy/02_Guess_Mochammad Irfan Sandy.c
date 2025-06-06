#include <stdio.h>

int main() {
    int guess, answer;
    printf("Input answer: ");
    scanf("%d", &answer);
    printf("Input your guess: ");
    do {
        scanf("%d", &guess);
        if(guess < answer) {
            printf("Your guess is too low!");
            printf("\nInput another guess: ");
        } else if(guess > answer) {
            printf("Your guess is too high!");
            printf("\nInput another guess: ");
        }
    } while (guess != answer);
    printf("Congratulations! Your guess is correct!\n");
}