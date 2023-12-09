#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

using namespace std;

class Node{

public:
    Node(string &x, string &y, string &z) : name(x), left(y), right(z) {}
    string name;
    string left;
    string right;
};

int main() {
    unsigned long long answer = 0;

    ifstream file("../../input.txt");

    string line;
    string nextToken;
    int nLine = -1;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    vector<char> instructions;
    vector<Node> nodes_list;

    string node_name, first, second;

    while (getline(file, line)) {
        ++nLine;
        istringstream iss(line);

        if(nLine == 0) {
            for (int i = 0; i < line.size(); i++) {
                instructions.push_back(line[i]);
            }
        }
        else{
            if(iss >> node_name) {
                iss >> first >> first;
                first.erase(0, 1);
                if (!first.empty()) {
                    first.erase(first.size() - 1, 1);
                }
                iss >> second;
                if (!second.empty()) {
                    second.erase(second.size() - 1, 1);
                }

                nodes_list.emplace_back(node_name,first,second);
            }
        }
    }

    vector<string> currentNodes_name;
    vector<unsigned long long> answers_list;
    int index = 0;
    int index2 = 0;

    for(int i = 0; i < nodes_list.size(); i++){
        if(nodes_list[i].name[2] == 'A'){           // STARTING POINT - ENDS WITH 'A'
            currentNodes_name.push_back(nodes_list[i].name);
        }
    }

    for(int i = 0; i < currentNodes_name.size(); i++) {
        while (currentNodes_name[i][2] != 'Z') {

            while (currentNodes_name[i] != nodes_list[index % nodes_list.size()].name) {
                ++index;
            }


            if (instructions[index2 % instructions.size()] == 'R')
                currentNodes_name[i] = nodes_list[index % nodes_list.size()].right;
            else
                currentNodes_name[i] = nodes_list[index % nodes_list.size()].left;

            ++index2;
            ++answer;
        }

        index = 0;
        index2 = 0;
        answers_list.push_back(answer);
        answer = 0;
    }

    answer = answers_list[0];
    for(int i = 1; i < answers_list.size(); i++){
        answer = std::lcm(answer, answers_list[i]);
    }

    cout << "ANSWER: " << answer;
}