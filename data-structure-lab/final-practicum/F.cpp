#include <iostream>
#include <string>
#include <stack>

int main() {
    std::stack<int> data;
    
    while(true) {
        std::string S;
        std::cin >> S;
        if(S.empty() | S == "\n") break;

        if(S == "+") {
            int a, b;
            a = data.top();
            data.pop();
            b = data.top();
            data.push(a);
            data.push(a+b);
        } else if(S == "C") {
            data.pop();
        } else if(S == "D") {
            data.push(data.top()*2);
        } else {
            data.push(std::stoi(S));
        }
    }

    long sum = 0;
    while(!data.empty()) {
        sum += data.top();
        data.pop();
    }

    std::cout << sum;
    return 0;
}