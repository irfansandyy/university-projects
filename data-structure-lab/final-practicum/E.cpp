#include <iostream>
#include <string>
#include <queue>

int main() {
    std::deque<long> q;
    long N;
    std::cin >> N;
    for (long i = 0; i < N; ++i) {
        std::string command;
        std::cin >> command;
        if (command == "depan") {
            if (q.empty()) {
                std::cout << "\n";
                continue;
            }
            std::cout << q.front() << "\n";
            q.pop_front();
        } else if (command == "belakang") {
            if (q.empty()) {
                std::cout << "\n";
                continue;
            }
            std::cout << q.back() << "\n";
            q.pop_back();
        } else if (command == "tambahDepan") {
            long x;
            std::cin >> x;
            q.push_front(x);
        } else if (command == "tambahBelakang") {
            long x;
            std::cin >> x;
            q.push_back(x);
        } else if (command == "balik") {
            if (q.size() >= 2) {
                std::swap(q.front(), q.back());
            }
        }
    }

    return 0;
}           