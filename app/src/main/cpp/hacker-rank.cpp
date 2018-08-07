/*
// Created by john on 8/1/18.
*/
#include "hacker-rank.h"
#include "util.h"
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;

namespace sample_hacker_one {
    // Complete the findNumber function below.
    string findNumber(vector<int> arr, int k) {

        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == k)
                return "YES";
        }
        return "NO";
    }
}

namespace sample_hacker_two {
    // Complete the oddNumbers function below.
    vector<int> oddNumbers(int l, int r) {
        vector<int> odds(0);

        for (int i = l; i <= r; i++) {
            if (i % 2 == 1)
                odds.push_back(i);
        }
        return odds;
    }
}

namespace hacker_one { // Change problem -should spend some time studying similar problems
// Complete the getUmbrellas function below.
    int getUmbrellas(int n, vector<int> p) {


    }
}

namespace hacker_two { // Greedy algorithm

    struct myInt {
        int val;
        int count;
    };

// Complete the maxPoints function below.
    long maxPoints(vector<int> elements) {
        vector<myInt> uniqueElements(0);
        vector<myInt>::iterator it, itSmart, itRemoveStart;

        long countChosenElements = 0;
        long smartPoints, points;

        int element, count;
        myInt *dummy;

        for (int i = 0; i < elements.size(); i++) {
            if (elements[i] == -1)
                continue;

            element = elements[i];
            count = 1;

            for (int j = i + 1; j < elements.size(); j++) {
                if (elements[j] == element) {
                    count++;
                    elements[j] = -1; // Mark the element as consumed
                }
            }

            dummy = new myInt {element, count};

            for (it = uniqueElements.begin(); it < uniqueElements.end(); it++) {
                if (element < it->val) {
                    uniqueElements.insert(it, *dummy);
                    dummy = NULL;
                    break;
                }
            }
            if (dummy != NULL)
                uniqueElements.push_back(*dummy);
        }

        // Accumulate all elements that are distanced far enough from their neighbors to cause no loss of potential points
        it = uniqueElements.begin();
        while (it < uniqueElements.end()) {
            if ((prev(it) == uniqueElements.begin() || prev(it)->val + 1 < it->val) &&
                    (next(it) == uniqueElements.end() || next(it)->val > it->val + 1)) {

                countChosenElements += it->count * it->val;
                uniqueElements.erase(it);
            } else
                it++;
        }

        // Accumulate the rest of the points that are not as obvious
        while (!uniqueElements.empty()) {
            it = uniqueElements.begin();

            // Initialize smart points
            points = it->count * it->val;
            points -= (next(it) == uniqueElements.end() || next(it)->val > it->val + 1) ? 0 : next(it)->count * next(it)->val;
            smartPoints = points;
            itSmart = it;
            it++;

            while (it < uniqueElements.end()) {
                points = it->count * it->val;
                points -= (prev(it)->val + 1 < it->val) ? 0 : prev(it)->count * prev(it)->val;
                points -= (next(it) == uniqueElements.end() || next(it)->val > it->val + 1) ? 0 : next(it)->count * next(it)->val;

                if (points > smartPoints) {
                    smartPoints = points;
                    itSmart = it;
                }
                it++;
            }

            // Accumulate the smart choice, for most points according to the rules
            // COUT(to_string(itSmart->val).data()); // Debug
            countChosenElements += itSmart->count * itSmart->val;

            // Remove the chosen element and the adjacent elements, if any
            itRemoveStart = itSmart;

            if (prev(itSmart) != uniqueElements.begin() && prev(itSmart)->val + 1 == itSmart->val)
                itRemoveStart = prev(itSmart);
            if (next(itSmart) != uniqueElements.end() && next(itSmart)->val == itSmart->val + 1)
                itSmart = next(itSmart);

            uniqueElements.erase(itRemoveStart, itSmart + 1);
        }
        return countChosenElements;
    }

    void test() {
        const int NUMBER_OF_POINTS = 12;
        vector<int> numbers(NUMBER_OF_POINTS);
        int arrPoints[] = {
//                4, 4, 3,
//                3, 3, 1,
//                2, 2, 5,
//                6, 7, 5

            2, 2, 2,
            4, 6, 8,
            4, 8, 12,
            22, 18, 16
        };

        for (int i = 0; i < NUMBER_OF_POINTS; i++) {
            numbers[i] = arrPoints[i];
        }

        COUT(("Number of points scored = " + to_string(maxPoints(numbers))).data())

        /**
         * Number of points scored = 27
         */

        /**
         * Number of points scored = 104
         */
    }
}

namespace hacker_three { // Array Problem, sorting optional
    bool binContains(int l, int r, vector<int> &consumed, int &value) {
        if (l > r)
            return false;

        int m = (l + r) >> 1;

        if (consumed[m] == value)
            return true;

        if (value < consumed[m])
            return binContains(l, --m, consumed, value);

        return binContains(++m, r, consumed, value);
    }

