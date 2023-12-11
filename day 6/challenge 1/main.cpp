#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    int answer = 1;

    ifstream file("day 6/input.txt");

    string line;
    string nextToken;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    int nLine = -1;

    vector<string> race_timers;
    vector<string> distances_record;

    int distance_by_boat;
    int records;

    while (getline(file, line)) {
        istringstream iss(line);

        ++nLine;

        while (iss >> nextToken) {
            if(isdigit(nextToken[0]) && nLine == 0){
                race_timers.push_back(nextToken);
            }
            else if(isdigit(nextToken[0]) && nLine == 1){
                distances_record.push_back(nextToken);
            }
        }
    }

    if(race_timers.size() != distances_record.size()){
        cerr << "ERROR! THERE SHOULD BE THE SAME AMOUT OF TIMERS AND DISTANCES RECORDS IN THE DOCUMENT!" << endl;
        return -1;
    }

    for(int i = 0; i < race_timers.size(); i++){
        records = 0;

        for(int hold_time = 0; hold_time <= stoi(race_timers[i]); hold_time++){
            distance_by_boat = hold_time * (stoi(race_timers[i]) - hold_time);

            if(distance_by_boat > stoi(distances_record[i]))
                ++records;

        }
        answer *= records;
    }

    cout << "ANSWER: " << answer;
}
