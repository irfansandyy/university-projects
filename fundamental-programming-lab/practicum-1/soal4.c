#include <stdio.h>

int main() {
    long long a, b, c, d, e, f, g, h, i;
    int aryaMenang = 0, andiMenang = 0;
    scanf(" %lld %lld %lld %lld %lld %lld %lld %lld %lld", &a, &b, &c, &d, &e, &f, &g, &h, &i);
    a %= 3;
    b %= 3;
    c %= 3;
    d %= 3;
    e %= 3;
    f %= 3;
    g %= 3;
    h %= 3;
    i %= 3;

    if((a == b) && (a == c)) {
        if(a == 1) {
            aryaMenang += 1;
        } else if(a == 2) {
            andiMenang += 1;
        }
    } 
    if((d == e) && (d == f)) {
        if(d == 1) {
            aryaMenang += 1;
        } else if(d == 2) {
            andiMenang += 1;
        }
    }
    if((g == h) && (g == i)) {
        if(g == 1) {
            aryaMenang += 1;
        } else if(g == 2) {
            andiMenang += 1;
        }
    }
    if((a == d) && (a == g)) {
        if(a == 1) {
            aryaMenang += 1;
        } else if(a == 2) {
            andiMenang += 1;
        }
    }
    if((b == e) && (b == h)) {
        if(b == 1) {
            aryaMenang += 1;
        } else if(b == 2) {
            andiMenang += 1;
        }
    }
    if((c == f) && (c == i)) {
        if(c == 1) {
            aryaMenang += 1;
        } else if(c == 2) {
            andiMenang += 1;
        }
    }
    if((a == e) && (a == i)) {
        if(a == 1) {
            aryaMenang += 1;
        } else if(a == 2) {
            andiMenang += 1;
        }
    }
    if((c == e) && (c == g)) {
        if(c == 1) {
            aryaMenang += 1;
        } else if(c == 2) {
            andiMenang += 1;
        }
    }

    printf("%lld | %lld | %lld", a, b, c);
    printf("\n%lld | %lld | %lld", d, e, f);
    printf("\n%lld | %lld | %lld", g, h, i);

    if((aryaMenang == 1) && (andiMenang == 1)) {
        printf("\nTerjadi alomani dua kemenangan!");
        printf("\nLah dua duanya menang, selamat Arya dan Andi");
    } else if(aryaMenang == 2) {
        printf("\nTerjadi alomani dua kemenangan!");
        printf("\nLah menang dua kali kamu Arya");
    } else if(andiMenang == 2) {
        printf("\nTerjadi alomani dua kemenangan!");
        printf("\nLah menang dua kali kamu Andi");
    } else if(aryaMenang == 1) {
        printf("\nKeberuntungan ada di kamu, selamat Arya");
    } else if(andiMenang == 1) {
        printf("\nKeberuntungan ada di kamu, selamat Andi");
    } else {
        printf("\nYahh kurang beruntung nih, gaada kemenangan!");
    }

    return 0;
}