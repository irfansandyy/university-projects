#include <iostream>
#include <string>
#include <map>

int main() {
    std::map<std::string, long double> inventory;
    long double N;
    std::cin >> N;

    std::string cmd;
    std::string name;
    long double quantity;
    for(long double i = 0; i < N; i++) {
        std::cin >> cmd;
        std::cin >> name;
        std::cin >> quantity;
        if(cmd == "ADD") {
            if(inventory.count(name)) inventory[name] += quantity;
            else inventory[name] = quantity;
        } else if(cmd == "SELL") {
            if(inventory.count(name)) {
                if(inventory[name] >= quantity) {
                    inventory[name] -= quantity;
                    std::cout << "SUCCESS\n";
                } else {
                    std::cout << "not enough stock\n";
                }
            } else {
                std::cout << "item not found\n";
            }
        }
    }
}