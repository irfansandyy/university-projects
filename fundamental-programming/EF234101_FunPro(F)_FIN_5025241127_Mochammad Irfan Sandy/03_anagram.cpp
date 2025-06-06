#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main() {
    int a, sizepattern;
    string input;
    string pattern;

    cout << "String: ";
    cin >> input;
    cout << "Pattern: ";
    cin >> pattern;

    sizepattern = pattern.size();

    cout << "Anagram: " << endl;

    // Loop through the input string to get all substrings of size equal to pattern
    for (a = 0; a <= (int) input.size() - sizepattern; a++) {
        string substring = input.substr(a, sizepattern);
        
        if (is_permutation(substring.begin(), substring.end(), pattern.begin())) {
                cout << substring << "\t at index " << a << endl;
            }
        }

    return 0;
}
