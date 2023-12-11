#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    int answer = 0;
    int currentCardAnswer;

    ifstream file("day 4/input.txt");

    string line;
    vector<int> winningNumbers;
    vector<int> myNumbers;

    string cardID;
    string nextToken;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    bool foundSeparator;
    bool foundAnyWinningNumber;

    while (getline(file, line)) {
        currentCardAnswer = 0;
        foundSeparator = false;
        foundAnyWinningNumber = false;

        istringstream iss(line);
        iss >> cardID >> cardID;
        cardID.erase(cardID.length()-1);    // delete the ':'

        winningNumbers.clear();
        myNumbers.clear();

        while(iss >> nextToken){
            if(nextToken == "|")
                foundSeparator = true;

            if(isdigit(nextToken[0]) && !foundSeparator){
                winningNumbers.push_back(stoi(nextToken));
            }
            else if(isdigit(nextToken[0]) && foundSeparator){
                myNumbers.push_back(stoi(nextToken));
            }

        }

        for(int i=0;i<winningNumbers.size();i++){
            for(int j=0;j<myNumbers.size();j++){
                if(winningNumbers[i] == myNumbers[j] && !foundAnyWinningNumber){
                    currentCardAnswer = 1;
                    foundAnyWinningNumber = true;
                }
                else if(winningNumbers[i] == myNumbers[j] && foundAnyWinningNumber){
                    currentCardAnswer *= 2;
                }
            }
        }

        answer += currentCardAnswer;
    }

    cout << "ANSWER: " << answer;
}