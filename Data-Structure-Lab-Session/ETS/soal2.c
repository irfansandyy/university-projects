#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CHAR 41

int timestamp_kedatangan = 0;

typedef struct {
    int id;
    char nama[MAX_CHAR];
    int prioritas;
    int timestamp;
} Laporan;

typedef struct node {
    Laporan data;
    struct node *next;
} Node;

typedef struct {
    Node *top;
} PriorityQueue;

bool isEmpty(PriorityQueue *pq) {
    return (pq->top == NULL);
}

void push(PriorityQueue *pq, Laporan data) {
    Node *temp = pq->top;
    Node *np = (Node*) malloc (sizeof(Node));
    np->data = data;
    np->next = NULL;

    if (isEmpty(pq)) {
        pq->top = np;
        return;
    }

    if (data.prioritas < pq->top->data.prioritas || (data.prioritas == pq->top->data.prioritas && data.timestamp < pq->top->data.timestamp)) {
        np->next = pq->top;
        pq->top = np;
    }
    else {
        while (temp->next != NULL && (temp->next->data.prioritas < data.prioritas || (temp->next->data.prioritas == data.prioritas && temp->next->data.timestamp < data.timestamp))) temp = temp->next;
        np->next = temp->next;
        temp->next = np;
    }
}

void pop(PriorityQueue *pq) {
    if (!isEmpty(pq)) {
        Node *temp = pq->top;
        pq->top = pq->top->next;
        free(temp);
    }
}

Laporan *top(PriorityQueue *pq) {
    if (!isEmpty(pq)) return &pq->top->data;
    else return NULL;
}

PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*) malloc(sizeof(PriorityQueue));
    pq->top = NULL;
    return pq;
}

void buatLaporan(PriorityQueue* pq) {
    Laporan data;
    printf("Masukkan id: ");
    scanf("%d", &data.id);
    getchar();
    printf("Masukkan nama: ");
    fgets(data.nama, MAX_CHAR, stdin);
    data.nama[strcspn(data.nama, "\n")] = 0;
    printf("Masukkan prioritas: ");
    scanf("%d", &data.prioritas);
    data.timestamp = ++timestamp_kedatangan;
    push(pq, data);
}

void prosesLaporan(PriorityQueue* pq) {
    Laporan *data = top(pq);
    if(data == NULL) {
        printf("Laporan Habis\n");
        return;
    }
    printf("Laporan yang Akan di Proses\n");
    printf("Id: %d\n", data->id);
    printf("Nama: %s\n", data->nama);
    printf("Prioritas: %d\n", data->prioritas);
    printf("Timestamp: %d\n", data->timestamp);
    pop(pq);
}

void tampilkanLaporan(PriorityQueue* pq) {
    Node *np = pq->top;
    printf("Data Seluruh Laporan\n");
    printf("Id | Nama | Prioritas | Timestamp\n");
    while(np != NULL) {
        printf("%d | %s | %d | %d\n", np->data.id, np->data.nama, np->data.prioritas, np->data.timestamp);
        np = np->next;
    }
}

int main() {
    int choice;
    PriorityQueue *pq = createPriorityQueue();
    do {
        printf("\n========= Menu =========\n");
        printf("1. Tambah Laporan Baru\n");
        printf("2. Proses Laporan\n");
        printf("3. Tampilkan Semua Laporan Dalam Antrian\n");
        printf("4. Keluar Dari Program\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        printf("========================\n\n");

        switch (choice) {
            case 1:
                buatLaporan(pq);
                break;
            case 2: 
                prosesLaporan(pq);
                break;
            case 3:
                tampilkanLaporan(pq);
                break;
            case 4:
                printf("Keluar dari program\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi\n");
        }
    } while (choice != 4);
}