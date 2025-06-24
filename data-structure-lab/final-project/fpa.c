#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

#define NUMBER_LENGTH 6
#define NAME_LENGTH 25
#define TEMP_SIZE 256
#define ARRAY_DEFAULT_CAPACITY 128
#define MIN_RECORDS 50
#define BINARY_FILE "result.bin"

typedef struct component {
    char number[NUMBER_LENGTH+1];
    char name[NAME_LENGTH+1];
    int stock;
    double price;
} Component;

typedef struct component_array {
    Component *data;
    int size;
    int capacity;
} Component_Array;

void reset_terminal_mode();
void set_raw_mode();
void clear_screen();
void print_menu(int selected);
void handle_choice(int choice);
void init_component_array(Component_Array *arr);
void add_component(Component_Array *arr);
void edit_component(Component_Array *arr);
void delete_component(Component_Array *arr);
void print_components_with_index(Component_Array *arr);
void print_components_without_index(Component_Array *arr);

void load_components(Component_Array *arr);
void save_components(Component_Array *arr);
void fill_records(Component_Array *arr);
void pause_screen();

Component_Array components;
struct termios orig_termios;
const char *menu_items[] = {
    "1. \033[4mM\033[24menambah data",
    "2. Meng\033[4mu\033[24mbah data",
    "3. Menampilkan semua data dengan inde\033[4mx\033[24m",
    "4. Menampilkan semua data \033[4mt\033[24manpa index",
    "5. \033[4mH\033[24mapus data",
    "6. \033[4mK\033[24meluar"
};
const int MENU_SIZE = sizeof(menu_items) / sizeof(menu_items[0]);

int main() {
    set_raw_mode();
    init_component_array(&components);
    load_components(&components);
    fill_records(&components);
    int selected = 0;
    char c;

    while (true) {
        print_menu(selected);
        c = getchar();

        if (c == '\033') {
            getchar();
            switch(getchar()) {
                case 'A':
                    selected = (selected - 1 + MENU_SIZE) % MENU_SIZE;
                    break;
                case 'B':
                    selected = (selected + 1) % MENU_SIZE;
                    break;
            }
        } else if (c >= '1' && c <= '6') {
            selected = c - '1';
        } else if (c == 'M' || c == 'm') {
            selected = 0;
        } else if (c == 'U' || c == 'u') {
            selected = 1;
        } else if (c == 'X' || c == 'x') {
            selected = 2;
        } else if (c == 'T' || c == 't') {
            selected = 3;   
        } else if (c == 'H' || c == 'h') {
            selected = 4; 
        } else if (c == 'K' || c == 'k') {
            selected = 5; 
        } else if (c == '\n' || c == '\r') {
            if (selected == 5) break;
            handle_choice(selected);
        } else if (c == 'q' || c == 'Q') {
            break;
        }
    }

    reset_terminal_mode();
    clear_screen();
    printf("Program selesai.\n");
    return 0;
}

