#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 202
#define NAMA_LEN 202
#define NIK_LEN 18
#define TEMPAT_LAHIR_LEN 22
#define TANGGAL_LAHIR_LEN 12
#define AGAMA_LEN 12
#define GOLDAR_LEN 5
#define MAX_DATABASE 200

typedef struct {
    char nama[NAMA_LEN];
    char nik[NIK_LEN];
    char tempatLahir[TEMPAT_LAHIR_LEN];
    char tanggalLahir[TANGGAL_LAHIR_LEN];
    char agama[AGAMA_LEN];
    char goldar[GOLDAR_LEN];
} ktp;

void rmnewln(char str[]) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void lower(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void inputstr(char str[], int size) {
    fgets(str, size, stdin);
    rmnewln(str);
    lower(str);
}

int main() {
    ktp penduduk[MAX_DATABASE];
    FILE *fptr = fopen("./penduduk-data.txt", "r");
    int count = 0;

    if (fptr == NULL) {
        printf("File penduduk-data.txt tidak ditemukan, melewatkan proses pembacaan file\n");
    } else {
        char goldar[GOLDAR_LEN], line[401], nama[NAMA_LEN/5], nama2[NAMA_LEN/5], nama3[NAMA_LEN/5], nama4[NAMA_LEN/5], nama5[NAMA_LEN/5];
        int lineCount = 1;

        while (fgets(line, sizeof(line), fptr)) {
            if (line[0] == '\n') continue;
            if (line[0] == '#') continue;
            if (count >= MAX_DATABASE) {
                printf("Database sudah penuh, menghentikan penambahan data\n");
                break;
            }
            int spaces = 0;
            for(int i = 0; line[i] != '\0'; i++) if (line[i] == ' ') spaces++;
            if (spaces < 5) {
                printf("Format data tidak valid, melewatkan baris %d\n", lineCount);
                continue;
            } else if (spaces > 9) {
                printf("Terlalu banyak data, melewatkan baris %d\n", lineCount);
                continue;
            } else if (spaces == 5) {
                sscanf(line, "%s %s %s %s %s %s", nama, penduduk[count].nik, penduduk[count].tempatLahir, penduduk[count].tanggalLahir, penduduk[count].agama, goldar);
                rmnewln(goldar);
                strcpy(penduduk[count].goldar, goldar);
                strcpy(penduduk[count].nama, nama);
            } else if (spaces == 6) {
                sscanf(line, "%s %s %s %s %s %s %s", nama, nama2, penduduk[count].nik, penduduk[count].tempatLahir, penduduk[count].tanggalLahir, penduduk[count].agama, goldar);
                rmnewln(goldar);
                snprintf(penduduk[count].nama, sizeof(penduduk[count].nama), "%s %s", nama, nama2);
                strcpy(penduduk[count].goldar, goldar);
            }   else if (spaces == 7) {
                sscanf(line, "%s %s %s %s %s %s %s %s", nama, nama2, nama3, penduduk[count].nik, penduduk[count].tempatLahir, penduduk[count].tanggalLahir, penduduk[count].agama, goldar);
                rmnewln(goldar);
                snprintf(penduduk[count].nama, sizeof(penduduk[count].nama), "%s %s %s", nama, nama2, nama3);
                strcpy(penduduk[count].goldar, goldar);
            } else if (spaces == 8) {
                sscanf(line, "%s %s %s %s %s %s %s %s %s", nama, nama2, nama3, nama4, penduduk[count].nik, penduduk[count].tempatLahir, penduduk[count].tanggalLahir, penduduk[count].agama, goldar);
                rmnewln(goldar);
                snprintf(penduduk[count].nama, sizeof(penduduk[count].nama), "%s %s %s %s", nama, nama2, nama3, nama4);
                strcpy(penduduk[count].goldar, goldar);
            } else if (spaces == 9) {
                sscanf(line, "%s %s %s %s %s %s %s %s %s %s", nama, nama2, nama3, nama4, nama5, penduduk[count].nik, penduduk[count].tempatLahir, penduduk[count].tanggalLahir, penduduk[count].agama, goldar);
                rmnewln(goldar);
                snprintf(penduduk[count].nama, sizeof(penduduk[count].nama), "%s %s %s %s", nama, nama2, nama3, nama4);
                strcpy(penduduk[count].goldar, goldar);
            }
            count++;
            lineCount++;
        }
    }
    fclose(fptr);

    int pilihan;
    while(true) {
        printf("\nMenu mana yang mau anda pilih\n");
        printf("1. Penambahan data\n");
        printf("2. Penghapusan data\n");
        printf("3. Penampilan data\n");
        printf("4. Pencarian data\n");
        printf("5. Penyimpanan data kedalam file .txt\n");
        printf("6. Keluar\n");

        printf("Pilih antara 1-6: ");
        scanf("%d", &pilihan);
        getchar();


        if (pilihan > 6 || pilihan < 1) {
            printf("\nPilihan tidak valid, mohon coba lagi\n");
            continue;
        } else if (pilihan == 1) {
            if (count >= MAX_DATABASE) {
                printf("\nDatabase sudah penuh, tidak bisa menambah data\n");
                continue;
            }
            printf("\nMasukkan nama: ");
            fgets(penduduk[count].nama, sizeof(penduduk[count].nama), stdin);
            printf("Masukkan nik: ");
            fgets(penduduk[count].nik, sizeof(penduduk[count].nik), stdin);
            printf("Masukkan tempatLahir: ");
            fgets(penduduk[count].tempatLahir, sizeof(penduduk[count].tempatLahir), stdin);
            printf("Masukkan tanggalLahir (dd-mm-yyyy): ");
            fgets(penduduk[count].tanggalLahir, sizeof(penduduk[count].tanggalLahir), stdin);
            printf("Masukkan agama: ");
            fgets(penduduk[count].agama, sizeof(penduduk[count].agama), stdin);
            printf("Masukkan golongan darah: ");
            fgets(penduduk[count].goldar, sizeof(penduduk[count].goldar), stdin);
            rmnewln(penduduk[count].nama);
            rmnewln(penduduk[count].nik);
            rmnewln(penduduk[count].tempatLahir);
            rmnewln(penduduk[count].tanggalLahir);
            rmnewln(penduduk[count].agama);
            rmnewln(penduduk[count].goldar);
            printf("Data berhasil ditambahkan\n");
            count++;
        } else if (pilihan == 2) {
            if (count == 0) {
                printf("\nDatabase kosong, tidak ada data yang bisa dihapus\n");
                continue;
            }
            printf("\nMenu mana yang mau anda pilih\n");
            printf("1. Penghapusan data menggunakan nama\n");
            printf("2. Penghapusan data menggunakan nik\n");
            printf("3. Penghapusan data menggunakan id\n");
            printf("4. Batal");

            printf("Pilih antara 1-4: ");
            scanf("%d", &pilihan);
            getchar();
            int idToDelete = -1;
            
            if (pilihan > 4 || pilihan < 1) {
                printf("\nPilihan tidak valid, penghapusan dibatalkan\n");
                continue;
            } else if (pilihan == 1) {
                char nama[NAMA_LEN];
                char namaPendudukTemp[NAMA_LEN];
                printf("\nMasukkan nama data yang akan dihapus: ");
                inputstr(nama, sizeof(nama));
                for(int i = 0; i < count; i++) {
                    strcpy(namaPendudukTemp, penduduk[i].nama);
                    lower(namaPendudukTemp);
                    if (strcmp(namaPendudukTemp, nama) == 0) idToDelete = i;
                }
            } else if (pilihan == 2) {
                char nik[NIK_LEN];
                printf("\nMasukkan NIK data yang akan dihapus: ");
                fgets(nik, sizeof(nik), stdin);
                rmnewln(nik);
                for(int i = 0; i < count; i++) if (strcmp(penduduk[i].nik, nik) == 0) idToDelete = i;
            } else if (pilihan == 3) {
                printf("\nMasukkan id data yang akan dihapus: ");
                scanf("%d", &idToDelete);
                getchar();
            } else if (pilihan == 4) {
                printf("\nPenghapusan dibatalkan\n");
                continue;
            }

            if (idToDelete == -1 || idToDelete >= count) {
                printf("Data tidak ditemukan\n");
            } else {
                for (int i = idToDelete; i < count - 1; i++) penduduk[i] = penduduk[i + 1];
                count--;
                printf("Data berhasil dihapus\n");
            }
        } else if (pilihan == 3) {
            printf("\nData yang ada di dalam database:\n");
            printf("-------------------------------------------------\n");
            for (int i = 0; i < count; i++) {
                printf("%-15s: %d\n", "Database id", i);
                printf("%-15s: %s\n", "Nama", penduduk[i].nama);
                printf("%-15s: %s\n", "NIK", penduduk[i].nik);
                printf("%-15s: %s\n", "Tempat Lahir", penduduk[i].tempatLahir);
                printf("%-15s: %s\n", "Tanggal Lahir", penduduk[i].tanggalLahir);
                printf("%-15s: %s\n", "Agama", penduduk[i].agama);
                printf("%-15s: %s\n", "Golongan Darah", penduduk[i].goldar);
                printf("-------------------------------------------------\n");
            }
            printf("Total data dalam database: %d\n", count);
        } else if (pilihan == 4) {
            if (count == 0) {
                printf("\nDatabase kosong, tidak ada data yang bisa dicari\n");
                continue;
            }
            printf("\nMenu mana yang mau anda pilih\n");
            printf("1. Pencarian data menggunakan nama\n");
            printf("2. Pencarian data menggunakan nik\n");
            printf("3. Pencarian data menggunakan tempat lahir\n");
            printf("4. Pencarian data menggunakan tanggal lahir\n");
            printf("5. Pencarian data menggunakan agama\n");
            printf("6. Pencarian data menggunakan golongan darah\n");
            printf("7. Pencarian data menggunakan id\n");
            printf("8. Batal\n");

            printf("Pilih antara 1-8: ");
            scanf("%d", &pilihan);
            getchar();
            char cari[MAX_STR];
            int idToSearch[MAX_DATABASE];
            int searchCount = -1;
            if (pilihan > 8 || pilihan < 1) {
                printf("\nPilihan tidak valid, pencarian dibatalkan\n");
                continue;
            } else if (pilihan == 1) {
                printf("\nMasukkan nama yang dicari: ");
                inputstr(cari, sizeof(cari));
                for (int i = 0; i < count; i++) {
                    char namaPendudukTemp[NAMA_LEN];
                    strcpy(namaPendudukTemp, penduduk[i].nama);
                    lower(namaPendudukTemp);
                    if (strcmp(namaPendudukTemp, cari) == 0) idToSearch[++searchCount] = i;
                }
            } else if (pilihan == 2) {
                printf("\nMasukkan NIK yang dicari: ");
                fgets(cari, sizeof(cari), stdin);
                rmnewln(cari);
                for (int i = 0; i < count; i++) if (strcmp(penduduk[i].nik, cari) == 0) idToSearch[++searchCount] = i;
            } else if (pilihan == 3) {
                printf("\nMasukkan tempat lahir yang dicari: ");
                inputstr(cari, sizeof(cari));
                for (int i = 0; i < count; i++) {
                    char tempatLahirPendudukTemp[TEMPAT_LAHIR_LEN];
                    strcpy(tempatLahirPendudukTemp, penduduk[i].tempatLahir);
                    lower(tempatLahirPendudukTemp);
                    if (strcmp(tempatLahirPendudukTemp, cari) == 0) idToSearch[++searchCount] = i;
                }
            } else if (pilihan == 4) {
                printf("\nMasukkan tanggal lahir yang dicari: ");
                inputstr(cari, sizeof(cari));
                for (int i = 0; i < count; i++) {
                    char tanggalLahirPendudukTemp[TANGGAL_LAHIR_LEN];
                    strcpy(tanggalLahirPendudukTemp, penduduk[i].tanggalLahir);
                    lower(tanggalLahirPendudukTemp);
                    if (strcmp(tanggalLahirPendudukTemp, cari) == 0) idToSearch[++searchCount] = i;
                }
            } else if (pilihan == 5) {
                printf("\nMasukkan agama yang dicari: ");
                inputstr(cari, sizeof(cari));
                for (int i = 0; i < count; i++) {
                    char agamaPendudukTemp[AGAMA_LEN];
                    strcpy(agamaPendudukTemp, penduduk[i].agama);
                    lower(agamaPendudukTemp);
                    if (strcmp(agamaPendudukTemp, cari) == 0) idToSearch[++searchCount] = i;
                }
            } else if (pilihan == 6) {
                printf("\nMasukkan golongan darah yang dicari: ");
                inputstr(cari, sizeof(cari));
                for (int i = 0; i < count; i++) {
                    char goldarPendudukTemp[GOLDAR_LEN];
                    strcpy(goldarPendudukTemp, penduduk[i].goldar);
                    lower(goldarPendudukTemp);
                    if (strcmp(goldarPendudukTemp, cari) == 0) idToSearch[++searchCount] = i;
                }
            } else if (pilihan == 7) {
                printf("\nMasukkan id yang dicari: ");
                scanf("%d", &idToSearch[++searchCount]);
                getchar();
                if (idToSearch[searchCount] < 0 || idToSearch[searchCount] >= count) {
                    printf("ID tidak valid, membatalkan pencarian\n");
                    searchCount--;
                    continue;
                }
            } else if (pilihan == 8) {
                printf("\nPencarian dibatalkan\n");
                continue;
            }

            if (searchCount == -1) {
                printf("Data tidak ditemukan\n");
            } else {
                printf("\nData yang ditemukan:\n");
                printf("-------------------------------------------------\n");
                for (int i = 0; i <= searchCount; i++) {
                    printf("%-15s: %d\n", "Database id", idToSearch[i]);
                    printf("%-15s: %s\n", "Nama", penduduk[idToSearch[i]].nama);
                    printf("%-15s: %s\n", "NIK", penduduk[idToSearch[i]].nik);
                    printf("%-15s: %s\n", "Tempat Lahir", penduduk[idToSearch[i]].tempatLahir);
                    printf("%-15s: %s\n", "Tanggal Lahir", penduduk[idToSearch[i]].tanggalLahir);
                    printf("%-15s: %s\n", "Agama", penduduk[idToSearch[i]].agama);
                    printf("%-15s: %s\n", "Golongan Darah", penduduk[idToSearch[i]].goldar);
                    printf("-------------------------------------------------\n");
                }
                printf("Total data ditemukan: %d\n", searchCount + 1);
            }
        } else if (pilihan == 5) {
            char namaFile[MAX_STR];
            printf("\nMasukkan nama file untuk penyimpanan (tanpa ekstensi): ");
            inputstr(namaFile, sizeof(namaFile));
            strcat(namaFile, ".txt");
            FILE *fptrw = fopen(namaFile, "r");
            if (fptrw != NULL) {
                fclose(fptrw);
                char overwrite;
                printf("File sudah ada, apakah anda yakin mau menimpa file (y/n)\n");
                scanf("%c", &overwrite);
                getchar();
                if (overwrite != 'y' && overwrite != 'Y') {
                    printf("Penyimpanan dibatalkan\n");
                    continue;
                } else {
                    fptrw = fopen(namaFile, "w");
                    fprintf(fptrw, "# Nama NIK TempatLahir TanggalLahir Agama GolonganDarah\n\n");
                    for (int i = 0; i < count; i++) {
                        fprintf(fptrw, "%s %s %s %s %s %s\n", penduduk[i].nama, penduduk[i].nik, penduduk[i].tempatLahir, penduduk[i].tanggalLahir, penduduk[i].agama, penduduk[i].goldar);
                    }
                    fclose(fptrw);
                    printf("Data berhasil disimpan ke dalam file penduduk-data.txt\n");
                }
            } else {
                fptrw = fopen(namaFile, "w");
                fprintf(fptrw, "# Nama NIK TempatLahir TanggalLahir Agama GolonganDarah\n\n");
                for (int i = 0; i < count; i++) {
                    fprintf(fptrw, "%s %s %s %s %s %s\n", penduduk[i].nama, penduduk[i].nik, penduduk[i].tempatLahir, penduduk[i].tanggalLahir, penduduk[i].agama, penduduk[i].goldar);
                }
                fclose(fptrw);
                printf("Data berhasil disimpan ke dalam file penduduk-data.txt\n");
            }
        
        } else if (pilihan == 6) {
            printf("\nProgram diberhentikan\n");
            break;
        }
    }
}