    void consume(vector<int> &consumed, int &value) {
        for (vector<int>::iterator it = consumed.begin(); it < consumed.end(); it++) {
            if (value < *it) {
                consumed.insert(it, value);
                return;
            }
        }
        consumed.push_back(value);
    }

// Complete the numberOfPairs function below.
    int numberOfPairs(vector<int> a, long k) {

        // Keep the pairs distinct, by searching for x in (x, y) | x <= y
        const long midValueGuard = (k >> 1) + 1;

        // A sorted container
        vector<int> consumed(0);

        int complement, num_distinct_pairs = 0;

        for (vector<int>::iterator it = a.begin(); it < a.end(); it++) {
            if (*it < midValueGuard && !binContains(0, (int)consumed.size() - 1, consumed, *it)) {
                // Form the complementary element that makes the pair sum to k
                complement = static_cast<int>(k) - *it;

                // Search for the term
                for (vector<int>::iterator it2 = a.begin(); it2 < a.end(); it2++) {
                    if (it2 != it && *it2 == complement) {
                        num_distinct_pairs++;

                        // Consume the first term in the pair
                        consume(consumed, *it);
                        break;
                    }
                }
            }
        }
        return num_distinct_pairs;
    }

    void test() {
        const int k = 12;

        vector<int> a(0);
        const int vals[] = {
                1, 2, 3, 4,
                5, 6, 6, 9,
                10, 11
        };
        const int size = 10;

        const char terms[] = "Elements: \n";
        COUT(terms);
        string listTerms = "";

        for (int i = 0; i < size; i++) {
            a.push_back(vals[i]);
            listTerms += to_string(vals[i]) + ' ';
        }
        listTerms += '\n';
        COUT(listTerms.data());
        listTerms = "Number of pairs that sum to " + to_string(k) + "...";
        COUT(listTerms.data());
        COUT(to_string(numberOfPairs(a, k)).data());

        /**
         * Elements:
            1 2 3 4 5 6 6 9 10 11
            Number of pairs that sum to 12...
            4
         */
    }
}

namespace hacker_four { // Stack problem


    bool matchingBrace(char left, char right) {
        if (left == '(' && right == ')')
            return true;
        if (left == '[' && right == ']')
            return true;
        if (left == '{' && right == '}')
            return true;
        return false;
    }

    bool balanced(string s) {
        vector<char> leftBraces(0);
        bool prevWasRightBrace = false;

        for (int i = 0; i < s.size(); i++) {
            if ( (s[i] == '(') || (s[i] == '{') || (s[i] == '[') ) {
                // The previous brace was a right brace, so all left braces should be consumed
                if (prevWasRightBrace && !leftBraces.empty())
                    return false;

                leftBraces.push_back(s[i]);
                prevWasRightBrace = false;
            }
            else if ( (s[i] == ')') || (s[i] == '}') || (s[i] == ']') ) {
                if (leftBraces.empty() || !matchingBrace(leftBraces.back(), s[i]))
                    return false;

                leftBraces.pop_back();
                prevWasRightBrace = true;
            }
        }

        // End of string; there should be no more left braces
        return leftBraces.empty();
    }

// Complete the braces function below.
    vector<string> braces(vector<string> values) {
        vector<string> _balanced(values.size());

        for (int i = 0; i < values.size(); i++)
            _balanced[i] = balanced(values[i]) ? "YES" : "NO";

        return _balanced;
    }

    void test() {
        vector<string> input = {
                "[{()}]",
                "{}[]()",
                "{[}]}"
        };

        COUT("Matching Braces");
        output_std(input);

        vector<string> result = braces(input);
        output_std(result);
    }
}

namespace grading_students {
/*
 * Complete the gradingStudents function below.
 */
    vector<int> gradingStudents(vector<int> grades) {
        vector<int> rounded(grades.size());
        // Perform rounding
        for (int i = 0; i < grades.size(); i++)
            rounded[i] = grades[i] < 38 || grades[i] % 5 < 3 ? grades[i] :
                             grades[i] + 5 - (grades[i] % 5);

        return rounded;
    }

    void test() {
        vector<int> grades = {22, 33, 56, 45, 38, 37, 64, 52, 85, 76, 77, 88, 90, 94, 100};
        COUT("Grading Students");
        output_std(grades);

        vector<int> result = gradingStudents(grades);
        output_std(result);
    }
}

namespace min_absolute_distance_array {
    // Complete the minimumAbsoluteDifference function below.
    // I got time-out errors in the test environment
    int minimumAbsoluteDifference(vector<int> arr) {
        int mindiff, absoluteMinDiff = numeric_limits<int>::max();

        for (int i = 0; i < arr.size(); ++i) {
            for (int j = i + 1; j < arr.size(); ++j) {
                if ((mindiff = abs(arr[i] - arr[j])) < absoluteMinDiff) {
                    if (mindiff == 0)
                        return mindiff;
                    else
                        absoluteMinDiff = mindiff;

                    // Debug
//                    COUT(("("+to_string(arr[i])+","+to_string(arr[j])+")").data());
                }
            }
        }
        return absoluteMinDiff;
    }

    int minimumAbsoluteDifference_1_1(vector<int> arr) {
        // Reduce the number of comparisons by first performing a sort
        // We need only compare adjacent elements
//        sort(arr.begin(), arr.end());
        my_quickSort(arr);

        int mindiff, absoluteMinDiff = numeric_limits<int>::max();
        const int comparisons = arr.size() - 1;

        int i = -1;

        while (++i < comparisons) {
            if ((mindiff = arr[i + 1] - arr[i]) < absoluteMinDiff) {
                if (mindiff == 0)
                    return mindiff;
                else
                    absoluteMinDiff = mindiff;

                // Debug
//                    COUT(("("+to_string(arr[i])+","+to_string(arr[j])+")").data());
            }

        }
        return absoluteMinDiff;
    }