void reset_terminal_mode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void set_raw_mode() {
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(reset_terminal_mode);

    new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

void clear_screen() {
    printf("\033[2J\033[H");
}

void pause_screen() {
    printf("\nTekan ENTER untuk melanjutkan");
    while (getchar() != '\n'); 
    clear_screen();
}

void print_menu(int selected) {
    clear_screen();
    printf("Gunakan panah atas/bawah atau tekan nomor/karakter untuk memilih:\n\n");
    for (int i = 0; i < MENU_SIZE; i++) {
        if (i == selected)
            printf("> %s\n", menu_items[i]);
        else
            printf("  %s\n", menu_items[i]);
    }
    printf("\nPilihan anda sekarang: %d\n", selected + 1);
    printf("Tekan ENTER untuk melanjutkan\n");
}

void handle_choice(int choice) {
    clear_screen();
    reset_terminal_mode();
    if(choice == 0) add_component(&components);
    if(choice == 1) edit_component(&components);
    if(choice == 2) print_components_with_index(&components);
    if(choice == 3) print_components_without_index(&components);
    if(choice == 4) delete_component(&components);
    set_raw_mode();
}

void init_component_array(Component_Array *arr) {
    arr->size = 0;
    arr->capacity = ARRAY_DEFAULT_CAPACITY;
    arr->data = (Component *)malloc(arr->capacity * sizeof(Component));
    if (arr->data == NULL) {
        perror("Gagal malloc");
        exit(EXIT_FAILURE);
    }
}

void add_component(Component_Array *arr) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = (Component *)realloc(arr->data, arr->capacity * sizeof(Component));
        if (arr->data == NULL) {
            perror("Gagal realloc");
            exit(EXIT_FAILURE);
        }
    }
    Component new_comp;
    int valid = false;
    char temp[TEMP_SIZE];

    printf("Tambah Data\n");
    do {
        valid = false;
        printf("Nomer Komponen: ");
        fflush(stdout);
        fgets(new_comp.number, NUMBER_LENGTH + 1, stdin);
        if (!strchr(new_comp.number, '\n')) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        new_comp.number[strcspn(new_comp.number, "\n")] = 0;

        if (strlen(new_comp.number) > 0) {
            for (int i = 0; i < arr->size; i++) {
                if (strncmp(new_comp.number, arr->data[i].number, NUMBER_LENGTH+1) == 0) {
                    valid = true;
                    break;
                }
            }
        }

        if (strlen(new_comp.number) == 0) printf("Input tidak boleh kosong!\n");
        if (valid) printf("Nomor komponen sudah ada!\n");

    } while (strlen(new_comp.number) == 0 || valid);

    do {
        printf("Nama Komponen: ");
        fflush(stdout);
        fgets(new_comp.name, NAME_LENGTH+1, stdin);
        if (!strchr(new_comp.name, '\n')) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        new_comp.name[strcspn(new_comp.name, "\n")] = 0;
        if (strlen(new_comp.name) == 0) printf("Input tidak boleh kosong!\n");
    } while (strlen(new_comp.name) == 0);

    do {
        printf("Jumlah Stok: ");
        fflush(stdout);
        fgets(temp, sizeof(temp), stdin);

        char *endptr;
        new_comp.stock = (int)strtol(temp, &endptr, 10);
        if (endptr == temp || *endptr != '\n') {
            printf("Input tidak valid. Masukkan angka bulat.\n");
            valid = false;
        } else valid = true;
    } while (!valid);

    do {
        printf("Harga Komponen: ");
        fflush(stdout);
        fgets(temp, sizeof(temp), stdin);

        char *endptr;
        new_comp.price = strtod(temp, &endptr);
        if (endptr == temp || *endptr != '\n') {
            printf("Input tidak valid. Masukkan angka desimal.\n");
            valid = false;
        } else valid = true;
    } while (!valid);

    arr->data[arr->size++] = new_comp;
    save_components(arr);
    printf("Data berhasil ditambahkan.\n");
}

void edit_component(Component_Array *arr) {
    int valid = false;
    int index;
    char temp[TEMP_SIZE];

    printf("Nomer Komponen: ");
    fflush(stdout);
    fgets(temp, NUMBER_LENGTH + 1, stdin);
    if (!strchr(temp, '\n')) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    temp[strcspn(temp, "\n")] = 0;

    if (strlen(temp) > 0) {
        for (int i = 0; i < arr->size; i++) {
            if (strncmp(temp, arr->data[i].number, NUMBER_LENGTH + 1) == 0) {
                valid = true;
                index = i;
            }
        }
    }

    if (strlen(temp) == 0) {
        printf("Input tidak boleh kosong!\n");
        pause_screen();
        return;
    }
    if (!valid) {
        printf("Nomor komponen tidak ada!\n");
        pause_screen();
        return;
    }

    Component *comp = &arr->data[index];
    printf("Data lama:\nNama: %s\nStok: %d\nHarga: %.2f\n", comp->name, comp->stock, comp->price);

    do {
        printf("Nama Komponen: ");
        fflush(stdout);
        fgets(comp->name, NAME_LENGTH+1, stdin);
        if (!strchr(comp->name, '\n')) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        comp->name[strcspn(comp->name, "\n")] = 0;
        if (strlen(comp->name) == 0) printf("Input tidak boleh kosong!\n");
    } while (strlen(comp->name) == 0);

    do {
        printf("Jumlah Stok: ");
        fflush(stdout);
        fgets(temp, sizeof(temp), stdin);

        char *endptr;
        comp->stock = (int)strtol(temp, &endptr, 10);
        if (endptr == temp || *endptr != '\n') {
            printf("Input tidak valid. Masukkan angka bulat.\n");
            valid = false;
        } else valid = true;
    } while (!valid);

    do {
        printf("Harga Komponen: ");
        fflush(stdout);
        fgets(temp, sizeof(temp), stdin);

        char *endptr;
        comp->price = strtod(temp, &endptr);
        if (endptr == temp || *endptr != '\n') {
            printf("Input tidak valid. Masukkan angka desimal.\n");
            valid = false;
        } else valid = true;
    } while (!valid);

    save_components(arr);
    printf("Data berhasil diperbarui.\n");
}

