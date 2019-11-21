/**
 * Problem: https://www.hackerrank.com/challenges/climbing-the-leaderboard/problem
 *
 * */

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int getRank(const vector<int>& scores, const int start, const int end, const int aliceScore) {
    if (start == end) {
        return aliceScore < scores.at(start) ? start + 2 : start + 1;
    }
    const int mid = (start + end) / 2;
    if (aliceScore == scores.at(mid)) {
        return mid + 1;
    } else if (aliceScore > scores.at(mid)) {
        return getRank(scores, start, max(start, mid - 1), aliceScore);
    } else {
        return getRank(scores, min(end, mid + 1), end, aliceScore);
    }
}

vector<int> climbingLeaderboard(vector<int>& scores, const vector<int>& alice) {
    vector<int> result;
    auto new_end = unique(scores.begin(), scores.end());
    scores.resize(distance(scores.begin(), new_end));
    int aliceMax = INT_MIN;
    int lastRank = scores.size();
    for (auto score: alice) {
        if (score > aliceMax) {
            aliceMax = score;
            lastRank = getRank(scores, 0, scores.size() - 1, aliceMax);
        }
        result.push_back(lastRank);
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    std::ifstream in("/home/saiftyfirst/CLionProjects/Rythm++/HackerRank/input.txt");
    std::cin.rdbuf(in.rdbuf());

    int scores_count;
    cin >> scores_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string scores_temp_temp;
    getline(cin, scores_temp_temp);

    vector<string> scores_temp = split_string(scores_temp_temp);

    vector<int> scores(scores_count);

    for (int i = 0; i < scores_count; i++) {
        int scores_item = stoi(scores_temp[i]);

        scores[i] = scores_item;
    }

    int alice_count;
    cin >> alice_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string alice_temp_temp;
    getline(cin, alice_temp_temp);

    vector<string> alice_temp = split_string(alice_temp_temp);

    vector<int> alice(alice_count);

    for (int i = 0; i < alice_count; i++) {
        int alice_item = stoi(alice_temp[i]);

        alice[i] = alice_item;
    }

    vector<int> result = climbingLeaderboard(scores, alice);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
