#include <stdio.h>
#include <string.h>

typedef struct {
    char nama[100];
    int matematika;
    int ipa;
    int bindo;
    int bing;
} Mahasiswa;

int main() { 
    int n;
    scanf("%d", &n);
    Mahasiswa listMahasiswa[n];
    for(int i = 0; i < n; i++) {
        scanf("%s", listMahasiswa[i].nama);
        scanf("%d", &listMahasiswa[i].matematika);
        scanf("%d", &listMahasiswa[i].ipa);
        scanf("%d", &listMahasiswa[i].bindo);
        scanf("%d", &listMahasiswa[i].bing);
    }
    int find;
    scanf("%d", &find);
    char findName[find][100];
    for(int i = 0; i < find; i++) {    
        scanf("%s", findName[i]);
    }
    for(int i = 0; i < find; i++) {
        int found = 0;
        for(int j = 0; j < n; j++) {
            if(strcmp(findName[i], listMahasiswa[j].nama) == 0) {
                printf("\nNilai %s", listMahasiswa[j].nama);
                printf("\nMatematika: %d", listMahasiswa[j].matematika);
                printf("\nIPA: %d", listMahasiswa[j].ipa);
                printf("\nBahasa Indonesia: %d", listMahasiswa[j].bindo);
                printf("\nBahasa Inggris: %d", listMahasiswa[j].bing);
                found = 1;
            }
        }
        if(found == 0) printf("\nNilai %s tidak ditemukan", findName[i]);
    }
}