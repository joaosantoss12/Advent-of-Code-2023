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

    int currentReds;
    int currentGreens;
    int currentBlues;

    int invalidGames = 0;
    int validGames = 0;
    bool currentGameValid;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    while (getline(file, line)) {
        currentGameValid = true;

        istringstream iss(line);

        iss >> currentGameID >> currentGameID;
        currentGameID.erase(currentGameID.length() - 1);

        while (iss >> nextToken) {
            iss >> nextToken2;

            if(nextToken2[nextToken2.length()-1] == ',' || nextToken2[nextToken2.length()-1] == ';')
                nextToken2.erase(nextToken2.length() - 1);

            if (nextToken2.compare("red") == 0) {
                currentReds = stoi(nextToken);
                if (currentReds > 12) {
                    ++invalidGames;
                    currentGameValid = false;
                    break;
                }
            } else if (nextToken2.compare("green") == 0) {
                currentGreens = stoi(nextToken);
                if (currentGreens > 13) {
                    ++invalidGames;
                    currentGameValid = false;
                    break;
                }
            } else if (nextToken2.compare("blue") == 0) {
                currentBlues = stoi(nextToken);
                if (currentBlues > 14) {
                    ++invalidGames;
                    currentGameValid = false;
                    break;
                }
            }
        }

        if (currentGameValid) {
            ++validGames;
            answer += stoi(currentGameID);
        }
    }

    cout << "INVALID GAMES: " << invalidGames << " | VALID GAMES: " << validGames << endl;
    cout << "ANSWER: " << answer << endl;

    return 0;
}
