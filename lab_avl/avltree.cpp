/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* r1 = t->right;
    t->right = r1->left;
    r1->left = t;
    // r1->height ++;
    // t->height = r1->height - 1;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = r1;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* l1 = t->left;
    t->left = l1->right;
    l1->right = t;
    // l1->height ++;
    // t->height = l1->height - 1;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = l1;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int bal = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);

    if (bal == 2) {
      int leftBal = heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right);
      if (leftBal == 1) {
        rotateRight(subtree);
      } else {
        rotateLeftRight(subtree);
      }
    }

    if (bal == -2) {
      int rightBal = heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right);
      if (rightBal == -1) {
        rotateLeft(subtree);
      } else {
        rotateRightLeft(subtree);
      }
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (!subtree) subtree = new Node(key, value);

    else if (key < subtree->key) insert(subtree->left, key, value);

    else if (key > subtree->key) insert(subtree->right, key, value);

    rebalance(subtree);
    //subtree->height = 1 + max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop = subtree->left;
            while (iop->right) iop = iop->right;
            swap(subtree, iop);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            Node* left = subtree->left;
            Node* right = subtree->right;
            delete subtree;
            if (left) subtree = left;
            else subtree = right;
        }
        // your code here
    }
    if (subtree) rebalance(subtree);
}
