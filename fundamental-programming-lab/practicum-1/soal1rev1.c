#include <stdio.h>

int main() {
    int ia, ib, ic, id, ie;
    char ca, cb, cc, cd, ce;
    scanf("%d %c %d %c %d %c %d %c %d %c", &ia, &ca, &ib, &cb, &ic, &cc, &id, &cd, &ie, &ce);
     
    if(((ia == ib) && (ia == ic) && (ia == id)) || ((ib == ic) && (ib == id) && (ib == ie)) || ((ia == ic) && (ia == id) && (ia == ie)) || ((ia == ib) && (ia == id) && (ia == ie)) || ((ia == ib) && (ia == ic) && (ia == ie))) {
        printf("Four of a Kind");
    } else if(((ia == ib) && (ib == ic) && (id == ie)) || ((ia == ib) && (ib == id) && (ic == ie)) || ((ia == ib) && (ib == ie) && (ic == id)) || ((ia == ic) && (ic == id) && (ib == ie)) || ((ia == ic) && (ic == ie) && (ib == id)) || ((ia == id) && (id == ie) && (ib == ic)) || ((ib == ic) && (ic == id) && (ia == ie)) || ((ib == ic) && (ic == ie) && (ia == id)) || ((ib == id) && (id == ie) && (ia == ic)) || ((ic == id) && (id == ie) && (ia == ib))) {
        printf("Full House");
    } else if((ca == cb) && (ca == cc) && (ca == cd) && (ca == ce)) {
        printf("Flush");
    } else if(((ia == ib) && (ib == ic)) || ((ia == ib) && (ib == id)) || ((ia == ib) && (ib == ie)) || ((ia == ic) && (ic == id)) || ((ia == ic) && (ic == ie)) || ((ia == id) && (id == ie)) || ((ib == ic) && (ic == id)) || ((ib == ic) && (ic == ie)) || ((ib == id) && (id == ie)) || ((ic == id) && (id == ie))) {
        printf("Three of a Kind");
    } else if(((ia == ib) && (ic == id)) || ((ia == ib) && (id == ie)) || ((ia == ib) && (ic == ie)) || ((ia == ic) && (ib == id)) || ((ia == ic) && (ib == ie)) || ((ia == ic) && (id == ie)) || ((ia == id) && (ib == ic)) || ((ia == id) && (ib == ie)) || ((ia == id) && (ic == ie)) || ((ia == ie) && (ib == ic)) || ((ia == ie) && (ib == id)) || ((ia == ie) && (ic == id)) || ((ib == ic) && (id == ie)) || ((ib == ic) && (ia == ie)) || ((ib == ic) && (ia == id)) || ((ib == id) && (ia == ic)) || ((ib == id) && (ia == ie)) || ((ib == id) && (ic == ie)) || ((ib == ie) && (ia == ic)) || ((ib == ie) && (ia == id)) || ((ib == ie) && (ic == id)) || ((ic == id) && (ie == ia)) || ((ic == id) && (ia == ib)) || ((ic == id) && (ib == ie)) || ((ic == ie) && (ia == ib)) || ((ic == ie) && (ia == id)) || ((ic == ie) && (ib == id)) || ((id == ie) && (ia == ib)) || ((id == ie) && (ia == ic)) || ((id == ie) && (ic == ib))) {
        printf("Two Pair");
    } else if((ia == ib) || (ia == ic) || (ia == id) || (ia == ie) || (ib == ic) || (ib == id) || (ib == ie) || (ic == id) || (ic == ie) || (id == ie)) {
        printf("One Pair");
    } else {
        printf("Tidak ada kombinasi khusus");
    }
    return 0;
}