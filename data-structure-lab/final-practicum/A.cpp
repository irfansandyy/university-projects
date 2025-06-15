#include <iostream>
#include <set>

long long difficultyInterval(long long d) {
    if (d <= 1) return 0;
    return (d - 1) * d * (d + 1) / 6;
}

int main() {
    int N, M;
    std::cin >> N >> M;

    std::set<int> buying;
    buying.insert(0);
    buying.insert(N + 1);

    long long total = difficultyInterval(N + 1);

    for (int i = 0; i < M; ++i) {
        int pos;
        std::cin >> pos;

        if (buying.count(pos)) {
            auto it = buying.find(pos);
            int left = *std::prev(it);
            int right = *std::next(it);

            total -= difficultyInterval(pos - left);
            total -= difficultyInterval(right - pos);
            total += difficultyInterval(right - left);

            buying.erase(it);
        } else {
            buying.insert(pos);

            auto it = buying.find(pos);
            int left = *std::prev(it);
            int right = *std::next(it);

            total -= difficultyInterval(right - left);
            total += difficultyInterval(pos - left);
            total += difficultyInterval(right - pos);
        }
        std::cout << total << '\n';
    }

    return 0;
}