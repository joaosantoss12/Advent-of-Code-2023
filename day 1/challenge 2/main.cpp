#include <iostream>
#include <fstream>
#include <string>

#define MAX_DIGITS 100

using namespace std;

// zero, one, two, three, four, five, six, seven, eight, nine
// zero
// one
// two, three
// four, five
// six, seven
// eight
// nine

int main() {
    int answer = 0;
    ifstream file;
    file.open("day 1/input.txt");

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
                else{
                    switch(line[i]){
                        case 'z' : {
                            if(line[i+1] == 'e' && line[i+2] == 'r' && line[i+3] == 'o'){
                                digits[++index] = "0";
                            }
                        }
                        case 'o' : {
                            if(line[i+1] == 'n' && line[i+2] == 'e'){
                                digits[++index] = "1";
                            }
                        }
                        case 't' : {
                            if(line[i+1] == 'w' && line[i+2] == 'o')
                                digits[++index] = "2";
                            else if(line[i+1] == 'h' && line[i+2] == 'r' && line[i+3] == 'e' && line[i+4] == 'e')
                                digits[++index] = "3";
                        }
                        case 'f' : {
                            if(line[i+1] == 'o' && line[i+2] == 'u' && line[i+3] == 'r')
                                digits[++index] = "4";
                            else if(line[i+1] == 'i' && line[i+2] == 'v' && line[i+3] == 'e')
                                digits[++index] = "5";
                        }
                        case 's' : {
                            if(line[i+1] == 'i' && line[i+2] == 'x')
                                digits[++index] = "6";
                            else if(line[i+1] == 'e' && line[i+2] == 'v' && line[i+3] == 'e' && line[i+4] == 'n')
                                digits[++index] = "7";
                        }
                        case 'e' : {
                            if(line[i+1] == 'i' && line[i+2] == 'g' && line[i+3] == 'h' && line[i+4] == 't')
                                digits[++index] = "8";
                        }
                        case 'n' : {
                            if(line[i+1] == 'i' && line[i+2] == 'n' && line[i+3] == 'e')
                                digits[++index] = "9";
                        }
                    }
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