    void test() {
        vector<int> nums = {
//                22, 33, 56, 45, 38, 37, 64, 52, 85, 76, 77, 88, 90, 94, 100
                -59, -36, -13, 1, -53, -92, -2, -96, -54, 75
        };
        COUT("Minimum Absolute Distance within Array");
        output_std(nums);

        COUT(to_string(minimumAbsoluteDifference_1_1(nums)).data());
    }
}

namespace grid_challenge {
    // Complete the gridChallenge function below.
    string gridChallenge(vector<string> &grid) {
        sort(grid[0].begin(), grid[0].end());

        for (int i = 1; i < grid.size(); i++) {
            // Sort the rows
            sort(grid[i].begin(), grid[i].end());

            for (int j = 0; j < grid.size(); j++) {
                // Columns must be monotonically increasing
                if (grid[i -1][j] > grid[i][j])
                    return "NO";
            }
        }
        return "YES";
    }

    void test() {
        vector<string> grid = {
                "abdefg",
                "begfad",
                "bagfed",
                "dbagfe",
                "fbdaeg",
                "beagdf"
        };

        COUT("Grid Challenge");
        output_std(grid);

        string result = gridChallenge(grid);
        COUT("Sorting the grid by rows...");
        output_std(grid);
        COUT("Columns are also sorted...");
        COUT(result.data());
    }
}

namespace marcsCakewalk {
    // Complete the marcsCakewalk function below.
    long marcsCakewalk(vector<int> calorie) {
        struct cmp {
            bool operator()(const int &a, const int &b) {
                return a > b;
            }
        };

        // We need calories in descending order to solve the problem
//        sort(calorie.begin(), calorie.end(), greater<int>()); // or equivalently
        sort(calorie.begin(), calorie.end(), cmp {});

        long miles = 0;
        long power = 1;

        for (int c : calorie) {
            miles += power * c;
            power = power << 1;
        }
        return miles;
    }

    void test() {
        vector<int> calories = {
                1,
                2,
                3,
                4,
                5,
                6,
                7,
                14,
                22,
                36,
                44,
                88
        };
        output_std(calories);
        COUT("Minimum number of miles for Marc to walk...");
        COUT(to_string(marcsCakewalk(calories)).data());
    }
}

namespace luck_balance {
    // Complete the luckBalance function below.
    int luckBalance(int k, vector<vector<int>> contests) {
        struct cmp {
            bool operator()(const vector<int> &a, const vector<int> &b) {
                // First sort key = importance: Ti
                // Second sort key = luck value: Li
                return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
            }
        };
        sort(contests.begin(), contests.end(), cmp {});
        int luck = 0;

        for (vector<int> dummy: contests) {
            if (dummy[1])
                break; // Reached the first element of the sorted as 'important' part of contests

            luck += dummy[0];
        }
        int dummy = contests.size();
        while (dummy-- > 0 && contests[dummy][1]) {
            if (k > 0) {
                luck += contests[dummy][0];
                k--;
            } else {
                luck -= contests[dummy][0];
            }
        }

        return luck;
    }

    void test() {
        vector<vector<int>> contests = {
                {4, 1},
                {2, 1},
                {5, 0},
                {22, 1}

//                {5, 1},
//                {2, 1},
//                {1, 1},
//                {8, 1},
//                {10, 0},
//                {5, 0}
        };
        const int k = 2;

        COUT("Luck Balance");
        for (vector<int> x : contests)
            output_std(x);
        COUT(("Important losses allowed = "+to_string(k)).data());
        COUT(("Total luck = "+to_string(luckBalance(k, contests))).data());

        /*
         * Luck Balance
            4 1
            2 1
            5 0
            22 1
            Important losses allowed = 2
            Total luck = 29
            Complete
         */
    }
}

namespace maximumPerimeterTriangle {
    // Complete the maximumPerimeterTriangle function below.
    vector<int> maximumPerimeterTriangle(vector<int> sticks) {
        sort(sticks.begin(), sticks.end());
        for (int i = sticks.size() - 1; i > 1; i--) {
            if (sticks[i] < sticks[i - 1] + sticks[i - 2])
                return {sticks[i - 2], sticks[i - 1], sticks[i]};
        }
        return {-1}; // No triangles found
    }

    void test() {
        vector<int> sticks = {
//                1, 2, 3
                1, 1, 1, 2, 3, 5
        };

        COUT("Maximum Perimeter Triangle");
        output_std(sticks);
        COUT("Answer");
        vector<int> result = maximumPerimeterTriangle(sticks);
        output_std(result);

        /*
         * Maximum Perimeter Triangle
            1 2 3
            Answer
            -1
            Complete
         */

        /*
         * Maximum Perimeter Triangle
            1 1 1 2 3 5
            Answer
            1 1 1
            Complete
         */
    }
}

