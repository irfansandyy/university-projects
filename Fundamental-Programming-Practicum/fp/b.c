#include <stdio.h>
#include <string.h>
#define ll long long
#define MAX_STRLEN 150

typedef struct {
    ll kode;
    char namaMakanan[MAX_STRLEN];
    ll harga;
    ll stock;
} Menu;

int main() {
    Menu db[100];
    ll dbc = 0;
    ll earnings = 0;
    char cmd[30];
    while(1) {
        scanf("%s", cmd);
        if(strcmp(cmd, "ADD") == 0) {
            int menuAlreadyExists = 0;
            ll kodeTemp;
            char namaMakananTemp[MAX_STRLEN];
            ll hargaTemp;
            ll stockTemp;
            scanf("%lld", &kodeTemp);
            getchar();
            fgets(namaMakananTemp, MAX_STRLEN, stdin);
            namaMakananTemp[strlen(namaMakananTemp) - 1] = 0;
            scanf("%lld", &hargaTemp);
            scanf("%lld", &stockTemp);
            for(ll i = 0; i < dbc + 1; i++) {
                if(db[i].kode == kodeTemp) {
                    printf("Menu is already exists\n");
                    menuAlreadyExists = 1;
                    break;
                }
            }
            if (menuAlreadyExists == 1) continue;
            db[dbc].kode = kodeTemp;
            strcpy(db[dbc].namaMakanan, namaMakananTemp);
            db[dbc].harga = hargaTemp;
            db[dbc].stock = stockTemp;
            dbc++;
            printf("Menu added\n");
        } else if(strcmp(cmd, "REMOVE") == 0) {
            ll remTemp;
            int menuFound = 0;
            scanf("%lld", &remTemp);
            for(ll i = 0; i < dbc + 1; i++) {
                if((db[i].kode == remTemp)) {
                    for(int j = i; j < dbc; j++) {
                        db[j] = db[j+1];
                    }
                    printf("Menu removed\n");
                    dbc--;
                    menuFound = 1;
                    break;
                }
            }
            if(menuFound == 0) {
                printf("Menu does not exist\n");
            }
        } else if(strcmp(cmd, "INFO") == 0) {
            ll infoTemp;
            int menuFound = 0;
            scanf("%lld", &infoTemp);
            for(ll i = 0; i < dbc + 1; i++) {
                if(db[i].kode == infoTemp) {
                    printf("#%lld %s\n", db[i].kode, db[i].namaMakanan);
                    printf("Price : Rp%lld\n", db[i].harga);
                    printf("Stock : %lldx\n", db[i].stock);
                    menuFound = 1;
                    break;
                }
            }
            if(menuFound == 0) {
                printf("Menu does not exist\n");
            }
        } else if(strcmp(cmd, "ORDER") == 0) {
            ll orderTemp;
            ll orderCount;
            int menuFound = 0;
            scanf("%lld", &orderTemp);
            scanf("%lld", &orderCount);
            if(orderCount <= 0) {
                printf("So you want to order or what\n");
                continue;
            }
            for(ll i = 0; i < dbc + 1; i++) {
                if(db[i].kode == orderTemp) {
                    menuFound = 1;
                    if(db[i].stock < orderCount) {
                        printf("Apologize, the stock is not enough\n");
                        break;
                    }
                    printf("Ordered %lldx %s for Rp%lld\n", orderCount, db[i].namaMakanan, db[i].harga*orderCount);
                    earnings += db[i].harga*orderCount;
                    db[i].stock -= orderCount;
                }
            }
            if(menuFound == 0) {
                printf("Menu does not exist\n");
            }
        } else if(strcmp(cmd, "CLOSE") == 0) {
            printf("Earnings: Rp%lld\n", earnings);
            printf("Informatics canteen is closing... thanks for the visit!");
            break;
        } 
    }
}