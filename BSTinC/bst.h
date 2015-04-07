// Struct for a binary search tree node

typedef struct BSTNode {
  int data;
  struct BSTNode* left;
  struct BSTNode* right;
} BSTNode;

BSTNode* newNode(int data);
BSTNode* buildTreeHelper(int nums[], int start, int end);
BSTNode* buildTree(int nums[], int arrayLength);
void preOrderTraversalPrint(BSTNode* root);
void inOrderTraversalPrint(BSTNode* root);
void postOrderTraversalPrint(BSTNode* root);
