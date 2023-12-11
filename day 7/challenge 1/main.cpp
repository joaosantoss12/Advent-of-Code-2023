#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <tuple>
#include <algorithm>

using namespace std;

enum types{
    none = 0,
    Five_of_Kind,
    Four_of_Kind,
    Full_House,
    Three_of_Kind,
    Two_Pair,
    One_Pair,
    High_Card
};

types checkType(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9, int v10, int v11, int v12, int v13){
    if(v1 == 5 || v2 == 5 || v3 == 5 || v4 == 5 || v5 == 5 || v6 == 5 || v7 == 5 || v8 == 5 || v9 == 5 || v10 == 5 || v11 == 5 || v12 == 5 || v13 == 5){
        return Five_of_Kind;
    }
    else if(v1 == 4 || v2 == 4 || v3 == 4 || v4 == 4 || v5 == 4 || v6 == 4 || v7 == 4 || v8 == 4 || v9 == 4 || v10 == 4 || v11 == 4 || v12 == 4 || v13 == 4){
        return Four_of_Kind;
    }
    else if(v1 == 3 || v2 == 3 || v3 == 3 || v4 == 3 || v5 == 3 || v6 == 3 || v7 == 3 || v8 == 3 || v9 == 3 || v10 == 3 || v11 == 3 || v12 == 3 || v13 == 3){
        if(v1 == 2 || v2 == 2 || v3 == 2 || v4 == 2 || v5 == 2 || v6 == 2 || v7 == 2 || v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Full_House;
        }
        else{
            return Three_of_Kind;
        }
    }

    // TWO PAIR (erh so many ifs)
    else if(v1 == 2){
        if(v2 == 2 || v3 == 2 || v4 == 2 || v5 == 2 || v6 == 2 || v7 == 2 || v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v2 == 2){
        if(v3 == 2 || v4 == 2 || v5 == 2 || v6 == 2 || v7 == 2 || v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v3 == 2){
        if(v4 == 2 || v5 == 2 || v6 == 2 || v7 == 2 || v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v4 == 2){
        if(v5 == 2 || v6 == 2 || v7 == 2 || v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v5 == 2){
        if(v6 == 2 || v7 == 2 || v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v6 == 2){
        if(v7 == 2 || v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v7 == 2){
        if(v8 == 2 || v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v8 == 2){
        if(v9 == 2 || v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v9 == 2){
        if(v10 == 2 || v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v10 == 2){
        if(v11 == 2 || v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v11 == 2){
        if(v12 == 2 || v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v12 == 2){
        if(v13 == 2){
            return Two_Pair;
        }
        else{
            return One_Pair;
        }
    }
    else if(v13 == 2)
        return One_Pair;


    else{
        return High_Card;
    }
}

bool setRank(const string& a, const string& b){
    string rankOrder = "AKQJT98765432";

    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            return rankOrder.find(a[i]) > rankOrder.find(b[i]);
        }
        else
            continue;
    }
}


int main() {
    int answer = 0;

    ifstream file("day 7/input.txt");

    string line;
    string currentHand;
    string currentBid;

    if (!file.is_open()) {
        cout << "Error opening the file!";
        return -1;
    }

    int nLine = -1;
    vector<tuple<string, string, types, int>> hands;

    int lastRank = 0;

    while (getline(file, line)) {
        istringstream iss(line);

        ++nLine;

        iss >> currentHand >> currentBid;
        hands.emplace_back(currentHand, currentBid, none, 1);

    }

    // NUMBER OF HANDS WITH TYPE:
    vector<string>nFive_of_Kind;
    vector<string>nFour_of_Kind;
    vector<string>nFull_House;
    vector<string>nThree_of_Kind;
    vector<string>nTwo_Pair;
    vector<string>nOne_Pair;
    vector<string>nHigh_Card;

    for(auto [hand, bid, handType, rank] : hands){
        int A = 0, K = 0, Q = 0, J = 0, T = 0, nine = 0, eight = 0, seven = 0, six = 0, five = 0, four = 0, three = 0, two = 0;

        for(int j = 0; j < hand.size(); j++){

            switch(hand[j]){
                case 'A' : ++A; break;
                case 'K' : ++K; break;
                case 'Q' : ++Q; break;
                case 'J' : ++J; break;
                case 'T' : ++T; break;
                case '9' : ++nine; break;
                case '8' : ++eight; break;
                case '7' : ++seven; break;
                case '6' : ++six; break;
                case '5' : ++five; break;
                case '4' : ++four; break;
                case '3' : ++three; break;
                case '2' : ++two; break;
            }
        }


        handType = checkType(A, K, Q, J, T, nine, eight, seven, six, five, four, three, two);

        switch(handType){
            case Five_of_Kind : nFive_of_Kind.push_back(hand); break;
            case Four_of_Kind : nFour_of_Kind.push_back(hand); break;
            case Full_House : nFull_House.push_back(hand); break;
            case Three_of_Kind : nThree_of_Kind.push_back(hand); break;
            case Two_Pair : nTwo_Pair.push_back(hand); break;
            case One_Pair : nOne_Pair.push_back(hand); break;
            case High_Card : nHigh_Card.push_back(hand); break;
        }
    }

    if(nFive_of_Kind.size() >= 2){
        sort(nFive_of_Kind.begin(), nFive_of_Kind.end(), setRank);
    }
    if(nFour_of_Kind.size() >= 2){
        sort(nFour_of_Kind.begin(), nFour_of_Kind.end(), setRank);
    }
    if(nFull_House.size() >= 2){
        sort(nFull_House.begin(), nFull_House.end(), setRank);
    }
    if(nThree_of_Kind.size() >= 2){
        sort(nThree_of_Kind.begin(), nThree_of_Kind.end(), setRank);
    }
    if(nTwo_Pair.size() >= 2){
        sort(nTwo_Pair.begin(), nTwo_Pair.end(), setRank);
    }
    if(nOne_Pair.size() >= 2){
        sort(nOne_Pair.begin(), nOne_Pair.end(), setRank);
    }
    if(nHigh_Card.size() >= 2){
        sort(nHigh_Card.begin(), nHigh_Card.end(), setRank);
    }

    vector<vector<string>> ranking;
    ranking.push_back(nHigh_Card); ranking.push_back(nOne_Pair); ranking.push_back(nTwo_Pair);
    ranking.push_back(nThree_of_Kind); ranking.push_back(nFull_House); ranking.push_back(nFour_of_Kind);
    ranking.push_back(nFive_of_Kind);


    for(int i=0; i<ranking.size(); i++){
        for(int j=0; j<ranking[i].size(); j++){
            for(auto [hand, bid, handType, rank] : hands) {
                if (hand == ranking[i][j]) {
                    rank = ++lastRank;

                    answer += (rank * stoi(bid));
                }
            }
        }
    }


    cout << "ANSWER: " << answer;
}