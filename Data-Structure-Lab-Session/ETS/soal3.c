#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CHAR 41

typedef struct {
    int id;
    char nama[MAX_CHAR];
    unsigned int warisan;
    bool isAlive;
} Anggota;

typedef struct node {
    Anggota data;
    struct node *left;
    struct node *right;
} Node;

typedef struct {
    Node *root;
} BST;

Node *createNode(Anggota data) {
    Node *np = (Node*) malloc(sizeof(Node));
    np->data = data;
    np->left = NULL;
    np->right = NULL;
    return np;
}

BST *createBST() {
    BST *tp = (BST*) malloc(sizeof(BST));
    tp->root = NULL;
    return tp;
}

Node* search(Node *root, int id) {
    while (root != NULL) {
        if (id < root->data.id) root = root->left;
        else if (id > root->data.id) root = root->right;
        else return root;
    }
    return root;
}

bool find(BST *tp, int id) {
    Node *temp = search(tp->root, id);
    if (temp == NULL) return false;
    
    if (temp->data.id == id) return true;
    else return false;
}

Node* utilityInsert(Node *root, Anggota data) {
    if (root == NULL) return createNode(data);

    if (data.id < root->data.id) root->left = utilityInsert(root->left, data);
    else if (data.id > root->data.id) root->right = utilityInsert(root->right, data);
    return root;
}

void insert(BST *tp, Anggota data) {
    if (!find(tp, data.id)) tp->root = utilityInsert(tp->root, data);
    else printf("Id sudah ada, pilih id lain\n");
}

Node* findMinNode(Node *np) {
    Node *curr = np;
    while (curr && curr->left != NULL) curr = curr->left;
    return curr;
}

void buatAnggota(BST *tp) {
    Anggota data;
    printf("\nMasukkan id: ");
    scanf("%d", &data.id);
    getchar();
    printf("Masukkan nama: ");
    fgets(data.nama, MAX_CHAR, stdin);
    data.nama[strcspn(data.nama, "\n")] = 0;
    printf("Masukkan warisan: ");
    scanf("%u", &data.warisan);
    data.isAlive = true;
    insert(tp, data);
}

void inOrder(Node *root) {
    if(root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->data.id);
    inOrder(root->right);
}

void printAnggota(Node *root) {
    printf("\nBerikut id Anggota di Print Secara inOrder: \n");
    inOrder(root);
    printf("\n");
}

bool adaKeturunanHidup(Node *node) {
    if (node == NULL) return 0;
    if (node->data.isAlive) return 1;
    return adaKeturunanHidup(node->left) || adaKeturunanHidup(node->right);
}

void bagiWarisan(Node *root, unsigned int warisan) {
    if (root == NULL) return;

    if (root->data.isAlive) {
        root->data.warisan += warisan;
        return;
    }

    int kiriAdaAhliWaris = 0;
    int kananAdaAhliWaris = 0;

    if (root->left != NULL) kiriAdaAhliWaris = root->left->data.isAlive || adaKeturunanHidup(root->left);
    if (root->right != NULL) kananAdaAhliWaris = root->right->data.isAlive || adaKeturunanHidup(root->right);

    if (!kiriAdaAhliWaris && !kananAdaAhliWaris) {
        printf("Tidak ada ahli waris hidup untuk warisan sebesar %u dari simpul wafat.\n", warisan);
        return;
    }

    if (kiriAdaAhliWaris && !kananAdaAhliWaris) {
        if (root->left->data.isAlive) root->left->data.warisan += warisan;
        else bagiWarisan(root->left, warisan);
    } else if (!kiriAdaAhliWaris && kananAdaAhliWaris) {
        if (root->right->data.isAlive) root->right->data.warisan += warisan;
        else bagiWarisan(root->right, warisan);
    } else {
        unsigned int warisanKiri = (unsigned int)(0.6 * warisan);
        unsigned int warisanKanan = warisan - warisanKiri;

        if (root->left->data.isAlive) root->left->data.warisan += warisanKiri;
        else bagiWarisan(root->left, warisanKiri);

        if (root->right->data.isAlive) root->right->data.warisan += warisanKanan;
        else bagiWarisan(root->right, warisanKanan);
    }
}

void kematianAnggota(BST *tp) {
    int id;
    printf("\nMasukkan id Anggota yang Meninggal: ");
    scanf("%d", &id);
    while(!find(tp, id) || search(tp->root, id)->data.isAlive == false) {
        printf("Id tidak ditemukan, masukkan id yang benar\n");
        printf("Masukkan id Anggota yang Meninggal: ");
        scanf("%d", &id);
    }
    Node *dead = search(tp->root, id);
    unsigned int totalWarisan = dead->data.warisan;
    dead->data.isAlive = false;
    bagiWarisan(dead, totalWarisan);
    dead->data.warisan = 0;
    printf("Anggota dengan ID %d telah ditandai meninggal dan warisan sebesar %u telah dibagi.\n", id, totalWarisan);
}

int main() {
    int choice;
    BST *tp = createBST();
    do {
        printf("\n========= Menu =========\n");
        printf("1. Tambah Anggota Baru\n");
        printf("2. Struktur Inorder\n");
        printf("3. Kematian Anggota\n");
        printf("4. Keluar Dari Program\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        printf("========================\n");

        switch (choice) {
            case 1:
                buatAnggota(tp);
                break;
            case 2: 
                printAnggota(tp->root);
                break;
            case 3:
                kematianAnggota(tp);
                break;
            case 4:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (choice != 4);
}