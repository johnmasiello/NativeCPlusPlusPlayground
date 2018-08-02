//
// Created by john on 7/31/18.
//

#include "sherlock-tiles.h"
#include "util.h"
#include <cmath>
#include <string>

using namespace std;

int sherlockTilesDriver() {
    int s1, s2, l;

    l = 1000000;
    s1 = 1000004;
    s2 = 1000003;

    vector<long int> qs(1, 258385599125);
    vector<double> ts = movingTiles(l, s1, s2, qs);

    for (int i = 0; i < ts.size(); i++)
        COUT((to_string(ts[i]) + '\n').data());

    /*
     * 07-31 18:32:18.997 2749-2779/? D/PurchaseBooks: 695345.564581 // correct answer
     */
    return 0;
}

vector<double> movingTiles(int l, int s1, int s2, vector<long int> queries) {
    vector<double> ans(queries.size());
    double coeff = sqrt(2) / (s1 > s2 ? s1 - s2 : s2 - s1);

    for (int i = 0; i < queries.size(); i++)
        ans[i] = coeff * (l - sqrt((double)queries[i]));

    return ans;
}
