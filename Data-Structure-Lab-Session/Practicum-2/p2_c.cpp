#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    std::vector<int> representative;
    std::map<int, int> districtVotes;
    int n, X, Xi;
    std::cin >> n >> X;
    for(int i = 0; i < X; i++) {
        std::cin >> Xi;
        representative.push_back(Xi);
        if(districtVotes.count(Xi)) {
            districtVotes[Xi] =  districtVotes.at(Xi) + 1;
        } else {
            districtVotes[Xi] = 1;
        }
    }
    std::sort(representative.begin(), representative.end());
    int biggest = -1;
    int mostVotesIndex = -1;
    for(int i = 1; i < n; i++) {
        if(districtVotes.at(i) > biggest) {
            biggest = districtVotes.at(i);
            mostVotesIndex = i;
        }
    }
    std::cout << mostVotesIndex << " " << representative[(X%2==0 ? X/2 - 1 : X/2)] << "\n";
    if(mostVotesIndex == representative[(X%2==0 ? X/2 - 1 : X/2)]) {
        std::cout << "Tidak ada yang menang\n";
    } else {
        std::cout << "Distrik " << mostVotesIndex << " menang\n";
    }
}