namespace largestPermutation {
    // Complete the largestPermutation function below.
    vector<int> largestPermutation(int k, vector<int> arr) {
        int mostSignificantSwapPosition = 0;
        int searchValue;

        while (k-- > 0 && mostSignificantSwapPosition < arr.size()) {
            searchValue = arr.size() - mostSignificantSwapPosition;
            for (int i = mostSignificantSwapPosition; i < arr.size(); i++) {
                if (arr[i] == searchValue) {
                    if (i == mostSignificantSwapPosition) { // No swap necessary
                        mostSignificantSwapPosition++;
                        searchValue = arr.size() - mostSignificantSwapPosition;
                    } else {
                        arr[i] = arr[mostSignificantSwapPosition];
                        arr[mostSignificantSwapPosition++] = searchValue;
                        break; // Consume a swap; fallback to the outermost loop
                    }
                }
            }
        }
        return arr;
    }

    void test() {
        vector<int> arr = {
//                5, 4, 3, 2, 1
                1, 2, 3, 4, 5
        };
        COUT("Largest Permutation");
        COUT("Starting Array");
        output_std(arr);

        const int swaps = 1;
        COUT(("Most \'backwards\' array using "+to_string(swaps)+" swap(s)...").data());
        vector<int> result = largestPermutation(swaps, arr);
        output_std(result);

        /*
         * Largest Permutation
            Starting Array
            5 4 3 2 1
            Most 'backwards' array using 1 swap(s)...
            5 4 3 2 1
            Complete
         */

        /*
         *Largest Permutation
            Starting Array
            1 2 3 4 5
            Most 'backwards' array using 1 swap(s)...
            5 2 3 4 1
            Complete
         */
    }
}

namespace greedy_florist {
    // Complete the getMinimumCost function below.
    // precondition: k > 0
    int getMinimumCost(int k, vector<int> c) {
        sort(c.begin(), c.end());

        // kfold is the number of flowers purchased by each of the friends, within the k-fold
        int kfold = 0, index;
        int cost = 0;

        do {
            index = c.size() - k * kfold;
            for (int i = 0; i < k; i++) {
                if (index-- > 0)
                    cost += (kfold + 1) * c[index];
                else
                    goto stop;
            }
            kfold++;

        } while (true);
        stop:
        return cost;
    }

    void test() {
        vector<int> costPerFlower = {
                1, 4, 4, 7, 7, 8, 9, 9, 11
//                1, 3, 5, 7, 9
        };

        const int kFriends = 3;

        COUT("Greedy Florist");
        output_std(costPerFlower);
        COUT(("Number of friends to buy all of the flowers = "+to_string(kFriends)).data());
        COUT("Minimum cost");
        COUT(to_string(getMinimumCost(kFriends, costPerFlower)).data());

        /*
         *Greedy Florist
            1 4 4 7 7 8 9 9 11
            Number of friends to buy all of the flowers = 3
            Minimum cost
            100
            Complete
         */

        /*
         * Greedy Florist
            1 3 5 7 9
            Number of friends to buy all of the flowers = 3
            Minimum cost
            29
            Complete
         */
    }
}

namespace beautiful_pairs {
    // Complete the beautifulPairs function below.
    int beautifulPairs(vector<int> A, vector<int> B) {
        vector<vector<int>> pairs(0);
        vector<vector<int>>::reverse_iterator rit;
        int n = A.size();
        int bDummy;

        for (int i = 0; i < n; ++i) {
            bDummy = 0;

            // Search for if the value of A[i] is already indicated by a beautiful pair.
            // If affirmative, we want an index to start from j in B so that is B[j] == A[i],
            // then j will be greater than any r in our beautiful pairs (l, r), and thus form
            // a new distinct beautiful pair
            for (rit = pairs.rbegin(); rit != pairs.rend(); rit++) {
                if (A[i] == A[(*rit)[0]]) {
                    bDummy = (*rit)[1] + 1;
                    break;
                }
            }

            // Search for the Bj term, such that B[j] == A[i]. Then (i, j) will be our new
            // distinct beautiful pair
            for (int j = bDummy; j < n; ++j) {
                if (A[i] == B[j]) {
                    pairs.push_back({i, j});
                    break;
                }
            }
        }

        // Debug
        for (auto pair : pairs) {
            output_std(pair);
            COUT("\n");
        }

        int distinctPairsBAsIs = pairs.size();

        if (distinctPairsBAsIs == n) {
            // You must replace EXACTLY one element, which will force a loss of a distinct beautiful pair
            // when there are n of them
            distinctPairsBAsIs--;
            goto allDone;
        }

        ////////////////////////////////////////////////////////////////////////////
        // $$
        // Search for an element (in A) to replace in B to maximize disjoint beautiful pairs
        // $$
        /////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < n; i++) {
            // i is a distinct l-value, not in any of our already-constructed beautiful pairs (li, ri)
            for (auto x : pairs) {
                if (i == x[0])
                    goto skipIteration;
            }

            // Show that A[i] is a distinct value, not indexed by any li
            // (We would replace some element in B with A[i])
            for (rit = pairs.rbegin(); rit != pairs.rend(); rit++) {
                if (A[i] == A[(*rit)[0]])
                    goto skipIteration;
            }
            distinctPairsBAsIs++;
            break;

            skipIteration:
            continue;
        }

