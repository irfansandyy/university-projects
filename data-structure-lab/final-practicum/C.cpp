#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int N;
    std::cin >> N;
    std::vector<int> cards(N);
    for(int i = 0; i < N; i++) std::cin >> cards[i];

    int left = 0;
    int right = cards.size() - 1;
    int leftMax = cards[left];
    int rightMax = cards[right];
    int energy = 0;

    while (left < right) {
        if (leftMax < rightMax) {
            left++;
            leftMax = std::max(leftMax, cards[left]);
            energy += leftMax - cards[left];
        } else {
            right--;
            rightMax = std::max(rightMax, cards[right]);
            energy += rightMax - cards[right];
        }
    }

    std::cout << energy;

    return 0;
}