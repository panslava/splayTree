#define Stress

void stress() {
    splay_tree<long long> tree;


    ofstream a("stressOut.txt");
    ofstream b("stressIn.txt");


    string s;
    set <int> check;

    while (true) {

        int command = rand() % 5;
        int x = (rand() - 16000) % 100;

        //cin >> x;
        if (command == 0 /*s == "insert"*/) {
            b << "insert " << x << '\n';
            cerr << "insert " << x << '\n';

            tree.insert(x);
            check.insert(x);
        }

        else if (command == 1/*s == "exists"*/) {
            cerr << "exists " << x << '\n';
            b << "exists " << x << '\n';

            if (tree.exists(x)) {
                if (check.find(x) == check.end()) system("pause");
                else {
                    a << "true\n";
                    cout << "true\n";
                }
            }
            else {
                if (check.find(x) != check.end()) system("pause");
                a << "false\n";
                cout << "false\n";
            }
        }
        else if (command == 2/*s == "delete"*/) {
            cerr << "delete " << x << '\n';
            b << "delete " << x << '\n';
            tree.erase(x);
            check.erase(x);
        }
        //else if (command == 3/*s == "next"*/) {
        //    cerr << "next " << x << '\n';
        //    b << "next " << x << '\n';

        //    Node<long long>* res = tree.next(x);


        //    if (res == nullptr) {
        //        if (check.upper_bound(x) == check.end()) {

        //            a << "none" << '\n';
        //            cout << "none" << '\n';
        //        }
        //        else {
        //            system("pause");
        //        }
        //    }
        //    else {

        //        if (*check.upper_bound(x) == res->key) {
        //            a << res->key << '\n';
        //            cout << res->key << '\n';
        //        }
        //        else {
        //            system("pause");

        //        }
        //    }

        //}
        //else if (command == 4/*s == "prev"*/) {

        //    cerr << "prev " << x << '\n';
        //    b << "prev " << x << '\n';



        //    Node<long long>* res = tree.prev(x);

        //    if (res == nullptr) {
        //        auto u = check.lower_bound(x - 1);
        //        u--;
        //        if (u == check.end()) {

        //            cout << "none" << '\n';
        //            a << "none" << '\n';
        //        }
        //        else {
        //            system("pause");
        //        }

        //    }
        //    else {
        //        auto u = check.lower_bound(x - 1);
        //        u--;

        //        if (*u == res->key) {
        //            cout << res->key << '\n';
        //            a << res->key << '\n';
        //        }
        //        else {
        //            system("pause");
        //        }
        //    }
        //}


        cerr << '\n';
        a << '\n';
        b << '\n';
        a.flush();
        b.flush();
    }
}