        allDone:
        return distinctPairsBAsIs;
    }

    void test() {
//        vector<int> A = {
//                1, 2, 3, 4
//        };
//        vector<int> B = {
//                1, 2, 3, 3
//        };
        auto *A = &beautiful_pairs::testCase01_A;
        auto *B = &beautiful_pairs::testCase01_B;

        COUT("Beautiful Pairs");
        int result = beautifulPairs(*A, *B);
        COUT(("Maximum number of disjoint Beautiful Pairs with one replacement in B allowed = "+to_string(result)).data());
    }
}

namespace min_max {
    // Complete the maxMin function below.
    int maxMin(int k, vector<int> arr) {
        sort(arr.begin(), arr.end());

        const int n = arr.size() - k + 1;
        int minrange, range;

        minrange = arr.back() - arr.front();

        for (int i = 0; i < n; i++) {
            range = arr[i + k - 1] - arr[i];
            if (range < minrange)
                minrange = range;
        }
        return minrange;
    }
}

namespace jim_and_the_orders {
    // Complete the jimOrders function below.
    vector<int> jimOrders(vector<vector<int>> orders) {
        struct cmp {
            // Map indices as follows:
            // 0 - order number
            // 1 - prep time
            // 2 - customer number (natural order)
            bool operator() (const vector<int> &a, const vector<int> &b) {
                return a[0] + a[1] < b[0] + b[1] || (
                        a[0] + a[1] == b[0] + b[1] && a[2] < b[2]);
            }
        };

        // Key the customer number to each element in orders, uses 1-based counting
        int i = 1;

        for (int j = 0; j < orders.size(); j++) {
            orders[j].push_back(i++);
        }

        sort(orders.begin(), orders.end(), cmp {} );

        // Debug
//        for (auto x: orders)
//            output_std(x);

        vector<int> servedOrders(orders.size());
        for (int i = 0; i < orders.size(); i++)
            servedOrders[i] = orders[i][2];

        return servedOrders;
    }

    void test() {
        vector<vector<int>> orders = {
                {1, 8},
                {2, 4},
                {3, 3}
        };
        COUT("Jim and the Orders");
        auto result = jimOrders(orders);
        COUT("Order in which customers are served");
        output_std(result);
    }
}

namespace army_bases {
    /*
 * Complete the gameWithCells function below.
 */
    int gameWithCells(int n, int m) {
        // Wrong answer, simply not the counted on the interior connections
        // return (n > 1 ? n - 1 : n) * (m > 1 ? m - 1 : m);

        // The correct idea is to consume to two army bases at a time per drop, and not consume them in a later drop
        return (n / 2 + n % 2) * (m % 2 + m / 2);
    }
}

namespace birthdayCakeCandles {
    // Complete the birthdayCakeCandles function below.
    int birthdayCakeCandles(vector<int> ar) {
        // Aim to solve this problem with as single pass
        long int index, tallest, count;
        index = count = tallest = 0;

        int n = ar.size();
        while (index < n) {
            if (ar[index] > tallest) {
                tallest = ar[index];
                // Reset count, and count for this instance
                count = 1;
            } else if (ar[index] == tallest)
                count++;

            index++;
        }
        return count;
    }
}

namespace miniMaxSum {
    // Complete the miniMaxSum function below.
    void miniMaxSum(vector<int> arr) {
        // Sum, minimum term -> form the max sum, maximum term -> form the min sum
        long long int sum, min, max;
        sum = max = 0;
        min = UINT32_MAX; // We could just set min to the value of the first element in arr; By setting min explicitly, we handle the case arr is empty

        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] > max)
                max = arr[i];
            if (arr[i] < min)
                min = arr[i];

            sum += arr[i];
        }

        // The minimum is printed first
        cout << sum - max << ' ';
        cout << sum - min;
    }
}

namespace forming_magic_square {
    struct node {
        float metric;
        int replacement;
        int selecti;
        int selectj;
        int cost;
    };

    void setNode(node &_node, float &metric, int &replacement, int &cost, int &selecti, int &selectj) {
        _node.metric = metric;
        _node.replacement = replacement;
        _node.cost = cost;
        _node.selecti = selecti;
        _node.selectj = selectj;
    }

    bool isNewDigit(vector<vector<int>> &s, int &replacement) {
        const int size = s.size();

        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (s[i][j] == replacement)
                    return false;

        return true;
    }

    float computeMetric(float directEffects, float indirectEffects, float cost) {
        return (directEffects + indirectEffects) / cost;
    }

