extern void putInMemory (int segment, int address, char character);
unsigned int strlen(char* str);

void main() {
    char* str = "FP Telah Menunggumu";
    int i = 0;

    for (i = 0; i < strlen(str); i++) {
      char warna = 0x5;
      putInMemory(0xB000, 0x8000 + i * 2, str[i]);
      putInMemory(0xB000, 0x8001 + i * 2, warna);
    }

    while (1);
}

unsigned int strlen(char* str) {
    unsigned int len = 0;
    while(*str++) len++;
    return len;
}