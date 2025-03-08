#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char nama[101];
    char nik[17];
    char tempatLahir[21];
    char tanggalLahir[11];
    char agama[11];
    char goldar[4];
} ktp;

int main() {
    ktp penduduk[100];

    int count = 0;
    int pilihan;
    while(true) {
        printf("Menu mana yang mau anda pilih\n");
        printf("1. Penambahan data\n");
        printf("2. Penghapusan data\n");
        printf("3. Penampilan data\n");
        printf("4. Pencarian data\n");
        printf("5. Keluar\n");

        printf("Pilih antara 1-5: ");
        scanf("%d", &pilihan);

        if (pilihan > 5 || pilihan < 1) {
            printf("Pilihan tidak valid, mohon coba lagi\n");
            continue;
        } else if (pilihan == 1) {
            printf("Masukkan nama: ");
            scanf("%s", penduduk[count].nama);
            printf("Masukkan nik: ");
            scanf("%s", penduduk[count].nik);
            printf("Masukkan tempatLahir: ");
            scanf("%s", penduduk[count].tempatLahir);
            printf("Masukkan tanggalLahir (dd-mm-yyyy): ");
            scanf("%s", penduduk[count].tanggalLahir);
            printf("Masukkan agama: ");
            scanf("%s", penduduk[count].agama);
            printf("Masukkan golongan darah: ");
            scanf("%s", penduduk[count].goldar);
            count++;
        } else if (pilihan == 2) {
            printf("Menu mana yang mau anda pilih\n");
            printf("1. Penghapusan data menggunakan nama\n");
            printf("2. Penghapusan data menggunakan nik\n");
            printf("3. Penghapusan data menggunakan id\n");
            printf("4. Batal");

            printf("Pilih antara 1-4: ");
            scanf("%d", &pilihan);
            int idToDelete = -1;
            if (pilihan > 4 || pilihan < 1) {
                printf("Pilihan tidak valid, penghapusan dilewatkan\n");
                continue;
            }else if (pilihan == 1) {
                char nama;
                printf("Masukkan nama data yang akan dihapus: ");
                scanf("%s", nama);
                for(int i = 0; i < count; i++) if (strcmp(penduduk[i].nama, nama) == 0) idToDelete = i;
            } else if (pilihan == 2) {
                char nik;
                printf("Masukkan NIK data yang akan dihapus: ");
                scanf("%s", nik);
                for(int i = 0; i < count; i++) if (strcmp(penduduk[i].nik, nik) == 0) idToDelete = i;
            } 
        }
    }
}