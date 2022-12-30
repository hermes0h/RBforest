/*
 * Skeleton code for project 3 in EE205 2018 Fall KAIST
 * Created by Wan Ju Kang.
 */

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef enum
{
    RED = 0,
    BLACK = 1,
    DOUBLE_BLACK = 2
} RBNodeColor;

inline RBNodeColor &operator+=(RBNodeColor &color, int a)
{
    color = static_cast<RBNodeColor>(static_cast<int>(color) + a);
    return color;
}

/*
 * ############################CAUTION!!!############################
 * You can define any additional features for your debugging purpose,
 * but make sure you remove all of them before you submit this.
 * ##################################################################
 */

template <class T>
class RBNode
{
public:
    uint32_t x_key;
    uint32_t y_key;
    T value;
    RBNodeColor color;

    class RBNode<T> *leftChild;
    class RBNode<T> *rightChild;
    class RBNode<T> *parent;

    // Constructor for RB_Matrix
    RBNode(uint32_t x, uint32_t y, RBNode<T> *p)
        : x_key{x},
          y_key{y},
          leftChild{NULL},
          rightChild{NULL},
          parent{p},
          value{},
          color{BLACK}
    {
    }

    // Constructor for LHRM_Matrix
    RBNode(uint32_t y, RBNode<T> *p)
        : x_key{}, // Not Used
          y_key{y},
          leftChild{NULL},
          rightChild{NULL},
          parent{p},
          value{},
          color{BLACK}
    {
    }
};

template <class T>
class RBTree
{
public:
    RBTree();
    ~RBTree();

    void display();

    int set_value(RBNode<T> *n, uint32_t x, uint32_t y, T value);
    RBNode<T> *set_value(uint32_t y, T value);

    bool remove(uint32_t x, uint32_t y, RBNode<T> *n);
    bool remove(uint32_t y, RBNode<T> *n);

    RBNode<T> *search(uint32_t x, uint32_t y, RBNode<T> *n);
    RBNode<T> *search(uint32_t y, RBNode<T> *n);

    RBNode<T> *get_root(void);

    bool is_external(RBNode<T> *n);
    bool is_root(RBNode<T> *n);

    void inorder_print(RBNode<T> *n);

    void clean(RBNode<T> *n);

private:
    RBNode<T> *root;
    void post_insertion_balance(RBNode<T> *n); // balancing after insertion
    void post_removal_balance(RBNode<T> *n);   // balancing after removal
    RBNode<T> *rotate_right(RBNode<T> *n);
    RBNode<T> *rotate_left(RBNode<T> *n);
    bool is_double_red(RBNode<T> *n);
    bool is_double_black(RBNode<T> *n);
    RBNode<T> *restructure(RBNode<T> *n, int direction);

    void preorder_print(RBNode<T> *n);
};

template <class T>
RBTree<T>::RBTree()
{
    root = new RBNode<T>(0, 0, NULL);
}

template <class T>
RBTree<T>::~RBTree()
{
    this->clean(this->root);
}

template <class T>
void RBTree<T>::display()
{
    if (is_external(root))
    {
        cout << "Tree is empty." << endl;
        return;
    }
    cout << root->x_key << ", " << root->y_key << endl;

    inorder_print(root);
    cout << endl;
    preorder_print(root);
    cout << endl;
}

template <class T>
RBNode<T> *RBTree<T>::get_root(void)
{
    return root;
}

template <class T>
bool RBTree<T>::is_external(RBNode<T> *n)
{

    return (n->leftChild == NULL && n->rightChild == NULL);
}

template <class T>
bool RBTree<T>::is_root(RBNode<T> *n)
{

    return n->parent == NULL;
}

#endif /* __RB_TREE_H__ */