#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <set>
#include <vector>

#include "splay.h"

using namespace std;


//#define STRESS
#ifdef STRESS
#include "stressTest.h"
#endif

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);


    splay_tree<int> tree;

#ifdef STRESS
    stressTest();
#endif
    
    string s;

    while (cin >> s) {

        int x;
        cin >> x;
        if (s == "insert") {
            tree.insert(x);
        }

        else if (s == "exists") {
            if (tree.exists(x)) {
                cout << "true\n";
            }
            else cout << "false\n";
        }
        else if (s == "delete") {
            tree.erase(x);
        }
        else if (s == "next") {
            Node<int>* res = tree.next(x);

            if (res == nullptr)
                cout << "none" << '\n';
            else
                cout << res->key << '\n';

        }
        else if (s == "prev") {
            Node<int>* res = tree.prev(x);

            if (res == nullptr)
                cout << "none" << '\n';
            else
                cout << res->key << '\n';
        }
        else if (s == "order") {
            Node<int>* res = tree.find_by_order(x);

            if (res == nullptr)
                cout << "none" << '\n';
            else
                cout << res->key << '\n';
        }
    }

    return 0;
}
