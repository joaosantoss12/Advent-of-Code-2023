#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    int answer = 0;
    ifstream file("day 3/input.txt");

    string line;
    vector<vector<char>> tokens;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    int nLine = -1;

    while (getline(file, line)) {
        ++nLine;
        vector<char> currentLine;
        for (int i = 0; i < line.length(); i++) {
            currentLine.push_back(line[i]);
        }

        tokens.push_back(currentLine);
    }

    for (int i = 0; i < tokens.size(); i++) {
        string num;
        for (int j = 0; j < tokens[i].size(); j++) {

            if (!isdigit(tokens[i][j]) && tokens[i][j] != '.') {

                // RIGHT
                if (j + 1 < tokens[i].size() && isdigit(tokens[i][j + 1])) {
                    num = tokens[i][j + 1];
                    if (isdigit(tokens[i][j + 2]) && j + 2 < tokens[i].size()) {
                        num += tokens[i][j + 2];
                        if (isdigit(tokens[i][j + 3]) && j + 3 < tokens[i].size()) {
                            num += tokens[i][j + 3];
                        }
                    }

                    answer += stoi(num);
                }

                // LEFT
                if (j - 1 >= 0 && isdigit(tokens[i][j - 1])) {
                    if (isdigit(tokens[i][j - 3]) && j - 3 >= 0) {    // 3 digits
                        num = tokens[i][j - 3];
                        num += tokens[i][j - 2];
                        num += tokens[i][j - 1];
                    } else if (isdigit(tokens[i][j - 2]) && j - 2 >= 0) {   // 2 digits
                        num = tokens[i][j - 2];
                        num += tokens[i][j - 1];
                    }

                    answer += stoi(num);
                }

                // ABOVE
                if (i - 1 >= 0 && isdigit(tokens[i - 1][j])) {
                    if (isdigit(tokens[i - 1][j - 1]) && j - 1 >= 0) {      // CHECK LEFT
                        if (isdigit(tokens[i - 1][j - 2]) && j - 2 >= 0) {
                            num = tokens[i - 1][j - 2];
                            num += tokens[i - 1][j - 1];
                            num += tokens[i - 1][j];
                        }
                        else if(isdigit(tokens[i - 1][j + 1]) && j + 1 < tokens[i].size()){
                                num = tokens[i - 1][j - 1];
                                num += tokens[i - 1][j];
                                num += tokens[i - 1][j + 1];
                        }
                        else {
                            num = tokens[i - 1][j - 1];
                            num += tokens[i - 1][j];
                        }
                    }
                    else {                               // CHECK RIGHT
                        num = tokens[i - 1][j];
                        if (isdigit(tokens[i - 1][j + 1])) {
                            num += tokens[i - 1][j + 1];
                            if (isdigit(tokens[i - 1][j + 2])) {
                                num += tokens[i - 1][j + 2];
                            }
                        }
                    }

                    answer += stoi(num);
                }

                // UNDER
                if (i + 1 < tokens.size() && isdigit(tokens[i + 1][j])) {
                    if (isdigit(tokens[i + 1][j - 1])) {      // CHECK LEFT
                        if (isdigit(tokens[i + 1][j - 2]) && j - 2 >= 0) {
                            num = tokens[i + 1][j - 2];
                            num += tokens[i + 1][j - 1];
                            num += tokens[i + 1][j];
                        }
                        else if(isdigit(tokens[i + 1][j + 1]) && j + 1 < tokens[i].size()){
                                num = tokens[i + 1][j - 1];
                                num += tokens[i + 1][j];
                                num += tokens[i + 1][j + 1];
                        }
                        else {
                            num = tokens[i + 1][j - 1];
                            num += tokens[i + 1][j];
                        }
                    }
                    else {                               // CHECK RIGHT
                        num = tokens[i + 1][j];
                        if (isdigit(tokens[i + 1][j + 1]) && j + 1 < tokens[i].size()) {
                            num += tokens[i + 1][j + 1];
                            if (isdigit(tokens[i + 1][j + 2]) && j + 2 < tokens[i].size()) {
                                num += tokens[i + 1][j + 2];
                            }
                        }
                    }

                    answer += stoi(num);
                }

                // ABOVE RIGHT
                if (i - 1 >= 0 && j + 1 < tokens[i - 1].size() && isdigit(tokens[i - 1][j + 1])) {
                    // ONLY TO THE RIGHT ALLOWED (if not, it's above)
                    if (!isdigit(tokens[i - 1][j])) {  // IF IT HAS DIGIT HERE THEN IT'S LITERALLY ABOVE THE SPECIAL CHARACTER

                        num = tokens[i - 1][j + 1];
                        if (isdigit(tokens[i - 1][j + 1 + 1]) && j + 1 + 1 < tokens[i - 1].size()) {
                            num += tokens[i - 1][j + 1 + 1];
                            if (isdigit(tokens[i - 1][j + 1 + 2]) && j + 1 + 1 < tokens[i - 1].size()) {
                                num += tokens[i - 1][j + 1 + 2];
                            }
                        }


                        answer += stoi(num);
                    }
                }

                // ABOVE LEFT
                if (i - 1 >= 0 && j - 1 >= 0 && isdigit(tokens[i - 1][j - 1])) {
                    // ONLY TO THE LEFT ALLOWED (if not, it's above)
                    if (!isdigit(tokens[i - 1][j])) {  // IF IT HAS DIGIT HERE THEN IT'S LITERALLY ABOVE THE SPECIAL CHARACTER
                        num = tokens[i-1][j-1];
                        if (j - 1 - 1 >= 0 && isdigit(tokens[i-1][j-1-1])) {
                            num = tokens[i - 1][j - 1 - 1];
                            num += tokens[i - 1][j - 1];
                        }
                        if (isdigit(tokens[i-1][j-1-1]) && isdigit(tokens[i - 1][j - 1 - 2]) && j - 1 - 2 >= 0) {
                            num = tokens[i - 1][j - 1 - 2];
                            num += tokens[i - 1][j - 1 - 1];
                            num += tokens[i - 1][j - 1];
                        }


                        answer += stoi(num);
                    }
                }

                // UNDER RIGHT
                if (i + 1 <= tokens.size() && j + 1 < tokens[i + 1].size() && isdigit(tokens[i + 1][j + 1])) {
                    // ONLY TO THE RIGHT ALLOWED (if not, it's above)
                    if (!isdigit(tokens[i + 1][j])) {  // IF IT HAS DIGIT HERE THEN IT'S LITERALLY ABOVE THE SPECIAL CHARACTER
                        num = tokens[i + 1][j + 1];
                        if (isdigit(tokens[i + 1][j + 1 + 1]) && j + 1 + 1 < tokens[i - 1].size()) {
                            num += tokens[i + 1][j + 1 + 1];
                            if (isdigit(tokens[i + 1][j + 1 + 2]) && j + 1 + 2 < tokens[i - 1].size()) {
                                num += tokens[i + 1][j + 1 + 2];
                            }
                        }


                        answer += stoi(num);
                    }
                }

                // UNDER LEFT
                if (i + 1 <= tokens.size() && j - 1 >= 0 && isdigit(tokens[i + 1][j - 1])) {
                    // ONLY TO THE LEFT ALLOWED (if not, it's above)
                    if (!isdigit(tokens[i + 1][j])) {  // IF IT HAS DIGIT HERE THEN IT'S LITERALLY ABOVE THE SPECIAL CHARACTER
                        num = tokens[i+1][j-1];
                        if (j - 1 - 1 >= 0 && isdigit(tokens[i+1][j-1-1])) {
                            num = tokens[i + 1][j - 1 - 1];
                            num += tokens[i + 1][j - 1];
                        }
                        if (isdigit(tokens[i+1][j-1-1]) && isdigit(tokens[i + 1][j - 1 - 2]) && j - 1 - 2 >= 0) {
                            num = tokens[i + 1][j - 1 - 2];
                            num += tokens[i + 1][j - 1 - 1];
                            num += tokens[i + 1][j - 1];
                        }


                        answer += stoi(num);
                    }
                }
            }
        }
    }

    cout << "ANSWER: " << answer;
}