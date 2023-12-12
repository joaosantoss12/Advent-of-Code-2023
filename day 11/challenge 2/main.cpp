#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    long long answer = 0;

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

    vector<int> empty_rows;
    vector<int> empty_columns;

    while (getline(file, line)) {
        ++nLine;

        bool isEmpty = true;

        for(int j = 0; j < line.size(); j++){
            if(line[j] == '#') {
                isEmpty = false;
                break;
            }
        }

        if(isEmpty)
            empty_rows.push_back(nLine);

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
        if(isEmpty)
            empty_columns.push_back(j);
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
            long long distance = (abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second));

            for(int k = 0; k < empty_rows.size(); k++){
                if((galaxies[i].first < empty_rows[k] && empty_rows[k] < galaxies[j].first ||
                    galaxies[i].first > empty_rows[k] && empty_rows[k] > galaxies[j].first)){
                    distance += 999999;
                }
            }
            for(int k = 0; k < empty_columns.size(); k++){
                if((galaxies[i].second < empty_columns[k] && empty_columns[k] < galaxies[j].second ||
                    galaxies[i].second > empty_columns[k] && empty_columns[k] > galaxies[j].second)){
                    distance += 999999;
                }
            }

            answer += distance;
        }
    }

    cout << "ANSWER: " << answer;
}