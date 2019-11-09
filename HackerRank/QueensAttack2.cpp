/**
 "Queen's Attack II" problem on HackerRank: www.hackerrank.com/challenges/queens-attack-2/

    The algorithm:

    1. I sum all the possible moves for the queen from it's position given its position.
        - (r_q -1) -> Possible moves to the left of board
        - (n - r_q) -> Possible moves to the right of board
        - (c_q -1) -> Possible moves towards the bottom
        - (n - c_q) -> Possible moves towards the top
        - min((r_q - 1), (c_q - 1)) -> Possible moves towards bottom-left
        - min((n - r_q), (c_q - 1)) -> Possible moves towards top-left
        - min((n - r_q), (n - c_q)) -> Possible moves towards top-right
        - min((r_q - 1), (n - c_q)) -> Possible moves towards bottom-right

    2. Next, I loop through the positions of the obstacles and store the deductions on the possible moves due to an obstacle.
       Since it is possible that there are more than one obstacle along the same line, I only store maximum deductions.
       I have commented on the code so hope it is reasonably clear.

    3. Finally, I deduct the deductions from the total possible moves.

 * */


#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long int max(long int a, long int b) {
    return a > b ? a : b;
}

long int min(long int a, long int b) {
    return a < b ? a : b;
}

// Complete the queensAttack function below.
long int queensAttack(long int n, long int k, long int r_q, long int c_q, vector<vector<long int>> obstacles) {

    long int degree = (r_q - 1) + (n - r_q) + (c_q - 1) + (n - c_q) +
                      min((r_q - 1), (c_q - 1)) + min((n - r_q), (c_q - 1)) +
                      min((n - r_q), (n - c_q)) + min((r_q - 1), (n - c_q));

    long int left_deduct = 0;
    long int right_deduct = 0;
    long int bottom_deduct = 0;
    long int top_deduct = 0;
    long int bottom_left_deduct = 0;
    long int top_left_deduct = 0;
    long int top_right_deduct = 0;
    long int bottom_right_deduct = 0;

    for (auto obstacle: obstacles) {

        long int r_diff = r_q - obstacle[0];
        long int c_diff = c_q - obstacle[1];

        if (c_diff == 0) { // obstacle in same column as queen

            if (r_diff > 0) { // obstacle below queen
                bottom_deduct = max(bottom_deduct, obstacle[0]);
            } else if (r_diff < 0) { // obstacle above queen
                top_deduct = max(top_deduct, (n - obstacle[0] + 1));
            }

        } else if (r_diff == 0) { // obstacle in same row as queen

            if (c_diff > 0) { // obstacle to the left of queen
                left_deduct = max(left_deduct, obstacle[1]);
            } else if (c_diff < 0) { //obstacle to the right of queen
                right_deduct = max(right_deduct, (n - obstacle[1] + 1));
            }

        } else if (abs(r_diff) == abs(c_diff)) { // obstacle along a diagonal

            if (r_diff * c_diff > 0) { // obstacle along bottom-left to top-right diag

                if (r_diff < 0) { // top-right
                    top_right_deduct = max(top_right_deduct, min(n - obstacle[0] + 1, n - obstacle[1] + 1));
                } else { // bottom-left
                    bottom_left_deduct = max(bottom_left_deduct, min(obstacle[0], obstacle[1]));
                }

            } else { // obstacle along top-left to bottom-right diag

                if (r_diff < 0) { // top-left
                    top_left_deduct = max(top_left_deduct, min(n - obstacle[0] + 1, obstacle[1]));;
                } else { // bottom-rigth
                    bottom_right_deduct = max(bottom_right_deduct, min(obstacle[0], n - obstacle[1] + 1));
                }

            }
        }
    }

    degree -= (left_deduct + right_deduct +
               bottom_deduct + top_deduct +
               bottom_left_deduct + top_left_deduct +
               top_right_deduct + bottom_right_deduct);

    return degree;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    long int n = stoi(nk[0]);

    long int k = stoi(nk[1]);

    string r_qC_q_temp;
    getline(cin, r_qC_q_temp);

    vector<string> r_qC_q = split_string(r_qC_q_temp);

    long int r_q = stoi(r_qC_q[0]);

    long int c_q = stoi(r_qC_q[1]);

    vector<vector<long int>> obstacles(k);
    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        for (int j = 0; j < 2; j++) {
            cin >> obstacles[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long int result = queensAttack(n, k, r_q, c_q, obstacles);

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
