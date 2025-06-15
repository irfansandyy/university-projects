#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> heights(n);
    for (int i = 0; i < n; ++i) std::cin >> heights[i];

    std::vector<int> widths(n);
    for (int i = 0; i < n; ++i) std::cin >> widths[i];

    std::vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + widths[i];
    }

    std::stack<int> stack;
    stack.push(-1);
    long long maxArea = 0;

    for (int i = 0; i < n; i++) {
        while (stack.top() != -1 && heights[i] <= heights[stack.top()]) {
            long long height = heights[stack.top()];
            stack.pop();
            long long width = prefix[i] - prefix[stack.top() + 1];
            maxArea = std::max(maxArea, height * width);
        }
        stack.push(i);
    }

    while (stack.top() != -1) {
        long long height = heights[stack.top()];
        stack.pop();
        long long width = prefix[n] - prefix[stack.top() + 1];
        maxArea = std::max(maxArea, height * width);
    }
    std::cout << maxArea << std::endl;

    return 0;
}