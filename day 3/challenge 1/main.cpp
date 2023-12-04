#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> lines;
vector<int> nums;

int construct_num(int i, int j);

int determine_nums(int i, int j) {
    if ((i >= 0 && i < lines.size()) && (j >= 0 && j < lines.at(i).length()) &&
        isdigit(lines.at(i).at(j))) {
        return construct_num(i, j);
    }
    return -1;
}

int construct_num(int i, int j) {
    string current_line = lines.at(i);
    string num;
    int start, end;
    int x = j;
    for (; x >= 0; --x) {
        if (x == -1 || !isdigit(current_line.at(x))) {
            break;
        }
    }
    start = x + 1;

    x = j;
    for (; x <= current_line.length(); ++x) {
        if (x >= current_line.length() || !isdigit(current_line.at(x))) {
            break;
        }
    }
    end = x - 1;

    for (int x = start; x < end + 1; ++x) {
        num.push_back(current_line.at(x));
    }
    nums.push_back(stoi(num));

    string new_line = current_line;
    for (int x = start; x <= end; ++x)
        new_line.at(x) = '.';
    lines.at(i) = new_line;
    return stoi(num);
}

int main() {
    ifstream file("input.txt");
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); ++i) {
        line = lines.at(i);

        for (int j = 0; j < line.length(); ++j) {
            char current_char = line.at(j);
            for (int x = -1; x < 2; ++x) {
                for (int y = -1; y < 2; ++y) {
                    if (current_char != '.' && !isdigit(current_char)) {
                        determine_nums(i + x, j + y);
                    }
                }
            }
        }
    }

    int sum = 0;
    for (int num: nums)
        sum += num;
    cout << sum << '\n';


    return 0;
}
