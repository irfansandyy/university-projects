#include <stdio.h>

int main() {
    int n;
    long long k;
    long long diskon[6] = {0, 35, 45, 50, 55, 40};
    long long diskonPengiriman = 0;
    long long hargaProduk, hargaPengiriman = 50000, hargaTotal;

    scanf("%d %lld", &n, &k);

    hargaProduk = k - diskon[n]*k/100;

    if (hargaProduk >= 250000) {
        diskonPengiriman = 100;
    } else if (hargaProduk >= 150000) {
        diskonPengiriman = 50;
    } else if (hargaProduk >= 50000) {
        diskonPengiriman = 25;
    }

    hargaPengiriman = hargaPengiriman - diskonPengiriman*hargaPengiriman/100;
    hargaTotal = hargaProduk + hargaPengiriman;

    if (hargaTotal > 300000) {
        printf("Mamaa minta uang, uangku kurang %lld :((\n", hargaTotal - 300000);
        printf("Totalnya tadi %lld\n", hargaTotal);
    } else if (hargaTotal < 300000) {
        printf("WOHHHH uangku sisa %lld\n", 300000 - hargaTotal);
        printf("Mamaa Surip bisa kasi THR ke adek adek, tadi totalnya %lld\n", hargaTotal);
    } else {
        printf("Yeyyy totalnya pas 300000\n");
        printf("Mamaa, Surip udah gede ga jadi minta uang :)\n");
    }
}