    // Complete the formingMagicSquare function below.
    int formingMagicSquare(vector<vector<int>> s) {
        // Forming a benefit:cost metric that parallels s
        // The benefit I will define as the difference between current value for row, column, diag and 15; The cost I will take from the problem definition
        // UPDATE: I add the sum of the effects going in the other directions to the benefit,
        // in order to make 'intelligent' replacements.
        // Example, if a replacement makes a row equal to the target of 15, an effect to add in is by how much farther or closer is the corresponding column, diagonal with the same entry
        // The final metric is the ratio of [benefit + sum of the effects] to cost
        const int targetSum = 15;
        const int size = 3;
        const int upperBoundOpen = 10;
        const int numReplacements = 9; // Terminate if exceeds 9 replacements
        const float lowerBoundMetricOpen = -4 * upperBoundOpen;
        const float lowerBoundMetricClosed = 0;
        int actualNumReplacements;

        vector<int> sumrows(size), sumcolumns(size), sumdiags(2);

        // Used to ensure the replacement is not made on the same entry
        vector<vector<bool>> selectIndicies(size);
        vector<bool> consumedDigits(upperBoundOpen);

        // Best metric is used to decide which replacement to make
        node bestMetric {}, bestMetricNewDigit{};
        node *chosenMetric;
        float metric, ieffects;
        bool solved;
        int dummyReplacement, dummyCost, a, b;
        int totalCost;

        // Initialize
        for (int i = 1; i < upperBoundOpen; i++)
            consumedDigits[i] = false;

        for (int i = 0; i < size; i++) {
            selectIndicies[i].resize(0);
            for (int j = 0; j < size; j++)
                selectIndicies[i].push_back(false);
        }
        totalCost = 0;

        for (actualNumReplacements = 0; actualNumReplacements < numReplacements; actualNumReplacements++) {
            // Reset the best metric
            bestMetric.metric           = lowerBoundMetricOpen;
            bestMetricNewDigit.metric   = lowerBoundMetricOpen;
            solved = true;

            // Find the state of the rows, columns, diags
            // Find their sums relative to targetSum
            sumdiags[1] = sumdiags[0] = targetSum;

            for (int i = 0; i < size; i++) {
                // Diags
                sumdiags[0] -= s[i][i];
                sumdiags[1] -= s[i][size - 1 - i];

                sumrows[i] = sumcolumns[i] = targetSum;
                for (int j = 0; j < size; j++) {
                    sumrows[i] -= s[i][j];
                    sumcolumns[i] -= s[j][i];
                }
                if (!sumrows[i] || !sumcolumns[i])
                    solved = false;
            }
            if (!sumdiags[0] || !sumdiags[1])
                solved = false;

            if (solved)
                break;

            // Calculate the 'benefit' for each entry of the matrix by finding a replacement which makes a row, column, or diagonal equal to targetSum. The replacement is restricted to [1, 9]. Also the effect can positive or negative, depending a row or column is nearer the target sum in magnitude after the replacement would occur. If the cost is 0, the replacement is void.
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (selectIndicies[i][j])
                        continue;

                    // Replacement for row
                    if (sumrows[i]) {
                        dummyReplacement = s[i][j] + sumrows[i];
                        if (dummyReplacement > 0 && dummyReplacement < upperBoundOpen &&
                            !consumedDigits[dummyReplacement]) {

                            dummyCost = abs(sumrows[i]);
                            ieffects = abs(sumcolumns[i]) -
                                       abs(sumcolumns[i] - sumrows[i]); // Variable effects on column

                            if (i == j)
                                ieffects += abs(sumdiags[0]) -
                                            abs(sumdiags[0] - sumrows[i]); // Variable effects on diagonal

                            if (i == size - 1 - j)
                                ieffects += abs(sumdiags[1]) -
                                            abs(sumdiags[1] - sumrows[i]); // Variable effects on diagonal

                            // Assume the difference of the sum of the row and its target is equal to the difference of the entry and its replacement

                            metric = computeMetric(dummyCost, ieffects, dummyCost);
                            chosenMetric = isNewDigit(s, dummyReplacement) ? &bestMetricNewDigit : &bestMetric;

                            if (metric > chosenMetric->metric) {
                                setNode(
                                        *chosenMetric,
                                        metric,
                                        dummyReplacement,
                                        dummyCost,
                                        i,
                                        j
                                );
                            }
                        }
                    }

                    // Replacement for column
                    if (sumcolumns[i]) {
                        dummyReplacement = s[i][j] + sumcolumns[i];
                        if (dummyReplacement > 0 && dummyReplacement < upperBoundOpen &&
                            !consumedDigits[dummyReplacement]) {
                            dummyCost = abs(sumcolumns[i]);
                            ieffects = abs(sumrows[i]) -
                                       abs(sumrows[i] - sumcolumns[i]); // Variable effects on row

                            if (i == j)
                                ieffects += abs(sumdiags[0]) -
                                            abs(sumdiags[0] - sumcolumns[i]); // Variable effects on diagonal

                            if (i == size - 1 - j)
                                ieffects += abs(sumdiags[1]) -
                                            abs(sumdiags[1] - sumcolumns[i]); // Variable effects on diagonal

                            metric = computeMetric(dummyCost, ieffects, dummyCost);
                            chosenMetric = isNewDigit(s, dummyReplacement) ? &bestMetricNewDigit : &bestMetric;

                            if (metric > chosenMetric->metric) {
                                setNode(
                                        *chosenMetric,
                                        metric,
                                        dummyReplacement,
                                        dummyCost,
                                        i,
                                        j
                                );
                            }
                        }
                    }

                    // Replacement for Diagonal 1
                    if (i == j && sumdiags[0]) {
                        dummyReplacement = s[i][j] + sumdiags[0];
                        if (dummyReplacement > 0 && dummyReplacement < upperBoundOpen &&
                            !consumedDigits[dummyReplacement]) {
                            dummyCost = abs(sumdiags[0]);
                            ieffects = abs(sumrows[i]) -
                                       abs(sumrows[i] - sumdiags[0]); // Variable effects on row

                            ieffects += abs(sumcolumns[i]) -
                                        abs(sumcolumns[i] - sumdiags[0]); // Variable effects on column

                            if (i == size - 1 - j)
                                ieffects += abs(sumdiags[1]) -
                                            abs(sumdiags[1] - sumdiags[0]); // Variable effects on diag 2

                            metric = computeMetric(dummyCost, ieffects, dummyCost);
                            chosenMetric = isNewDigit(s, dummyReplacement) ? &bestMetricNewDigit :
                                           &bestMetric;

                            if (metric > chosenMetric->metric) {
                                setNode(
                                        *chosenMetric,
                                        metric,
                                        dummyReplacement,
                                        dummyCost,
                                        i,
                                        j
                                );
                            }
                        }
                    }

                    // Replacement for Diagonal 2
                    if (i == size - 1 - j && sumdiags[1]) {
                        dummyReplacement = s[i][j] + sumdiags[1];
                        if (dummyReplacement > 0 && dummyReplacement < upperBoundOpen &&
                            !consumedDigits[dummyReplacement]) {
                            dummyCost = abs(sumdiags[1]);
                            ieffects = abs(sumrows[i]) -
                                       abs(sumrows[i] - sumdiags[1]); // Variable effects on row

                            ieffects += abs(sumcolumns[i]) -
                                        abs(sumcolumns[i] - sumdiags[1]); // Variable effects on column

                            if (i == j)
                                ieffects += abs(sumdiags[0]) -
                                            abs(sumdiags[0] - sumdiags[1]); // Variable effects on diag 1

                            metric = computeMetric(dummyCost, ieffects, dummyCost);
                            chosenMetric = isNewDigit(s, dummyReplacement) ? &bestMetricNewDigit : &bestMetric;

                            if (metric > chosenMetric->metric) {
                                setNode(
                                        *chosenMetric,
                                        metric,
                                        dummyReplacement,
                                        dummyCost,
                                        i,
                                        j
                                );
                            }
                        }
                    }
                }
            }

