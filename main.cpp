#include <iostream>

using namespace std;

template<typename T, int n>
struct Node {
    T **value;
    Node **child;
    int count;
    bool isLeaf;

public:
    Node() {
        count = 0;
        isLeaf = false;
        this->value = new T *[n];
        this->child = new Node *[n];
        for (int i = 0; i < n; i++) {
            this->child[i] = nullptr;
            this->value[i] = nullptr;
        }
    }

    int addValue(T Value) {
        int i;
        for (i = 0; i < n; i++) {
            if (value[i] == nullptr) break;
            if (Value > *(value[i])) break;
        }
        for (int j = i; j < count; j++) {
            value[j + 1] = value[j];
        }
        value[i] = &Value;
        count++;
        return i;
    }

    Node *findLeaf(Node<T, n> *root, int val) {
        bool flag = false;
        if (root->isLeaf) return root;
        else {
            for (int i = 0; i < count; i++) {
                if (val < *(root->value[i])) {
                    flag = true;
                    return findLeaf(&(root[i]), val);
                }
            }
            if (!flag) return findLeaf(&(root[count]), val);
        }
    }

    bool exist(T val) {
        for (int i = 0; i < count; i++) {
            if (val == *value[i]) return true;
        }
        return false;
    }
};

template<typename T, int n>
class BTree {
    Node<T, n> *root;
public:
    BTree() {
        root = new Node<T, n>;
        root->isLeaf = true;
    }

    void insert(T value) {
        Node<T, n> *leaf = root->findLeaf(root, value);
        leaf->addValue(value);
        if (leaf == root)
            split(leaf, -1);
        else
            split(leaf, 0);

    }

    void split(Node<T, n> *node, int flag) {
        if (node->count == n) {
            if (flag == -1) {
                Node<T, n> *root = new Node<T, n>;
                Node<T, n> *rightChild = new Node<T, n>;
                T *midValue = node->value[n / 2];
                node->value[n / 2] = nullptr;
                for (int i = n / 2 + 1; i < n-1; i++) {
                    rightChild->addValue(*(node->value[i]));
                    rightChild->count++;
                    node->value[i] = nullptr;
                    node->count--;
                }
                rightChild->isLeaf= true;
                root->addValue(*midValue);
                node->count--;
                node->isLeaf= true;
                root->child[0] = node;
                root->child[1] = rightChild;
                this->root = root;
                root->isLeaf= true;

            } else {
                T *midValue = node->value[n / 2];
                Node<T, n> *parent = findParent(*midValue);
                node->value[n / 2] = nullptr;
                int index = parent->addValue(*midValue);
                for (int i = index + 1; i < parent->count - index + 1; i++) {
                    parent->child[i + 1] = parent->child[i];
                }
                parent->child[index + 1] = new Node<T, n>;
                for (int i = n / 2 + 1; i < n; i++) {
                    parent->child[index + 1]->addValue(*node->value[i]);
                    node->value[i] = nullptr;
                }
            }
        }
    }

    Node<T, n> *findParent(T value) {
        Node<T, n> *current = root;
        Node<T, n> *parent;
        while (!current->exist(value)) {
            bool found = false;
            for (int i = 0; i < current->count; i++) {
                if (value < *current->value[i]) {
                    found = true;
                    parent = current;
                    current = current->child[i];
                    break;
                }
            }
            if (!found) {
                parent = current;
                current = current->child[current->count];
            }
        }
        return parent;
    }
};

int main() {
    BTree<char, 4> s;
    s.insert('a');
    s.insert('b');
    s.insert('c');
    s.insert('d');
    s.insert('e');
    s.insert('x');

    return 0;
}
