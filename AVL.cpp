#include <cassert>

using namespace std;
template <typename T> struct AVLNode {
  T data;
  int height;
  AVLNode *left;
  AVLNode *right;
  AVLNode(T data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
  }
};
int max(int a, int b) { return a > b ? a : b; }
template <typename T> class AVL {
private:
  AVLNode<T> *root;
  int getHeight(AVLNode<T> *node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }
  void updateHeight(AVLNode<T> *node) {

    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = 1 + max(leftHeight, rightHeight);
  }
  int getBalance(AVLNode<T> *node) {
    if (node == nullptr) {
      return 0;
    }
    return getHeight(node->right) - getHeight(node->left);
  }
  void insertRec(AVLNode<T> *&node, T data) {
    if (node == nullptr) {
      node = new AVLNode<T>(data);
    }
    if (data < node->data) {
      this->insertRec(node->left, data);
    } else {
      this->insertRec(node->right, data);
    }
    this->updateHeight(node);

    int balance = getBalance(node);

    if (balance <= -2 && node->left->data > data) {
      // left left case
      this->rightRotate(node);
    }

    if (balance <= -2 && node->left->data < data) {
      // left right case
      this->leftRotate(node->left);
      this->rightRotate(node);
    }

    if (balance >= 2 && node->right->data < data) {
      // right right case
      this->leftRotate(node);
    }

    if (balance >= 2 && node->right->data > data) {
      // right left case
      this->rightRotate(node->right);
      this->leftRotate(node);
    }
  }
  bool existRec(AVLNode<T> *node, T data) {
    if (node == nullptr) {
      return false;
    }
    if (node->data == data) {
      return true;
    }
    if (data < node->data) {
      return this->existRec(node->left, data);
    } else {
      return this->existRec(node->right, data);
    }
  }

public:
  AVL() { this->root = nullptr; }
  void insert(T data) { this->insertRec(this->root, data); }
  bool exist(T data) { return this->existRec(this->root, data); }
};
