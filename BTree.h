#ifndef BTREE_H
#define BTREE_H
#include <iostream>
using namespace std;

class BTree {
 public:
  BTree(int newValue);
  ~BTree();
  void setLeft(BTree* newLeft);
  void setRight(BTree* newRight);
  void setValue(int newValue); 
  BTree* getLeft();
  BTree* getRight();
  int getValue();
 protected:
  int value;
  BTree* left;
  BTree* right;
};
#endif
