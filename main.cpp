#include <iostream>

using namespace std;

template<typename T, int n>
struct Node {
    T *value;
    Node **child;
    int count;
    bool isLeaf;

public:
    Node() {
        count = 0;
        isLeaf = false;
        this->value = new T[n];
        this->child = new Node *[n];
        for (int i = 0; i < n; i++) {
            this->child[i] = NULL;
            this->value[i] = NULL;
        }
    }

    bool isNIL() {
        for (int i = 0; i < n; i++) {
            if (!(this->child[i] == NULL))
                return false;
        }
        return true;
    }

    int addValue(T Value) {
        int i;
        for (i = 0; i < n; i++) {
            if (value[i] == NULL) break;
            if (Value < value[i]) break;
        }

        for (int j = count; j >= i; j--) {
            value[j + 1] = value[j];
        }
        value[i] = Value;
        count++;
        return i;
    }

    Node *findLeaf(Node<T, n> *node, T val) {
        bool flag = false;
        if (node->isLeaf) return node;
        else {
            for (int i = 0; i < count; i++) {
                if (val < node->value[i]) {
                    flag = true;
                    return findLeaf(node->child[i], val);
                }
            }
            if (!flag) return findLeaf(node->child[count], val);
        }
    }

    bool exist(T val) {
        for (int i = 0; i < count; i++) {
            if (val == value[i]) return true;
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

    void Insert(T value) {
        Node<T, n> *leaf = root->findLeaf(root, value);
        leaf->addValue(value);
        if (leaf == this->root)
            split(leaf, true);
        else
            split(leaf, false);

    }

    void split(Node<T, n> *node, bool flag) {
        if (node->count == n) {
            if (flag) {
                Node<T, n> *newRoot = new Node<T, n>;
                Node<T, n> *rightChild = new Node<T, n>;
                T midValue = node->value[n / 2];
                node->value[n / 2] = NULL;
                int j = 0;
                for (int i = n / 2; i < node->count + 1; ++i) {
                    rightChild->child[j] = node->child[i];
                    node->child[i] = NULL;
                    j++;
                }
                for (int i = n / 2 + 1; i < n; i++) {
                    rightChild->addValue(node->value[i]);
                    node->value[i] = NULL;
                    node->count--;
                }
                newRoot->addValue(midValue);
                node->count--;
                rightChild->isLeaf = rightChild->isNIL();
                node->isLeaf = node->isNIL();
                newRoot->child[0] = node;
                newRoot->child[1] = rightChild;
                this->root = newRoot;
            } else {
                T midValue = node->value[n / 2];
                Node<T, n> *parent = findParent(midValue);
                node->value[n / 2] = NULL;
                node->count--;
                int index = parent->addValue(midValue);
                for (int i = parent->count; i >= index + 1; i--) {
                    parent->child[i + 1] = parent->child[i];
                }
                Node<T, n> *newNode = new Node<T, n>;
                for (int i = n / 2 + 1; i < n; i++) {
                    newNode->addValue(node->value[i]);
                    node->value[i] = NULL;
                    node->count--;
                }
                parent->child[index + 1] = newNode;
                newNode->isLeaf = newNode->isNIL();
                if (parent->count == n) {
                    if (parent == root) {
                        split(parent, true);
                    } else {
                        split(parent, false);
                    }
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
                if (value < current->value[i]) {
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

    void traverse(Node<T, n> *root) {
        if (root == NULL) return;
        else {
            int i;
            for (i = 0; i < root->count; i++) {
                cout << root->value[i];
            }
            for (int j = 0; j <= root->count; j++) {
                traverse(root->child[j]);
            }


        }
    }
//        if(root== NULL)
//            return;
//        int i;
//        for(i=0;i<root->count;i++){
//            cout<<root->value[i];
//        }cout<<"\n";
//        for (int j = 0; j <root->count+1; j++) {
//            traverse(root->child[i]);
//        }
//        cout<<endl;

    void print() {
        traverse(root);
    }
};

int main() {
    BTree<char, 5> t;
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.print();

    return 0;
}
