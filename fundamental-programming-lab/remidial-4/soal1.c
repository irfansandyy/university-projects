#include <stdio.h>
#include <string.h>

typedef struct Relasi{
    char nama[101];
    struct Relasi *next; 
} Kontak;

typedef Kontak *ptrKontak;

int main() {
    ptrKontak start = NULL;
    int n;
    scanf("%d", &n);
    char listNama[101][101];
    for(int i = 0; i < n; i++) {
        ptrKontak temp = (ptrKontak)malloc(sizeof(Kontak));
        char nama1[101];
        char nama2[101];
        scanf("%s", nama1);
        scanf("%s", nama2);
        if(strcmp(nama2, "-") == 0) {  
            strcpy(temp->nama, nama1);
            temp->next = start;
        } else {
            strcpy(temp->nama, nama1);
            temp->next = start;
        }
    }
}