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

using namespace std;

template <typename T>
struct Node {
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    Node<T>* next;
    Node<T>* prev;
    size_t size;
    T key;

    Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        next = nullptr;
        prev = nullptr;
        size = 0;
    }
    Node(const T& a) : Node() {
        key = a;
    }
};

template <typename T>
struct splay_tree {
    Node<T>* root;

    splay_tree() {
        root = nullptr;
    }


    void zig(Node<T>* cur) {
        if (cur == nullptr) return;
        if (cur->parent == nullptr) {
            return;
        }
        if (cur->parent->parent) {
            if (cur->parent->parent->left == cur->parent) {
                cur->parent->parent->left = cur;
            }
            else {
                cur->parent->parent->right = cur;
            }
        }

        if (cur->parent->left == cur) {
            Node<T>* P = cur->parent;
            Node<T>* R = cur->right;
            cur->parent = P->parent;
            cur->right = P;
            P->parent = cur;
            P->left = R;
            if (R) {
                R->parent = P;
            }
        }

        else if (cur->parent->right == cur) {
            Node<T>* P = cur->parent;
            Node<T>* L = cur->left;
            cur->parent = P->parent;
            cur->left = P;
            P->parent = cur;
            P->right = L;
            if (L) {
                L->parent = P;
            }
        }

        if (cur->parent == nullptr) {
            root = cur;
        }
    }


    void splay(Node<T>* cur) {
        if (cur == nullptr) return;
        if (cur->parent == nullptr) {
            root = cur;
            return;
        }
        if (cur->parent->parent == nullptr) {
            zig(cur);
            root = cur;
            return;
        }
        zig(cur->parent);
        zig(cur);
        splay(cur);
    }

    Node<T>* find_node(const T& key) {
        if (root == nullptr) return nullptr;

        Node<T>* cur = root;
        while (true) {
            if (key > cur->key) {
                if (cur->right == nullptr) break;
                else cur = cur->right;
            }
            else if (key < cur->key) {
                if (cur->left == nullptr) break;
                else cur = cur->left;
            }
            else {
                break;
            }
        }

        return cur;
    }


    void insert(const T& key) {
        if (root == nullptr) {
            root = new Node<T>(key);
            return;
        }

        Node<T>* res = find_node(key);

        if (res->key == key) return;
        if (key > res->key) {
            res->right = new Node<T>(key);
            res->right->parent = res;

            if (res->next != nullptr)
                res->next->prev = res->right;
            res->right->next = res->next;

            res->next = res->right;
            res->right->prev = res;

            splay(res->right);
        }
        else {
            res->left = new Node<T>(key);
            res->left->parent = res;

            if (res->prev != nullptr)
                res->prev->next = res->left;
            res->left->prev = res->prev;

            res->prev = res->left;
            res->left->next = res;

            splay(res->left);
        }

    }

    pair <Node<T>*, Node<T>*> split(const T& key) {
        if (root == nullptr) return { nullptr, nullptr };

        Node<T>* res = find_node(key);

        if (res == nullptr) return { nullptr, nullptr };

        if (res->key != key) return { nullptr, nullptr };

        splay(res);

        Node<T>* R = root->right;
        root->right = nullptr;
        if (root->right != nullptr)
            R->parent = nullptr;

        return { root, R };
    }

    void join(Node<T>* L, Node<T>* R) {
        if (L == nullptr && R == nullptr) return;
        splay(get_max(L));


        if (root != nullptr) {
            root->right = R;

            if (R != nullptr)
                R->parent = root;
        }
        else {
            root = R;
            R->parent = nullptr;
        }

    }

    void erase(const T& key) {
        if (root == nullptr) return;

        Node<T>* res = find_node(key);
        if (res != nullptr && res->key == key) {
            Node<T>* tmp = res->prev;
            if (res->prev != nullptr)
                res->prev->next = res->next;
            if (res->next != nullptr)
                res->next->prev = tmp;
        }



        pair<Node<T>*, Node<T>*> p = split(key);

        if (p.first == nullptr && p.second == nullptr) return;

        Node<T>* was = p.first;
        p.first = p.first->left;
        delete was;

        root = p.first;
        if (p.first != nullptr)
            p.first->parent = nullptr;

        join(p.first, p.second);
    }

    bool exists(const T& key) {
        if (root == nullptr) return 0;

        Node<T>* res = find_node(key);

        if (res == nullptr) return 0;
        if (res->key == key) {
            return 1;
        }
        else return 0;
    }


    Node<T>* get_max(Node<T>* start) {
        if (start == nullptr) return nullptr;
        while (start->right != nullptr) {
            start = start->right;
        }

        return start;
    }

    Node<T>* next(const T& key) {
        Node<T>* res = find_node(key);
        if (res == nullptr)
            return nullptr;

        Node<T>* ans = nullptr;

        if (res->key > key) {
            ans = res;
        }
        else if (res->key <= key) {
            ans = res->next;
        }

        return ans;
    }

    Node<T>* prev(const T& key) {
        Node<T>* res = find_node(key);

        if (res == nullptr)
            return nullptr;

        Node<T>* ans = nullptr;

        if (res->key < key) {
            ans = res;
        }
        else if (res->key >= key) {
            ans = res->prev;
        }

        return ans;
    }
};


#include "stress.h"

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    //srand(time(0));


    splay_tree<int> tree;

#ifdef Stress
    stress();
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

    }

    return 0;
}