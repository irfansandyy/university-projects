#include <iostream>
#include <string>
#include <set>

int main() {
    std::string S;
    std::cin >> S;
    std::multiset<char> unique;
    for (char c : S) unique.insert(c);
    for (long unsigned i = 0; i < S.size(); ++i) {
        if (unique.count(S.at(i)) == 1) {
            std::cout << i;
            return 0;
        }
    }
    std::cout << -1;
    return 0;
}