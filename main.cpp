using namespace std;

template <typename T>
struct Node
        {
    int size;
    T *value;
    Node **child;
    bool isLeaf;
    int count;
public:
    Node(int size)
    {
        count = 0;
        isLeaf = false;
        this->size = size;
        this->value = new T[size];
        this->child = new Node*[size];
        for (int i = 0; i < size; i++) child[i] = nullptr;
    }
    void insert(T value)
    {
        int i = 0;
        while (this->value[i] != nullptr && this->value[i] < value && i < size - 1) i++;
        this->value[i] = value;
        count++;
    }
    Node *findLeaf(Node<T> *root, T value)
    {
        if (root->isLeaf) return root;
        else
        {
            for (int i = 0; i < size - 1; i++)
            {
                if (root->value[i] == nullptr) return findLeaf(root->child[i])
            }
        }
    }
};

template <typename T>
class BTree
{
private:
    Node<T> *root;
    int order;
public:
    BTree(int size)
    {
        root = nullptr;
        order = size;
    }
    void insert(T value){
        if (root == nullptr)
        {
            root = new Node<T>(order);
            root->isLeaf = true;
            root->insert(value);
        }
        else
        {
            Node<T> * currentNode = root;
            while (!currentNode->isLeaf)
            {
                int i;
                for (i = 0; value > currentNode->value[i]; i++)
                {
                    if (i == order) break;
                }
                currentNode = currentNode->child[i];
            }
            currentNode->insert(value);
            if (currentNode->size == order)
            {
                //TODO Divide
                T centerValue = currentNode->value[order/2];

            }
        }
    }
};

int main() {

    return 0;
}