            // Give priority to the best metric when a new digit is introduced
            if (bestMetricNewDigit.metric >= lowerBoundMetricClosed)
                chosenMetric = &bestMetricNewDigit;
            else if (bestMetric.metric >= lowerBoundMetricClosed)
                chosenMetric = &bestMetric;
            else
                chosenMetric = NULL;

            if (chosenMetric)
            {
                dummyReplacement = chosenMetric->replacement;
                dummyCost = chosenMetric->cost;
                a = chosenMetric->selecti;
                b = chosenMetric->selectj;
                consumedDigits[dummyReplacement] = true;
                s[a][b] = dummyReplacement;
                totalCost += dummyCost;
                selectIndicies[a][b] = true;
                cout << "s[" << a << "][" << b << "] = "
                     << dummyReplacement <<
                     " with cost = " << dummyCost << endl;
            } else
                break;
        }
        cout << "Actual number of replacements = " << actualNumReplacements << endl;
        cout << endl;
        cout << s[0][0] << ' ' << s[0][1] << ' ' << s[0][2] << endl;
        cout << s[1][0] << ' ' << s[1][1] << ' ' << s[1][2] << endl;
        cout << s[2][0] << ' ' << s[2][1] << ' ' << s[2][2] << endl;
        return totalCost;
    }
}

namespace lowest_triangle {
    int lowestTriangle(int base, int area){
        return ceil(area * 2 / (float)base);
    }
}

namespace plus_minus {
    // Complete the plusMinus function below.
    void plusMinus(vector<int> arr) {
        const int precision = 6;
        const int width = precision;
        int n, neg, p, z;
        double dN;

        n = arr.size();
        dN = n;
        p = z = neg = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] > 0)
                p++;
            else if (arr[i] < 0)
                neg++;
            else
                z++;
        }
        // Print the output to stdout
        cout << setprecision(precision) << fixed << p / dN << endl;
        cout << setprecision(precision) << fixed << neg / dN << endl;
        cout << setprecision(precision) << fixed << z / dN << endl;
    }
}

namespace paper_cutting {
    // Complete the solve function below.
    long solve(int n, int m) {
        // Cut the smaller side a - 1 times to get [number of strips = a] of b squares to cut b - 1 times. Hence,
        // a - 1 + a * (b - 1)
        // == (a * (1) + a * (b - 1)) - 1
        // == a * b - 1;
        return (long)n * m - 1;
    }
}

namespace special_multiples {
    // Complete the solve function below.
    string solve(int n) {
        // We want to leverage numbers created in 9,0 by saving them
        // Leverage solutions for n by saving them
        static vector<unsigned long long> nines_numbers(1, 9);
        static string solved_numbers[501];

        if (solved_numbers[n].length() != 0)
            return solved_numbers[n];

        int index = 0;
        while (true) {
            if (index == nines_numbers.size()) {
                // Construct nines numbers by taking combinations with higher order 9's
                for (int j = 0; j < index; j++) {
                    nines_numbers.push_back(nines_numbers[j] * 10);
                    nines_numbers.push_back(nines_numbers[j] * 10 + 9);
                }
            }
            if (nines_numbers[index] % n == 0) {
                solved_numbers[n] = to_string(nines_numbers[index]);
                return solved_numbers[n];
            }
            index++;
        }
    }
}

