#include <stdio.h>

int main() {
    int ia, ib, ic, id, ie;
    char ca, cb, cc, cd, ce;
    scanf("%d %c %d %c %d %c %d %c %d %c", &ia, &ca, &ib, &cb, &ic, &cc, &id, &cd, &ie, &ce);
    
    if((ca == cb) && (ca == cc) && (ca == cd) && (ca == ce)) {
        printf("Flush");
    } else if(ia == ib) {
        if(ib == ic) {
            if(id == ie) {
                printf("Full House");
            } else if(ic == id) {
                printf("Four of a Kind");
            } else {
                printf("Three of a Kind");
            }
        } else if((ic == id) || (id == ie) || (ic == ie)) {
            printf("Two Pair");
        } else {
            printf("One Pair");
        }
    } else if(ib == ic) {
        if(ic == id) {
            if(ia == ie) {
                printf("Full House");
            } else if(id == ie) {
                printf("Four of a Kind");
            } else {
                printf("Three of a Kind");
            }
        } else if(ic == id) {
            printf("Two Pair");
        } else {
            printf("One Pair");
        }
    } else {
        printf("Tidak ada kombinasi khusus");
    }
    return 0;
}