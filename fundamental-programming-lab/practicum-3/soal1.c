#include <stdio.h>
#include <math.h>
#define MAX_FIB 10000
#define llu long long unsigned

void fibonacci(int num, llu fib, llu prev, llu fibs[], int counter, int target) {
    if((fib <= (llu) target)) {
        counter++;
        fibs[counter] = fib;
    }
    if(fib > (llu) target) {
        return;
    }
    return fibonacci(num-1, fib+prev, fib, fibs, counter, target);
}

llu fibonacciPrint(llu fibs[], int counter, llu fibnum, llu sum) {
    if(counter == 0) {
        printf("0");
    }
    if(counter < 0) return sum;
    if((fibs[counter] <= fibnum) && (fibs[counter] != 0)) {
        if(counter < 0) return sum;
        sum += fibs[counter];
        printf("%llu ", fibs[counter]);
    }
    return fibonacciPrint(fibs, counter-1, fibnum, sum);
}

int main() {
    int n;
    scanf("%d", &n);
    llu fiboList[MAX_FIB];
    fiboList[0] = 0;
    fibonacci(n, 1, 0, fiboList, 0, n);
    llu sum = fibonacciPrint(fiboList, 1000, n, 0);
    printf("\n%llu", sum);
    return 0;
}