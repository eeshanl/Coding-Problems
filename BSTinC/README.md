# Binary Search Tree implementation in C
* struct for BSTNode used:

```
typedef struct BSTNode {
  int data;
  struct BSTNode* left;
  struct BSTNode* right;
} BSTNode;
```

* Recursively built tree from sorted array using binary search to traverse the array. Used the middle of the array as root of the tree.
