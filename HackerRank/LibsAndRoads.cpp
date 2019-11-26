#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int customDfs(vector<vector<int>>& links, vector<bool>& visited, int start) {
    int count = 1;
    visited[start] = true;
    for (int i = 0; i < links[start].size(); i++) {
        if (!visited[links[start][i]]) {
            count += customDfs(links, visited, links[start][i]);
        }
    }
    return count;
}

long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> links) {
    vector<bool> visited(n, false);
    long cost = 0;
    int count;
    for (int i = 0; i < links.size(); i++) {
        if (!visited[i]) {
            cost += c_lib;
            count = customDfs(links, visited, i);
            if (c_lib > c_road) cost += c_road * (count - 1);
            else  cost += c_lib * (count - 1);
        }
    }
    return cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> links(n);
        int start;
        int end;
        for (int i = 0; i < m; i++) {

            cin >> start;
            cin >> end;

            links[start - 1].push_back(end - 1);
            links[end - 1].push_back(start - 1);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, links);

        cout << result << "\n";
    }

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
