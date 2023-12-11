#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool checkOnlyZeros(vector<long int> numbers){
    for(int i = 0; i < numbers.size(); i++){
        if(numbers[i] != 0)
            return false;
    }
    return true;
}

int main() {
    long int answer = 0;
    long int answer_aux;

    ifstream file("day 9/input.txt");

    string line;
    string nextToken;
    int nLine = -1;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        ++nLine;

        answer_aux = 0;
        vector<long int> currentLineNumbers;
        while(iss >> nextToken){
            currentLineNumbers.push_back(stol(nextToken));
        }

        vector<long int> auxNumbers;

        answer_aux = currentLineNumbers[currentLineNumbers.size()-1];

        for(int i = 0; i <= currentLineNumbers.size()-2; i++) {
            long int diff = (currentLineNumbers[i+1] - currentLineNumbers[i]);

            auxNumbers.push_back(diff);
        }

        while(true){
            if(checkOnlyZeros(auxNumbers))
                break;

            if(auxNumbers.size() == 1){
                answer_aux = 0;
                break;
            }

            answer_aux += auxNumbers[auxNumbers.size()-1];

            vector<long int> aux;

            for(int i = 0; i <= auxNumbers.size()-2; i++){
                long int diff = (auxNumbers[i+1] - auxNumbers[i]);


                aux.push_back(diff);
            }

            auxNumbers = aux;
        }

        answer += answer_aux;
    }

    cout << "ANSWER: " << answer;
}