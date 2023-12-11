#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class Point{
    public:
    char type;
    int j;
    int i;
    Point(){}
};

// |  north/south
// -  east/west
// L  north/east
// J  north/west
// 7  south/west
// F  south/east
// .  ground, no pipes lead to it
// S  starting position of animal

int main() {
    int answer = 0;

    ifstream file("../../input.txt");

    string line;
    string nextToken;
    int nLine = -1;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    vector<vector<string>> characters;


    while (getline(file, line)) {
        ++nLine;

        characters.emplace_back();

        characters[nLine].push_back(line);
    }

    Point S;
    Point currentPoint;
    Point lastPoint;
    vector<Point> loopPoints;

    for (int i = 0; i < characters.size(); i++) {
        for (int j = 0; j < characters[i][0].size(); j++) {
            if (characters[i][0][j] == 'S') {
                // STARTING POINT
                S.i = i;
                S.j = j;
                S.type = 'S';

                loopPoints.push_back(S);
                currentPoint = S;
                lastPoint = S;
            }
        }
    }

    // FIND NEXT POINT AFTER 'S'
    if (currentPoint.j + 1 <= characters[currentPoint.i][0].size() - 1 && characters[currentPoint.i][0][currentPoint.j + 1] == '-') { // RIGHT
        currentPoint.j += 1;
        currentPoint.type = '-';
        loopPoints.push_back(currentPoint);
    }
    else if (currentPoint.j - 1 >= 0 && characters[currentPoint.i][0][currentPoint.j - 1] == '-') {
        currentPoint.j -= 1;
        currentPoint.type = '-';
        loopPoints.push_back(currentPoint);
    }
    else if(currentPoint.i - 1 >= 0 && characters[currentPoint.i - 1][0][currentPoint.j] == '|'){
        currentPoint.i -= 1;
        currentPoint.type = '|';
        loopPoints.push_back(currentPoint);
    }
    else if(currentPoint.i + 1 <= characters.size()-1 && characters[currentPoint.i + 1][0][currentPoint.j] == '|'){
        currentPoint.i += 1;
        currentPoint.type = '|';
        loopPoints.push_back(currentPoint);
    }
    else if (currentPoint.i + 1 <= characters.size() - 1 && characters[currentPoint.i + 1][0][currentPoint.j] == 'L') { // UNDER
        currentPoint.i += 1;
        currentPoint.type = 'L';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }
    else if (currentPoint.j - 1 >= 0 && characters[currentPoint.i][0][currentPoint.j - 1] == 'L') {
        currentPoint.j -= 1;
        currentPoint.type = 'L';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }
    else if (currentPoint.i + 1 <= characters.size() - 1 && characters[currentPoint.i + 1][0][currentPoint.j] == 'J') { // UNDER
        currentPoint.i += 1;
        currentPoint.type = 'J';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }
    else if (currentPoint.j + 1 <= characters[currentPoint.i][0].size() - 1 && characters[currentPoint.i][0][currentPoint.j + 1] == 'J') {
        currentPoint.j += 1;
        currentPoint.type = 'J';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }
    else if (currentPoint.i - 1 >= 0 && characters[currentPoint.i - 1][0][currentPoint.j] == '7') { // ABOVE
        currentPoint.i -= 1;
        currentPoint.type = '7';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }
    else if (currentPoint.j + 1 <= characters[currentPoint.i][0].size() - 1 && characters[currentPoint.i][0][currentPoint.j + 1] == '7') {
        currentPoint.j += 1;
        currentPoint.type = '7';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }
    else if (currentPoint.i - 1 >= 0 && characters[currentPoint.i - 1][0][currentPoint.j] == 'F') { // ABOVE
        currentPoint.i -= 1;
        currentPoint.type = 'F';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }
    else if (currentPoint.j - 1 >= 0 && characters[currentPoint.i][0][currentPoint.j - 1] == 'F') {
        currentPoint.j -= 1;
        currentPoint.type = 'F';
        loopPoints.push_back(currentPoint);
        vertices.emplace_back(currentPoint.i, currentPoint.j);
    }


    bool stop = false;
    while(!stop){
        switch (currentPoint.type) {
            case 'S': {
                stop = true;
                break;
            }
            case '-': {
                if (currentPoint.j - 1 >= 0 && lastPoint.j == currentPoint.j + 1 && currentPoint.j + 1 <= characters[currentPoint.i][0].size() - 1) { // went from right to left to the current point
                    lastPoint = currentPoint;
                    currentPoint.j -= 1;
                }
                else if (currentPoint.j + 1 <= characters[currentPoint.i][0].size() - 1 && lastPoint.j == currentPoint.j - 1) { // went from left to right to the current point
                    lastPoint = currentPoint;
                    currentPoint.j += 1;
                }
                currentPoint.type = characters[currentPoint.i][0][currentPoint.j];
                loopPoints.push_back(currentPoint);
                break;
            }
            case '|': {
                if (currentPoint.i - 1 >= 0 && lastPoint.i == currentPoint.i + 1 && currentPoint.i + 1 <= characters.size() - 1) { // went from under to above to the current point
                    lastPoint = currentPoint;
                    currentPoint.i -= 1;
                }
                else if (currentPoint.i + 1 <= characters.size() - 1 && lastPoint.i == currentPoint.i - 1) { // went from above to under to the current point
                    lastPoint = currentPoint;
                    currentPoint.i += 1;
                }
                currentPoint.type = characters[currentPoint.i][0][currentPoint.j];
                loopPoints.push_back(currentPoint);
                break;
            }
            case 'L': {
                if (currentPoint.i + 1 <= characters.size() - 1 && lastPoint.i == currentPoint.i - 1) { // went from under to above to the current point
                    lastPoint = currentPoint;
                    currentPoint.j += 1;
                }
                else if (currentPoint.j + 1 <= characters[currentPoint.i][0].size() - 1 && lastPoint.j == currentPoint.j + 1) { // went from left to right to the current point, so next is above
                    lastPoint = currentPoint;
                    currentPoint.i -= 1;
                }
                currentPoint.type = characters[currentPoint.i][0][currentPoint.j];
                loopPoints.push_back(currentPoint);
                break;
            }
            case 'J': {
                if (currentPoint.i - 1 <= characters.size() - 1 && lastPoint.i == currentPoint.i - 1) { // went from under to above to the current point
                    lastPoint = currentPoint;
                    currentPoint.j -= 1;
                }
                else if (currentPoint.j - 1 >= 0 && lastPoint.j == currentPoint.j - 1) { // went from right to left to the current point, so next is above
                    lastPoint = currentPoint;
                    currentPoint.i -= 1;
                }
                currentPoint.type = characters[currentPoint.i][0][currentPoint.j];
                loopPoints.push_back(currentPoint);
                break;
            }
            case '7': {
                if (currentPoint.i - 1 >= 0 && lastPoint.i == currentPoint.i + 1) { // went from above to under to the current point
                    lastPoint = currentPoint;
                    currentPoint.j -= 1;
                }
                else if (currentPoint.j - 1 >= 0 && lastPoint.j == currentPoint.j - 1) { // went from right to left to the current point, so next is under
                    lastPoint = currentPoint;
                    currentPoint.i += 1;
                }
                currentPoint.type = characters[currentPoint.i][0][currentPoint.j];
                loopPoints.push_back(currentPoint);
                break;
            }
            case 'F': {
                if (currentPoint.i + 1 >= 0 && lastPoint.i == currentPoint.i + 1) { // went from above to under to the current point
                    lastPoint = currentPoint;
                    currentPoint.j += 1;
                }
                else if (currentPoint.j + 1 <= characters[currentPoint.i][0].size() - 1 && lastPoint.j == currentPoint.j + 1) { // went from left to right to the current point, so next is under
                    lastPoint = currentPoint;
                    currentPoint.i += 1;
                }
                currentPoint.type = characters[currentPoint.i][0][currentPoint.j];
                loopPoints.push_back(currentPoint);
                break;
            }
            case '.': {
                break;
            }
        }

    }

    answer = loopPoints.size() / 2;

    cout << "ANSWER: " << answer;
}