#define RANDOM

void stressTest() {
    srand(time(0));

    splay_tree <long long> tree;


    ofstream a("stressOut.txt");
    ofstream b("stressIn.txt");

    ifstream c("in.txt");


    string s;
    set <int> check;

    while (true) {
        int command;
        int x;
#ifdef RANDOM
        command = rand() % 6;
        x = rand() % 200 - 100;

#else
        c >> s >> x;
        if (s == "insert") command = 0;
        else if (s == "exists") command = 1;
        else if (s == "delete") command = 2;
        else command = -1;


#endif
        //cin >> x;
        if (command == 0 /*s == "insert"*/) {
            b << "insert " << x << '\n';
            cerr << "insert " << x << '\n';

            tree.insert(x);
            check.insert(x);
        }

        else if (command == 1/*s == "delete"*/) {
            cerr << "delete " << x << '\n';
            b << "delete " << x << '\n';

            tree.erase(x);
            check.erase(x);
        }

        else if (command == 1/*s == "exists"*/) {
            cerr << "exists " << x << '\n';
            b << "exists " << x << '\n';

            if (tree.exists(x)) {
                if (check.find(x) == check.end()) system("pause");
                else {
                    a << "true\n";
                    cerr << "true\n";
                }
            }
            else {
                if (check.find(x) != check.end()) system("pause");
                a << "false\n";
                cerr << "false\n";
            }
        }
        else if (command == 3/*s == "next"*/) {
            cerr << "next " << x << '\n';
            b << "next " << x << '\n';

            Node<long long>* res = tree.next(x);

            long long checkAns = LLONG_MAX;
            for (auto u : check) {
                if (u > x) {
                    checkAns = u;
                    break;
                }
            }


            if (res == nullptr) {
                if (checkAns == LLONG_MAX) {

                    a << "none" << '\n';
                    cerr << "none" << '\n';
                }
                else {
                    system("pause");
                }
            }
            else {
                if (checkAns == res->key) {
                    a << res->key << '\n';
                    cerr << res->key << '\n';
                }
                else {
                    system("pause");
                }
            }

        }
        else if (command == 4/*s == "prev"*/) {

            cerr << "prev " << x << '\n';
            b << "prev " << x << '\n';

            Node<long long>* res = tree.prev(x);
            long long checkAns = LLONG_MAX;
            for (auto u : check) {
                if (u < x) checkAns = u;
            }

            if (res == nullptr) {
                if (checkAns == LLONG_MAX) {
                    cout << "none" << '\n';
                    a << "none" << '\n';
                }
                else {
                    system("pause");
                }

            }
            else {
                if (checkAns == res->key) {
                    cout << res->key << '\n';
                    a << res->key << '\n';
                }
                else {
                    system("pause");
                }
            }
        }

        else if (command == 5/*s == "order"*/) {
            if (tree.size() == 0) continue;
            x = rand() % tree.size() + 1;
            cerr << "order " << x << '\n';
            b << "order " << x << '\n';

            long long checkAns = LLONG_MAX;
            int t = 0;
            for (auto u : check) {
                t++;
                if (t == x) {
                    checkAns = u;
                    break;
                }
            }

            auto res = tree.find_by_order(x);
            if (res->key != checkAns) {
                system("pause");
            }
            else {
                cerr << res->key << '\n';
                a << res->key << '\n';
            }
        }

        if (check.size() != tree.size()) {
            cerr << "Sizes do not match\n";
            system("pause");
        }
        cerr << '\n';
        a << '\n';
        b << '\n';
        a.flush();
        b.flush();
    }
}