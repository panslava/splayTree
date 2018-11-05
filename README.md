# splayTree

Simple [splay tree](https://en.wikipedia.org/wiki/Splay_tree) implementation with fast k-order statistics

Operations: 

 - *insert (key)*. Add new Node to tree by key. If Node with such key already exists &mdash; doesn't do anything
 - *erase (key)*. Erase Node from tree by key. If Node with such key doesn't exists &mdash; doesn't do anything
 - *exists (key)*. Returns true if Node with argument key exists in tree. Else returns false
 - *next (key)*. Returns minimum Node with key > argument key. If no such Node &mdash; returns nullptr
 - *prev (key)*. Returns maximum Node with key < argument key. If no such Node &mdash; returns nullptr
 - *find_by_order (order)*. Returns Node by order. If order > size of tree &mdash; return nullptr
 - *find_by_key (key)*. Finds and returns Node by key. If Node with such key doesn't exists &mdash; returns nullptr
 - *size()*. Returns size of the tree
 
 All operations complexity: **O(log n)**. Size operation complexity: **O(1)**
 
 Todo:
 
 - iterators
