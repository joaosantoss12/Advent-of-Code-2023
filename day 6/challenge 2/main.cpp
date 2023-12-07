#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

int main() {
    int answer = 1;

    ifstream file("../../input.txt");

    string line;
    string nextToken;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    int nLine = -1;

    string race_timer;
    string distance_record;

    unsigned long long distance_by_boat;
    int records = 0;

    while (getline(file, line)) {
        istringstream iss(line);

        ++nLine;

        while (iss >> nextToken) {
            if(isdigit(nextToken[0]) && nLine == 0){
                race_timer += nextToken;
            }
            else if(isdigit(nextToken[0]) && nLine == 1){
                distance_record += nextToken;
            }
        }
    }

    unsigned long long race_timer_value = stoull(race_timer);
    unsigned long long distance_record_value = stoull(distance_record);

    for (unsigned long long hold_time = 0; hold_time <= race_timer_value; hold_time++) {
        distance_by_boat = hold_time * (race_timer_value - hold_time);

        if (distance_by_boat > distance_record_value)
            ++records;
    }

    answer *= records;

    cout << "ANSWER: " << answer;
}
