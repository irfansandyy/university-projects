#include <stdio.h>

int main() {
    int jumlah_misi, waktu = 0;
    scanf("%d", &jumlah_misi);
    
    if(jumlah_misi == 1) {
        int a;
        scanf("%d", &a);
        if(a == 1) {
            waktu += 30;
        } else if(a == 2) {
            waktu += 45;
        } else if(a == 3) {
            waktu += 90;
        } else {
            printf("Kesulitan yang kamu masukkan tidak valid! Program berhenti.");
            return 0;
        }
    } else if(jumlah_misi == 2) {
        int a, b;
        scanf("%d %d", &a, &b);
        if(a == 1) {
            waktu += 30;
        } else if(a == 2) {
            waktu += 45;
        } else if(a == 3) {
            waktu += 90;
        } else {
            printf("Kesulitan yang kamu masukkan tidak valid! Program berhenti.");
            return 0;
        }
        if(b == 1) {
            waktu += 30;
        } else if(b == 2) {
            waktu += 45;
        } else if(b == 3) {
            waktu += 90;
        } else {
            printf("Kesulitan yang kamu masukkan tidak valid! Program berhenti.");
            return 0;
        }
    } else if(jumlah_misi == 3) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a == 1) {
            waktu += 30;
        } else if(a == 2) {
            waktu += 45;
        } else if(a == 3) {
            waktu += 90;
        } else {
            printf("Kesulitan yang kamu masukkan tidak valid! Program berhenti.");
            return 0;
        }
        if(b == 1) {
            waktu += 30;
        } else if(b == 2) {
            waktu += 45;
        } else if(b == 3) {
            waktu += 90;
        } else {
            printf("Kesulitan yang kamu masukkan tidak valid! Program berhenti.");
            return 0;
        }
        if(c == 1) {
            waktu += 30;
        } else if(c == 2) {
            waktu += 45;
        } else if(c == 3) {
            waktu += 90;
        } else {
            printf("Kesulitan yang kamu masukkan tidak valid! Program berhenti.");
            return 0;
        }
    } else {
        printf("Jumlah misi harus antara 1 dan 3!");
        return 0;
    }
    printf("Total waktu yang dihabiskan: %d menit", waktu);
    printf("\nSisa waktu: %d menit", 180 - waktu);
    if(180 - waktu >= 30) {
        printf("\nBenerin mobil kayanya asik di AutoWin. Anjay mulus!");
    } else if(180 - waktu >= 15) {
        printf("\nMakan dulu gasih brow di Klenger Noodles. Perut kenyang hidup tenang!");
    } else {
        printf("\nJangan sok jago, mampus kan ga cukup waktunya. ang ang ang bye bye real life.");
    }
    return 0;
}