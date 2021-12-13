#include <iostream>

using namespace std;

template<typename T ,int n>
struct Node {
    int size;
    T *value;
    Node **child;
    int count;
public:
    Node() {
        count = 0;
        isLeaf = false;
        this->size = n;
        this->value = new T[size];
        this->child = new Node *[size];
        for (int i = 0; i < size; i++) child[i] = nullptr;
    }

    void insert(T value) {
        int i = 0;
        while (this->value[i] != nullptr && this->value[i] < value && i < size - 1) i++;
        this->value[i] = value;
        count++;
    }

    Node *findLeaf(Node<T,n> *root) {
        if (root->isLeaf) return root;
        else {
            for (int i = 0; i < size - 1; i++) {
                if (!root->isLeaf) return findLeaf(root->child[i]);
            }
        }
    }

    bool isLeaf;
};

template<typename T,int n>
class BTree {
private:
    Node<T,n> *root;
    int order;
public:
    BTree() {
        root = nullptr;
        order = n;
    }

    void insert(T value) {
        if (root == nullptr) {
            root = new Node<T,n>(order);
            root->isLeaf = true;
            root->insert(value);
        } else {
            Node<T,n> *currentNode = root;
            while (!currentNode->isLeaf) {
                int i;
                for (i = 1; value > currentNode->value[i]; i++) {
                    if (i == order) break;
                }
                currentNode = currentNode->child[i];
            }
            currentNode->insert(value);
            if (currentNode->size == order) {
                if (currentNode == root)
                    split(currentNode, true);
                else
                    split(currentNode, false);
            }
        }
    }

    void split(Node<T,n> node, bool isRoot) {
        int midElem;
        Node<T,n> *dummy1, *dummy2;
        dummy1 = new Node<T,n>(order);
        dummy1->isleaf = true;
        if (isRoot) {
            dummy2 = new Node<T,n>(order);
            midElem = node->values[(order / 2) - 1];
            node->values[(order / 2) - 1] = 0;
            node->count--;
            dummy2->isleaf = false;
            node->isleaf = true;
            int i;
            for (i = order / 2; i < order; i++) {
                dummy1->value[i - (order / 2)] = node.value[i];
                dummy1->child[i - (order / 2)] = node.child[i];
                node->value[i] = nullptr;
                dummy1->count++;
                node->count--;
            }
            for (i = 0; i < order; i++) {
                node->child[i] = nullptr;
            }
            dummy2=node.value[0]=midElem;
            dummy2->child[dummy2->count] = node;
            dummy2->child[dummy2->count+1] = dummy1;
            dummy2=node->count++;
            root=dummy2;
        }
        //TODO split for any node not root
        //


    }
};

int main() {
    BTree<int,5> s;


    return 0;
}
