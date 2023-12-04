#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    int answer = 0;
    ifstream file("day 2/input.txt");

    string line;
    string currentGameID;
    string nextToken, nextToken2;

    int maxReds;
    int maxGreens;
    int maxBlues;


    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    while (getline(file, line)){
        istringstream iss(line);

        iss >> currentGameID >> currentGameID;
        currentGameID.erase(currentGameID.length() - 1);

        maxReds = 0;
        maxGreens = 0;
        maxBlues = 0;

        while (iss >> nextToken) {
            iss >> nextToken2;

            if(nextToken2[nextToken2.length()-1] == ',' || nextToken2[nextToken2.length()-1] == ';')
                nextToken2.erase(nextToken2.length() - 1);

            if (nextToken2.compare("red") == 0) {
                if(maxReds < stoi(nextToken))
                    maxReds = stoi(nextToken);
            }
            else if (nextToken2.compare("green") == 0) {
                if(maxGreens < stoi(nextToken))
                    maxGreens = stoi(nextToken);
            }
            else if (nextToken2.compare("blue") == 0) {
                if(maxBlues < stoi(nextToken))
                    maxBlues = stoi(nextToken);
            }
        }

        answer += (maxReds*maxGreens*maxBlues);
    }

    cout << "ANSWER: " << answer << endl;

    return 0;
}
