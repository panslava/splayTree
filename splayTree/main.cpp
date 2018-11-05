#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
//#include <windows.h>
#include <math.h>
#include <algorithm>
#include <bitset>
#include <climits>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <locale>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#include "splay.h"

using namespace std;


//#define STRESS
#ifdef STRESS
#include "stress.h"
#endif

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    //srand(time(0));


    splay_tree<int> tree;

#ifdef STRESS
    stress();
#endif

    int n;
    cin >> n;

    int com, x;
    while (cin >> com) {
        cin >> x;
        if (com == 1) {
            tree.insert(x);
        }
        else if (com == 0) {
            auto res = tree.find_by_order(tree.root->size - x + 1, tree.root);
            cout << res->key << '\n';
        }
        else if (com == -1) {
            tree.erase(x);
        }
    }

    return 0;
}

/*
30
+1 10
0 1
-1 10
*/