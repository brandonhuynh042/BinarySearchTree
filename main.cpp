#include <iostream>
#include <cstring>
#include "BTree.h"

using namespace std;
BTree* add(BTree* root, int addInput);
void printTree(BTree* root);
void searchTree(BTree* root, int searchInput);
int main() {
  bool quit = false;
  char input[30];
  BTree* root = NULL;
  do {
    cout << "You can: \'ADD\' \'PRINT\' \'DELETE\' \'SEARCH\' \'QUIT\'" << endl;
    cin >> input;
    if (strcmp(input, "QUIT") == 0) {
      quit = true;
    }
    else if (strcmp(input, "ADD") == 0) {
      cout << "What is the number you'd like to add?" << endl;
      int addInput;
      cin >> addInput;
      root = add(root, addInput);
    }
    else if (strcmp(input, "DELETE") == 0) {

    }
    else if (strcmp(input, "PRINT") == 0) {
      printTree(root);
      cout << endl;
    }
    else if (strcmp(input, "SEARCH") == 0) {
      cout << "What number are you looking for?" << endl;
      int searchInput;
      cin >> searchInput;
      searchTree(root, searchInput);
    }
  } while (quit != true);
  return 0;
}

BTree* add(BTree* root, int addInput) {
  if (!root) {
    root = new BTree(addInput);
  }
  else if (root->getValue() > addInput) {
    root->setLeft(add(root->getLeft(), addInput));
  }
  else {
    root->setRight(add(root->getRight(), addInput));
  }
  return root;
}

void printTree(BTree* root) {
  if (root == NULL) {
    return;
  }
  cout << root->getValue() << " ";
  printTree(root->getLeft());
  printTree(root->getRight());
}

void searchTree(BTree* root, int searchInput) {
  if (root == NULL) {
    return;
  }
  if (root->getValue() == searchInput) {
    cout << "This number is in the tree." << endl;
  }
  searchTree(root->getLeft(), searchInput);
  searchTree(root->getRight(), searchInput);
    cout << "This number is not in the tree." << endl;
 }
