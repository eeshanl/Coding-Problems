#include <stdio.h> // for printf
#include <stdlib.h> // for malloc
#include "bst.h"

// Constructing a balanced BSTree from a sorted array.
int main() {
  int nums[] = {1, 2, 3, 4, 5, 6, 7};
  int arraylength = sizeof(nums)/sizeof(nums[0]);
  BSTNode* root = buildTree(nums, arraylength);
  printf("Pre order Traversal: ");
  preOrderTraversalPrint(root);
  printf("\nIn order Traversal: ");
  inOrderTraversalPrint(root);
  printf("\nPost order Traversal: ");
  postOrderTraversalPrint(root);
  printf("\n");
  return 0;
}

// Constructs a new node
BSTNode* newNode(int data) {
  BSTNode* node = (BSTNode*) malloc(sizeof(BSTNode));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// builds a tree from a sorted array using binary search. Makes the middle of the array the root of the tree.
BSTNode* buildTree(int nums[], int arrayLength) {
  return buildTreeHelper(nums, 0, arrayLength - 1);
}

// buildTree helper method that recursivley builds tree
BSTNode* buildTreeHelper(int nums[], int start, int end) {
  if (start > end) return NULL;
  int mid = (start + end)/2;
  // Take middle of array as root of tree
  BSTNode* root = newNode(nums[mid]);
  // recursivley build left half of tree with left half of array
  root->left = buildTreeHelper(nums, start, mid - 1);
  // recursivley build right half of tree with right half of array
  root->right = buildTreeHelper(nums, mid + 1, end);
  return root;
}

// pre order traversal print
void preOrderTraversalPrint(BSTNode* root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preOrderTraversalPrint(root->left);
    preOrderTraversalPrint(root->right);
  }
}

// in porder traversal print
void inOrderTraversalPrint(BSTNode* root) {
  if (root != NULL) {
    inOrderTraversalPrint(root->left);
    printf("%d ", root->data);
    inOrderTraversalPrint(root->right);
  }
}

// post order traversal print
void postOrderTraversalPrint(BSTNode* root) {
  if (root != NULL) {
    postOrderTraversalPrint(root->left);
    postOrderTraversalPrint(root->right);
    printf("%d ", root->data);
  }
}
