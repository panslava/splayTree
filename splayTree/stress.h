#define RANDOM

void stress() {
    splay_tree<long long> tree;


    ofstream a("stressOut.txt");
    ofstream b("stressIn.txt");

    ifstream c("in.txt");


    string s;
    set <int> check;

    while (true) {
        int command;
        int x;
#ifdef RANDOM
        command = rand() % 3 - 1;
        x = (rand() - 16000) % 100;

#else
        c >> s >> x;
        if (s == "insert") command = 0;
        else if (s == "exists") command = 1;
        else if (s == "delete") command = 2;
        else command = -1;


#endif
        //cin >> x;
        if (command == 1 /*s == "insert"*/) {
            b << "insert " << x << '\n';
            cerr << "insert " << x << '\n';

            tree.insert(x);
            check.insert(x);
        }

        else if (command == 0/*s == "exists"*/) {
            x = rand() % tree.root->size + 1;
            cerr << "order " << x << '\n';
            b << "order " << x << '\n';


            auto res = tree.find_by_order(x, tree.root);
            if (res != nullptr)
                cout << res->key << '\n';
        }
        else if (command == -1/*s == "delete"*/) {
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

        if (check.size() != tree.get_size(tree.root)) {
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