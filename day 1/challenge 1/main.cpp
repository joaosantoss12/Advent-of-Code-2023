#include <iostream>
#include <fstream>
#include <string>

#define MAX_DIGITS 100

using namespace std;

int main() {
    int answer = 0;
    ifstream file;
    file.open("../../input.txt");

    string line;
    string digits[MAX_DIGITS];
    int index = -1;

    if(!file.is_open()){
        cout << "Error opening the file!";
        return -1;
    }

    if(file.is_open()) {
        while (!file.eof()) {
            index = -1;
            getline(file, line);

            for (int i = 0; i < line.length(); i++) {
                if (isdigit(line[i])) {
                    digits[++index] = line[i];

                }
            }

            string x;

            if (index >= 1)
                x = digits[0] + digits[index];
            else if (index == 0)
                x = digits[0] + digits[0];
            else
                x = "0";

            answer += stoi(x);

        }
    }

    cout << "ANSWER: " + to_string(answer);

    return 0;
}
