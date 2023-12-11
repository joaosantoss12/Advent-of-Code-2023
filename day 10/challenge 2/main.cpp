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

// PART 2
// L,J,7,F are vertices -> Shoelace formula

int main() {
    int answer = 0;

    ifstream file("day 10/input.txt");

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
    vector<pair<int,int>> vertices;

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

                vertices.emplace_back(S.i, S.j);
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
                vertices.emplace_back(currentPoint.i, currentPoint.j);
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
                vertices.emplace_back(currentPoint.i, currentPoint.j);
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
                vertices.emplace_back(currentPoint.i, currentPoint.j);
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
                vertices.emplace_back(currentPoint.i, currentPoint.j);
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

    // shoelace formula
    int area = 0;
    int perimetro = 0;
    for(int i = 0; i < vertices.size(); i++){
        if(i == vertices.size()-1) {
            area += (vertices[i].first * vertices[0].second) - (vertices[i].second * vertices[0].first);
            perimetro += abs(vertices[i].first - vertices[0].first) + abs(vertices[i].second - vertices[0].second);
        }
        else {
            area += (vertices[i].first * vertices[i + 1].second) - (vertices[i].second * vertices[i + 1].first);
            perimetro += abs(vertices[i].first - vertices[i + 1].first) + abs(vertices[i].second - vertices[i + 1].second);
        }
    }

    area = abs(area)/2;

    // formula for this puzzle
    answer = area - ((perimetro/2) - 1);

    cout << "ANSWER: " << answer;
}