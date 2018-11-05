#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <set>
#include <vector>

#include "splay.h"

using namespace std;


#define STRESS
#ifdef STRESS
#include "stress.h"
#endif

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


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
