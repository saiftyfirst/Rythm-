/**

    Problem Description: https://www.hackerrank.com/challenges/synchronous-shopping

    * Not entirely an original solution
    * Potentially helpful though process:
    *   - Variation of Dijkstra's algorithm
    *   - Bismasking used to save
    *   - Consider each <node, fish> combination as a seperate node for Dijkstra's algorithm, i.e. for example, <Node 2, Fish 1> is treated as a separate node from <Node 2, Fish 1 & Fish 3>
    *   - This ensures that the algorithm moves back to already visited node after collecting more fish
    *   - After traversal, the destination vector of distance struct contains distances from src to dest for all combinations of fish that can be collected
*/

#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

void pushForVisit(unsigned int dest, unsigned int fishMask, unsigned int dist, set<pair<unsigned int, pair<unsigned int, unsigned int>>>& toVisit, vector<vector<unsigned int>>& distances) {
    if (distances[dest][fishMask] < dist) return;
    pair<unsigned  int, pair<unsigned int, unsigned int>> visitPair = make_pair(distances[dest][fishMask], make_pair(dest, fishMask));
    if (toVisit.find(visitPair) != toVisit.end()) toVisit.erase(toVisit.find(visitPair));
    distances[dest][fishMask] = dist;
    visitPair.first = dist;
    toVisit.insert(visitPair);
}

unsigned int shop(int n, int k, const vector<unsigned int>& maskedCenters, const vector<vector<pair<int, unsigned int>>>& adjVector) {
    vector<vector<unsigned int>> distances(n, vector<unsigned int>(1 << k, UINT_MAX));

    set<pair<unsigned int, pair<unsigned int, unsigned int>>> toVisit;
    pushForVisit(0, maskedCenters[0], 0, toVisit, distances);

    unsigned int src, srcFish, destFish;
    while (!toVisit.empty()) {
        src = toVisit.begin() -> second.first;
        srcFish = toVisit.begin() -> second.second;
        toVisit.erase(toVisit.begin());
        for (auto link: adjVector[src]) {
            destFish = maskedCenters[link.first];
            pushForVisit(link.first, destFish | srcFish, link.second + distances[src][srcFish], toVisit, distances);
        }
    }

    int maskedSum = (1 << k) - 1;
    unsigned int minDistance = UINT_MAX;
    for (size_t i = 0; i < distances[n - 1].size(); ++i) {
        for (size_t j = 0; j < distances[n - 1].size(); ++j) {
            if (((i | j) == maskedSum)) {
                minDistance = min(minDistance, max(distances[n - 1][i], distances[n - 1][j]));
            }
        }
    }
    return minDistance;
}

int main()
{

    ofstream fout(getenv("OUTPUT_PATH"));

    int n, m, k;
    cin >> n >> m >> k;

    vector<unsigned int> maskedCenters(n, 0);
    for (int i = 0; i < n; ++i) {
        int fCount, fID;
        cin >> fCount;
        for (int j = 0; j < fCount; ++j) {
            cin >> fID;
            maskedCenters[i] |= (1 << (fID - 1));
        }
    }

    vector<vector<pair<int, unsigned int>>> adjVector(n);
    int start, end, weight;
    for (int i = 0; i < m; ++i) {
        cin >> start >> end >> weight;
        adjVector[start - 1].push_back(make_pair(end - 1, weight));
        adjVector[end - 1].push_back(make_pair(start - 1, weight));

    }

    unsigned int res = shop(n, k, maskedCenters, adjVector);

    fout << res << "\n";

    fout.close();

    return 0;
}
