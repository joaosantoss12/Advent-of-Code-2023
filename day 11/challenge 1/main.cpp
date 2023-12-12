#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    int answer = 0;

    ifstream file("day 11/input.txt");

    string line;
    string nextToken;
    int nLine = -1;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    vector<string>map;
    vector<pair<int,int>> galaxies;

    while (getline(file, line)) {
        ++nLine;

        bool isEmpty = true;

        for(int j = 0; j < line.size(); j++){
            if(line[j] == '#') {
                isEmpty = false;
                break;
            }
        }

        if(isEmpty){
            map.push_back(line);
            map.push_back(line);
        }
        else
            map.push_back(line);
    }

    for(int j = 0; j < map[0].size(); j++) {        // EVERY LINE HAS THE SAME NUMBER OF CHARACTERS
        string column;
        bool isEmpty = true;
        for (int i = 0; i < map.size(); i++) {
            column.push_back(map[i][j]);
            if(map[i][j] == '#')
                isEmpty = false;
        }
        if(isEmpty){
            for(int i = 0; i < map.size(); i++) {
                map[i].insert(j + 1, ".");
            }
            j += 1;
        }
    }

    // POPULATE galaxies
    for(int i = 0; i < map.size(); i++){
        for(int j = 0; j < map[i].size(); j++){
            if(map[i][j] == '#')
                galaxies.emplace_back(i,j);
        }
    }

    for(int i = 0; i < galaxies.size(); i++){
        for(int j = i+1; j < galaxies.size(); j++){
            int distance = (abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second));
            answer += distance;
        }
    }

    cout << "ANSWER: " << answer;
}