/*
// Created by john on 8/1/18.
*/
#include "hacker-rank.h"
#include "util.h"
#include <string>
#include <vector>
#include <iostream>
#include <limits>

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
    luck_balance::test();

    COUT("Complete");
    return 0;
}