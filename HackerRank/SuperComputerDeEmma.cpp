/**
 * Problem: https://www.hackerrank.com/challenges/two-pluses/
 *
 * */

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class Plus {
public:
    int x; int y; int s;

    Plus() : x(-1), y(-1), s(-1) {}
    Plus(int _x, int _y, int _s): x(_x), y(_y), s(_s) {};

    bool _centerOverlap(const Plus& plus) {
        return plus.x == x && plus.y == y;
    }

    bool _rowOverlap(const Plus& plus) {
        return plus.x == x && ((plus.y > y && plus.y - plus.s <= y + s) || (plus.y < y && y - s <= plus.y + plus.s));
    }

    bool _colOverlap(const Plus& plus) {
        return plus.y == y && ((plus.x > x && plus.x - plus.s <= x + s) || (plus.x < x && x - s <= plus.x + plus.s));
    }

    bool _rightOverlap(const Plus& plus) {
        if (plus.x > x) {
            if (plus.y > y) { // to the bottom-right
                return (y + s >= plus.y && plus.x - plus.s <= x) || (x + s >= plus.x && plus.y - plus.s <= y);
            } else { // to the top-right
                return ((y - s <= plus.y && plus.x - plus.s <= x)|| (x + s >= plus.x && plus.y + plus.s >= y));
            }
        }
        return false;
    }

    bool _leftOverlap(const Plus& plus) {
        if (plus.x < x) {
            if (y > plus.y) { // to the top-left
                return (plus.y + plus.s >= y && x - s <= plus.x) || (plus.x + plus.s >= x && y - s <= plus.y);
            } else { // to the bottom-left
                return (plus.y - plus.s <= y && x - s <= plus.x) || (plus.x + plus.s >= x && y + s >= plus.y);
            }
        }
        return false;
    }

    bool overlaps(const Plus& plus) {
        bool ret = _centerOverlap(plus);
        if (!ret) ret = _rowOverlap(plus);
        if (!ret) ret = _colOverlap(plus);
        if (!ret) ret = _rightOverlap(plus);
        if (!ret) ret = _leftOverlap(plus);
        return ret;
    }

};

bool checkExistence(vector<string>& grid, int x, int y, int size) {
    if (size == 0) return true;
    if (x + size >= grid[0].length() || x - size < 0
        || y + size >= grid.size() || y - size < 0) return false;
    bool upExists = true;
    bool downExists = true;
    for (int i = 1; i <= size; i++) {
        upExists = upExists && grid[y-i][x] == 'G';
        downExists = downExists && grid[y+i][x] == 'G';
    }
    return upExists && downExists;
}

// Complete the twoPluses function below.
int twoPluses(vector<string> grid) {
    vector<Plus*> plusVector;

    int counter;
    bool exists;
    for (int i = 0; i < grid.size(); i++) {
        counter = 0;
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 'G') {
                counter++;
                if (counter > 0) {
                    plusVector.push_back(new Plus(j, i, 0));
                    for (int k = counter/2 + 1; k < counter; k++) {
                        exists = checkExistence(grid, j - (counter - k), i, counter - k);
                        if (exists) {
                            plusVector.push_back(new Plus(j - (counter - k), i, counter - k));
                        }
                    }
                }
            } else {
                counter = 0;
            }
        }
    }

    int res = 1;
    for (int i = 0; i < plusVector.size(); i++) {
        for (int j = i + 1; j < plusVector.size(); ++j) {
            if (!plusVector.at(i)->overlaps(*plusVector.at(j))) {
                res = max(res, (plusVector.at(i)->s * 4 + 1) * (plusVector.at(j)->s * 4 + 1));
            }
        }
    }

    for (auto ptr: plusVector) {
        delete ptr;
    }
    plusVector.clear();

    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

//    std::ifstream in("in.txt");
//    std::cin.rdbuf(in.rdbuf());

    string nm_temp;

    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);
    cout << result << "\n";

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
