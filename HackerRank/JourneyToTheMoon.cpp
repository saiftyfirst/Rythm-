/**
 * Problem: https://www.hackerrank.com/challenges/journey-to-the-moon/problem
 *
 * */

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long customDfs(vector<bool>& visited, vector<vector<int>>& astronaut, int start) {
    long count = 1;
    for (int i = 0; i < astronaut[start].size(); i++) {
        if (!visited[astronaut[start][i]]) {
            visited[astronaut[start][i]] = true;
            count += customDfs(visited, astronaut, astronaut[start][i]);
        }
    }
    return count;
}

long journeyToMoon(long n, vector<vector<int>> astronaut) {
    vector<bool> visited(n, false);
    long combinations = 0;
    long sum = 0;
    long res;
    for (int i = 0; i < astronaut.size(); i++) {
        if (!visited[i]) {
            visited[i] = true;
            res = customDfs(visited, astronaut, i);
            combinations += res * sum;
            sum += res;
        }
    }
    return combinations;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string np_temp;
    getline(cin, np_temp);

    vector<string> np = split_string(np_temp);

    int n = stoi(np[0]);

    int p = stoi(np[1]);

    vector<vector<int>> astronaut(n);
    int astros[2];
    for (int i = 0; i < p; i++) {
        cin >> astros[0];
        cin >> astros[1];
        astronaut[astros[0]].push_back(astros[1]);
        astronaut[astros[1]].push_back(astros[0]);

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = journeyToMoon(n, astronaut);

    fout << result << "\n";

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
