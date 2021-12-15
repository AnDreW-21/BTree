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
            this->child[i] = nullptr;
            this->value[i] = NULL;
        }
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

    void insert(T value) {
        Node<T, n> *leaf = root->findLeaf(root, value);
        leaf->addValue(value);
        if (leaf == this->root)
            split(leaf, -1);
        else
            split(leaf, 0);

    }

    void split(Node<T, n> *node, int flag) {
        if (node->count == n) {
            if (flag == -1) {
                Node<T, n> *newRoot = new Node<T, n>;
                Node<T, n> *rightChild = new Node<T, n>;
                T midValue = node->value[n / 2];
                node->value[n / 2] = NULL;
                for (int i = n / 2 + 1; i < n; i++) {
                    rightChild->addValue(node->value[i]);
                    node->value[i] = NULL;
                    node->count--;
                }
                newRoot->addValue(midValue);
                node->count--;
                rightChild->isLeaf = true;
                node->isLeaf = true;
                newRoot->child[0] = node;
                newRoot->child[1] = rightChild;
                this->root = newRoot;
            } else {
                T midValue = node->value[n / 2];
                Node<T, n> *parent = findParent(midValue);
                node->value[n / 2] = NULL;
                node->count--;
                int index = parent->addValue(midValue);
                for (int i = index + 1; i < parent->count; i++) {
                    parent->child[i + 1] = parent->child[i];
                }
                Node<T, n> *newNode = new Node<T, n>;
                newNode->isLeaf = true;
                for (int i = n / 2 + 1; i < n; i++) {
                    newNode->addValue(node->value[i]);
                    node->value[i] = NULL;
                    node->count--;
                }
                parent->child[index + 1] = newNode;
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

    void traverse(Node<T,n> *root) {
        if(root== nullptr)
            return;
        int i;
        for(i=0;i<root->count;i++){
            cout<<root->value[i];
        }cout<<"\n";
        for (int j = 0; j <root->count+1; j++) {
            traverse(root->child[i]);
        }
        cout<<endl;
    }
    void print(){
        traverse(root);
    }
};

int main() {
    BTree<char, 3> s;
    s.insert('x');
    s.insert('f');
    s.insert('g');
    s.insert('d');
    s.insert('e');
    s.insert('z');
    s.print();

    return 0;
}
