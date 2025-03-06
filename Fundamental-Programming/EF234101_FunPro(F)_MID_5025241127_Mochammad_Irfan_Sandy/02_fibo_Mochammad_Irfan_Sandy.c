#include <stdio.h>
#include <time.h>
#define llu long long unsigned

struct nthFiboandSum {llu nthFibo, sum;};
typedef struct nthFiboandSum fibdata;
fibdata iterativeFibo(int n);
fibdata recursiveFibo(int number, llu nthValue, llu prevValue, llu sum);

int main() {
    int number;
    double recursiveTime, iterativeTime;
    struct timespec start, end;
    fibdata recursive, iterative;

    printf("Enter a number: ");
    scanf("%d", &number);

    clock_gettime(CLOCK_MONOTONIC, &start);    
    iterative = iterativeFibo(number);
    clock_gettime(CLOCK_MONOTONIC, &end);
    iterativeTime = (end.tv_sec - start.tv_sec) * 1e9;
    iterativeTime = (iterativeTime + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    clock_gettime(CLOCK_MONOTONIC, &start);
    recursive = recursiveFibo(number, 1, 0, 0);
    clock_gettime(CLOCK_MONOTONIC, &end);
    recursiveTime = (end.tv_sec - start.tv_sec) * 1e9;
    recursiveTime = (recursiveTime + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    char suffix[3] = {'t', 'h', '\0'};
    if((number % 10 >= 1 && number % 10 <= 3) && ((number % 100)/10 != 1)) {
        suffix[0] = (number % 10 == 1) ? 's' : (number % 10 == 2) ? 'n' : 'r';
        suffix[1] = (number % 10 == 1) ? 't' : (number % 10 == 2) ? 'd' : 'd';
    }

    printf("\nIterative");
    printf("\n%d%s Fibonacci = %llu", number, suffix, iterative.nthFibo);
    printf("\nSum of Fibonacci until %d%s term = %llu", number, suffix, iterative.sum);
    printf("\nIterative time: %.0lf nanoseconds", iterativeTime * 1e9);

    printf("\n\nRecursive");
    printf("\n%d%s Fibonacci = %llu", number, suffix, recursive.nthFibo);
    printf("\nSum of Fibonacci until %d%s term = %llu", number, suffix, recursive.sum);
    printf("\nRecursive time: %.0lf nanoseconds", recursiveTime * 1e9);

    if(recursiveTime < iterativeTime) {
        printf("\n\nRecursive method is faster than iterative method by %.0lf nanoseconds", (iterativeTime - recursiveTime) * 1e9);
    } else if(recursiveTime > iterativeTime) {
        printf("\n\nIterative method is faster than recursive method by %.0lf nanoseconds", (recursiveTime - iterativeTime) * 1e9);
    } else {
        printf("\n\nBoth method is as fast (this timer records time in 100 nanoseconds increment)");
    }
    return 0;
}

fibdata iterativeFibo(int n) {
    if(n <= 1) return (fibdata) {(llu)n, (llu)n};
    llu a = 0, b = 1, c, sum = 1;
    for(int i = 0; i < n - 1; i++) {
        c = a + b;
        a = b;
        b = c;
        sum += c;
    }
    return (fibdata) {c, sum};
}

fibdata recursiveFibo(int number, llu nthValue, llu prevValue, llu sum){
    if(number == 0) return (fibdata) {prevValue, sum};
    return recursiveFibo(number - 1, nthValue+prevValue, nthValue, sum+nthValue);
}