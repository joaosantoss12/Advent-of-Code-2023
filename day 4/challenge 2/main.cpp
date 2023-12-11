#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    int answer = 0;
    int copies;

    ifstream file("day 4/input.txt");

    string line;
    vector<string> lines;

    string cardID;
    string nextToken;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    vector<int> howManyDoesItGenerate(lines.size(), 0);
    vector<int> howManyCopiesDoesItHave(lines.size(), 1);

    for (int i = 0; i < lines.size(); i++) {
        istringstream iss(lines[i]);

        vector<int> winningNumbers;
        vector<int> myNumbers;

        copies = 0;

        iss >> cardID >> cardID;
        cardID.pop_back(); // remove the trailing ':'

        while (iss >> nextToken && nextToken != "|") {
            if (isdigit(nextToken[0])) {
                winningNumbers.push_back(stoi(nextToken));
            }
        }

        while (iss >> nextToken) {
            if (isdigit(nextToken[0])) {
                myNumbers.push_back(stoi(nextToken));
            }
        }

        for (int k = 0; k < winningNumbers.size(); k++) {
            for (int j = 0; j < myNumbers.size(); j++) {
                if (winningNumbers[k] == myNumbers[j]) {
                    ++copies;
                }
            }
        }

        for (int x = 0; x < copies && (stoi(cardID) + x) < lines.size(); x++) {
            howManyCopiesDoesItHave[stoi(cardID) + x] += 1 * howManyCopiesDoesItHave[stoi(cardID)-1]; // next cards have one more copy
            howManyDoesItGenerate[stoi(cardID) - 1] += 1;    // current card generated another copy
        }
    }

    for (int y = 0; y < lines.size(); y++) {
        answer += howManyCopiesDoesItHave[y];
        //cout << endl << "howManyCopiesDoesItHave[" << y+1 << "]: " << howManyCopiesDoesItHave[y] <<  " howManyDoesItGenerate[" << y+1 << "]: " << howManyDoesItGenerate[y] << endl;
    }

    cout << "ANSWER: " << answer;
}
