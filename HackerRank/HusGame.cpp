/* Source: https://www.spoj.com/problems/HUSGAME/
 * According to the problem description the only way to win the game is to have 2 stones remaining when a player gets his turn.
 * 1. Observation: It appears that A has a good chance of winning if he has even number of stones during his turn.
 * 2. Even Strategy: If A starts the game and N is even, always make sure Player B gets odd number of stones on table.
 *              If B never gets even number of stones, he never gets a 2 turn and never wins
 * 3. Validation of Even Strategy: (A starts with N = even, Both players rational and using same strategy)
 *      - First option is to leave N - 1 stones for B. We fulfill our strategy.
 *        But how can we be sure that N - 1 stones ?
 *      - Now, B has N - 1 stones on the table.
 *          Case 1: B leaves A with N - 2 stones. A will again have a turn with even stones. A is happy !
 *          Case 2: B leaves A with floor((N - 1 + 1) / 2) stones. If this is even again, A is happy!
 *                  However, if it is odd, A is worried!
 *      - If A realizes that floor((N - 1 + 1) / 2) is a losing position for him/her, he/she realizes that he can put B
 *        in that SAME state before B does that to him by not giving him N - 1 stones in the first place.
 *        Key Idea : floor((N - 1 + 1) / 2) = floor((N + 1) / 2) for N equals even!
 */

#include <iostream>
using namespace std;

#define HUSEY_WINS "HuseyNO"
#define ZIA_WINS "ZiYES"

int main() {

    int test_cases;
    cin >> test_cases;

    unsigned long long N;
    for (int i = 0; i < test_cases; i++) {
        cin >> N;
        if ((N == 1) || (N % 2) == 0) {
            cout << HUSEY_WINS << endl;
            continue;
        }
        unsigned long long count = 0;
        while (N % 2 == 1) {
            count++;
            N = (N + 1) / 2;
        }
        if (count % 2 == 1) cout << ZIA_WINS << endl;
        else cout << HUSEY_WINS << endl;

    }

    return 0;
}