void delete_component(Component_Array *arr) {
    int valid = false;
    int index;
    char temp[NUMBER_LENGTH + 1];
    printf("Nomer Komponen: ");
    fflush(stdout);
    fgets(temp, NUMBER_LENGTH + 1, stdin);
    if (!strchr(temp, '\n')) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    temp[strcspn(temp, "\n")] = 0;

    if (strlen(temp) > 0) {
        for (int i = 0; i < arr->size; i++) {
            if (strncmp(temp, arr->data[i].number, NUMBER_LENGTH + 1) == 0) {
                valid = true;
                index = i;
            }
        }
    }

    if (strlen(temp) == 0) {
        printf("Input tidak boleh kosong!\n");
        pause_screen();
        return;
    }
    if (!valid) {
        printf("Nomor komponen tidak ada!\n");
        pause_screen();
        return;
    }

    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;

    if ((arr->size < arr->capacity/2) && (arr->size > ARRAY_DEFAULT_CAPACITY)) {
        arr->capacity /= 2;
        arr->data = (Component *)realloc(arr->data, arr->capacity * sizeof(Component));
        if (arr->data == NULL) {
            perror("Gagal realloc");
            exit(EXIT_FAILURE);
        }
    }

    save_components(arr);
    printf("Data berhasil dihapus.\n");
}

void print_components_with_index(Component_Array *arr) {
    if (arr->size == 0) {
        printf("Tidak ada data.\n");
        return;
    }

    double total = 0;
    int count = 0;
    
    for(int i = 0; i < arr->size;i++){
        printf("[%d] Nomor: %s\t | Nama: %s\t | Stok: %d\t | Harga: %.2f\n",
                i, arr->data[i].number, arr->data[i].name,
                arr->data[i].stock, arr->data[i].price);
        total += arr->data[i].stock * arr->data[i].price;
        count++;
        
    }
    printf("\nTotal komponen: %d\nTotal nilai aset: Rp %.2f\n", count, total);
    pause_screen();
}

void print_components_without_index(Component_Array *arr) {
    if (arr->size == 0) {
        printf("Tidak ada data.\n");
        return;
    }
    double total = 0;
    int count = 0;
    for (int i = 0; i < arr->size; i++) {
        printf("Nomor: %s\t | Nama: %s\t | Stok: %d\t | Harga: %.2f\n",
                arr->data[i].number, arr->data[i].name,
                arr->data[i].stock, arr->data[i].price);
        total += arr->data[i].stock * arr->data[i].price;
        count++;
        
    }
    printf("\nTotal komponen: %d\nTotal nilai aset: Rp %.2f\n", count, total);
    pause_screen();
}

void load_components(Component_Array *arr) {
    FILE *f = fopen(BINARY_FILE, "rb");
    if(!f) return; 
    Component temp;
    while (fread(&temp, sizeof(Component), 1, f) == 1) {
        if (arr->size >= arr->capacity) {
            arr->capacity *= 2;
            arr->data = realloc(arr->data, arr->capacity * sizeof(Component));
        }
        arr->data[arr->size++] = temp;
    }
    fclose(f);
}

void save_components(Component_Array *arr) {
    FILE *f = fopen(BINARY_FILE, "wb");
    if (!f) {
        perror("Gagal menulis file");
        return;
    }
    fwrite(arr->data, sizeof(Component), arr->size, f);
    fclose(f);
}

void fill_records(Component_Array *arr) {
    while (arr->size < 50) {
        Component new_comp;

        snprintf(new_comp.number, NUMBER_LENGTH + 1, "ABC%03d", arr->size + 1);

        snprintf(new_comp.name, NAME_LENGTH + 1, "Komponen%d", arr->size + 1);

        new_comp.stock = (arr->size + 1) * 2;
        new_comp.price = 10000.0 + (arr->size * 500.0);

        arr->data[arr->size++] = new_comp;
    }
}