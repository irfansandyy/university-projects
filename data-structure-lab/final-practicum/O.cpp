#include <iostream>

int main() {
    int N;
    std::cin >> N;
    bool membesar = false, pohon = true;
    long sekarang, sebelumnya = __LONG_MAX__;
    for(int i = 0; i < N; i++) {
        std::cin >> sekarang; 
        if(!membesar && sekarang >= sebelumnya) membesar = true;
        if(membesar && sekarang <= sebelumnya) pohon = false;
        sebelumnya = sekarang;
    }
    std::cout << "Ini " << (pohon ? "" : "bukan ") << "pohon";
}