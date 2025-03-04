#include <iostream>
#include "BTree.h"
using namespace std;

BTree::BTree(int newValue) {
  value = newValue;
  left = NULL;
  right = NULL;
}

BTree::~BTree() {
  left = NULL;
  right = NULL;
}

void BTree::setValue(int newValue) {
  value = newValue;
}

int BTree::getValue() {
  return value;
}

void BTree::setLeft(BTree* newLeft) {
  left = newLeft;
}

void BTree::setRight(BTree* newRight) {
  right = newRight;
}

BTree* BTree::getLeft() {
  return left;
}

BTree* BTree::getRight() {
  return right;
}
