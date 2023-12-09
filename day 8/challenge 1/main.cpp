#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Node{

public:
    Node(string &x, string &y, string &z) : name(x), left(y), right(z) {}
    string name;
    string left;
    string right;
};

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

    string currentNode_name = "AAA";
    int index = 0;
    int index2 = 0;

    while(currentNode_name != "ZZZ"){
        while(currentNode_name != nodes_list[index % nodes_list.size()].name) {
            ++index;
        }


        if(instructions[index2 % instructions.size()] == 'R')
            currentNode_name = nodes_list[index % nodes_list.size()].right;
        else
            currentNode_name = nodes_list[index % nodes_list.size()].left;

        ++index2;
        ++answer;
    }


    cout << "ANSWER: " << answer;
}