/**

    Problem Description: https://www.hackerrank.com/challenges/non-divisible-subset/problem

     * Create an array holding module counts from the set of numbers.
     * Loop through half the array, picking the number higher between two complements that would result in module
     * summation of 3.
     * For example, in case k=7, we pick the higher of ModuloArray[3] or ModuloArray[4] but not both (or we get sum of 7).
     * Edge scenario: We can always pick one item that is divisible by 7 but not more.
*/

#include <bits/stdc++.h>

using namespace std;

int nonDivisibleSubset(int k, vector <int> modCount) {
    int setCount= (modCount[0] != 0);
    for(int i = 1; i <= (k-1)/2; i++) setCount+= modCount[i] > modCount[k-i] ? modCount[i] : modCount[k-i];
    setCount += k%2 == 0 ? (modCount[k/2] != 0) : 0;
    return setCount;
}

int main() {
    int n;
    int k;
    cin >> n >> k;
    vector<int> arr(n);
    vector<int> modCount(k);
    for(int arr_i = 0; arr_i < n; arr_i++) {
        cin >> arr[arr_i];
        modCount[arr[arr_i]%k]++;
    }
    vector<int>::iterator it = modCount.begin();
    int result = nonDivisibleSubset(k, modCount);
    cout << result << endl;
    return 0;
}