namespace staircase {
    // Complete the staircase function below.
    void staircase(int n) {
        for (int i = n; i > 0; i--) {
            for (int j = 0; j < n; j++) {
                if (j < i - 1)
                    cout << ' ';
                else
                    cout << '#';
            }
            cout << endl;
        }
    }
}

namespace time_conversion {
    /*
    * Complete the timeConversion function below.
    */
    string timeConversion(string s) {
        int hours = stoi(s.substr(0, 2)) % 12;

        if (tolower(s.at(8)) == 'p')
            hours += 12;

        return (hours < 10 ? "0" : "") + to_string(hours) + s.substr(2, 6);
    }
}

namespace cutting_boards_hard {
    // Aids in representing a cost that fits in a long to a cost that fits in an int
    const int DIVISOR = 1000000007;

    void updateTotalCostOfCuts(int &cost, int &numberOfSegments, int &costSoFar) {
        long costPerSlice = (cost * numberOfSegments) % DIVISOR;

        costPerSlice = (costPerSlice + costSoFar) % DIVISOR;
        costSoFar = static_cast<int>(costPerSlice);
    }


    // Complete the boardCutting function below.
    // Minimize the cost of cutting a board into 1x1 squares
    int boardCutting(vector<int> cost_y, vector<int> cost_x) {
        int  xit, yit, numHorizontalSegments, numVerticalSegments;

        // Sort reverse of natural order, greatest cost first
        sort(cost_y.begin(), cost_y.end(), greater<int>());
        sort(cost_x.begin(), cost_x.end(), greater<int>());

        int totalCost = 0;
        xit = yit = 0;
        numHorizontalSegments = numVerticalSegments = 1;

        // The cuts with the GREATEST costs are made first.
        // If a cut along rows ties on cost with a cut along columns,
        // then choose the cut with the FEWER segments across first
        while (xit < cost_x.size() && yit < cost_y.size()) {
            if (cost_x[xit] > cost_y[yit]) {
                // Cut along the column, across the current number of vertical segments
                updateTotalCostOfCuts(cost_x[xit++], numVerticalSegments, totalCost);
                numHorizontalSegments++;
            } else if (cost_x[xit] == cost_y[yit]) {
                if (numVerticalSegments < numHorizontalSegments) {
                    // Cut along the column, across the current number of vertical segments
                    updateTotalCostOfCuts(cost_x[xit++], numVerticalSegments, totalCost);
                    numHorizontalSegments++;
                } else {
                    // Cut along the row, across the current number of horizontal segments
                    updateTotalCostOfCuts(cost_y[yit++], numHorizontalSegments, totalCost);
                    numVerticalSegments++;
                }
            } else {
                // Cut along the row, across the current number of horizontal segments
                updateTotalCostOfCuts(cost_y[yit++], numHorizontalSegments, totalCost);
                numVerticalSegments++;
            }
        }

        while (xit < cost_x.size()) {
            updateTotalCostOfCuts(cost_x[xit++], numVerticalSegments, totalCost);
            COUT("Just column cuts");
        }

        while (yit < cost_y.size()) {
            updateTotalCostOfCuts(cost_y[yit++], numHorizontalSegments, totalCost);
            COUT("Just row cuts");
        }

        return totalCost;
    }

    void test() {
//        vector<int> cost_y = {
//                2, 1, 3, 1, 4
//        };
//        vector<int> cost_x = {
//                4, 1, 2
//        };

        COUT("Cuttings Boards");
        COUT(("Total cost equivalence = "+to_string(boardCutting(
                cutting_boards_hard::tc_y_08,
                cutting_boards_hard::tc_x_08
        ))).data());
        COUT(("Expected answer = "+to_string(cutting_boards_hard::tc_answers[7])).data());

        /*
         * Cuttings Boards
            Total cost equivalence = 42
            Complete
         */

        /*
         * // testcase 08
         * Cuttings Boards
            Total cost equivalence = 856128333
            Expected answer = 604491628
            Complete
         */

        /*
         * // testcase 06
         *Cuttings Boards
            Total cost equivalence = 986256778
            Expected answer = 288670782
            Complete
         */

        /*
         * // testcase 03
         * Cuttings Boards
            Total cost equivalence = 129443957
            Expected answer = 733709321
            Complete
         */

        /*
         * // testcase 01
         * Cuttings Boards
            D: Total cost equivalence = 127210119
                Expected answer = 278642107
                Complete

         */

        // The error probably lies in the computation of cost
    }
}

/* The main driver
 *
 *
 *
 *
 *
 *
 *
 *
 */

int main() {
//    hacker_two::test();
//    hacker_three::test();
//    hacker_four::test();
//    grading_students::test();
//    min_absolute_distance_array::test();
//    grid_challenge::test();
//    marcsCakewalk::test();
//    luck_balance::test();
//    maximumPerimeterTriangle::test();
//    largestPermutation::test();
//    greedy_florist::test();
//    beautiful_pairs::test();
//    jim_and_the_orders::test();
    cutting_boards_hard::test();

    COUT("Complete");
    return 0;
}