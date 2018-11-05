#pragma once

template <typename T>
struct Node {
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    Node<T>* next;
    Node<T>* prev;
    T key;

    size_t size;

    Node() {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        next = nullptr;
        prev = nullptr;
        size = 1;
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

    splay_tree(Node<T>* root) {
        this->root = root;
    }

    void insert(const T& key) {
        if (root == nullptr) {
            root = new Node<T>(key);
            return;
        }

        Node<T>* res = find_by_key(key);

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

    void erase(const T& key) {
        Node<T>* res = find_by_key(key);

        if (res == nullptr || res->key != key) return;

        Node<T>* tmp = res->prev;
        if (res->prev != nullptr)
            res->prev->next = res->next;
        if (res->next != nullptr)
            res->next->prev = tmp;

        splay_tree<T>* R = split(key);

        Node<T>* wasRoot = root;
        root = wasRoot->left;
        delete wasRoot;

        if (root != nullptr)
            root->parent = nullptr;


        join(R);

    }

    bool exists(const T& key) {
        Node<T>* res = find_by_key(key);

        if (res == nullptr || res->key != key)
            return 0;
        else 
            return 1;
    }

    Node<T>* next(const T& key) {
        Node<T>* res = find_by_key(key);

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
        Node<T>* res = find_by_key(key);

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

    Node<T>* find_by_order(size_t order, Node<T>* cur) {

        if (order == size(cur->left) + 1) return cur;
        if (order <= size(cur->left)) {
            return find_by_order(order, cur->left);
        }
        else {
            return find_by_order(order - size(cur->left) - 1, cur->right);
        }
    }

    size_t size() {
        return size(root);
    }

private:

    size_t size(Node<T>* cur) {
        return (cur == nullptr) ? 0 : cur->size;
    }

    void fix_size(Node<T>* cur) {
        if (cur != nullptr) {
            cur->size = 1 + size(cur->left) + size(cur->right);
        }
    }

    Node<T>* find_by_key(const T& key) {
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

    void zig(Node<T>* cur) {
        if (cur == nullptr) return;
        if (cur->parent == nullptr) {
            fix_size(cur);
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

        fix_size(cur->left);
        fix_size(cur->right);
        fix_size(cur);
    }

    void splay(Node<T>* cur) {
        if (cur == nullptr) return;
        if (cur->parent == nullptr) {
            fix_size(cur);
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

    splay_tree<T>* split(const T& key) {

        Node<T>* res = find_by_key(key);

        if (res == nullptr) return nullptr;

        if (res->key != key) return nullptr;

        splay(res);

        Node<T>* R = root->right;
        root->right = nullptr;
        if (R != nullptr)
            R->parent = nullptr;

        fix_size(root);
        return new splay_tree<T>(R);
    }

    void join(splay_tree<T>* R) {
        if (root == nullptr && R->root == nullptr) {
            delete R;
            return;
        }
        splay(get_max());

        if (root != nullptr) {
            root->right = R->root;

            if (root->right != nullptr)
                root->right->parent = root;
        }
        else {
            root = R->root;
            root->parent = nullptr;
        }
        fix_size(root);

        delete R;
    }

    Node<T>* get_max() {
        Node<T>* cur = root;
        if (cur == nullptr) return nullptr;
        while (cur->right != nullptr) {
            cur = cur->right;
        }

        return cur;
    }

};