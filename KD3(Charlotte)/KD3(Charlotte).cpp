#include <iostream>
#include <string> // string.compare(string compareTo) -> (string > compareTo) = -1, (string == compareTo) = 0, (string < compareTo) = 1 \
                     string.substr(pos, length) -> ("abcdef", 1, 2) = "bc", ("Jonaitis", 0, 3) = "Jon"
using namespace std;

struct Node {
    string data;
    Node* prev;
    Node* next;

    Node(string val) :data(val), prev(nullptr), next(nullptr) {} // Parameterised constructor with default argument
};

struct TreeNode {
    string data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(string val = "") :data(val), left(nullptr), right(nullptr) {} 
};

class Queue {
    Node* start;
    Node* end;

public:

    Queue() :start(nullptr), end(nullptr) {}

    void insert(string val) {
        Node* new_node = new Node(val); // make a new node


        if (start == nullptr) { // If list is empty, make the new node the head
            start = end = new_node;
            return;
        }

        new_node->next = start;
        start = new_node;
    }

    string remove() {
        Node* temp = start;

        start = temp->next;

        string data = temp->data;

        delete temp;

        return data;
    }

    void display() {
        Node* temp = start;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class Dequeue {
    Node* start;
    Node* end;

public:

    Dequeue() :start(nullptr), end(nullptr) {}

    void insertStart(string val) {
        Node* new_node = new Node(val); // make a new node


        if (start == nullptr) { // If list is empty, make the new node the head
            start = end = new_node;
            return;
        }

        new_node->next = start;
        start->prev = new_node;
        start = new_node;
    }

    void insertEnd(string val) {
        Node* new_node = new Node(val); // make a new node


        if (end == nullptr) { // If list is empty, make the new node the head
            start = end = new_node;
            return;
        }

        new_node->prev = end;
        end->next = new_node;
        end = new_node;
    }

    string removeStart() {
        Node* temp = start;

        start = temp->next;

        string data = temp->data;

        delete temp;

        return data;
    }

    string removeEnd() {
        Node* temp = end;

        end = temp->prev;

        string data = temp->data;

        delete temp;

        return data;
    }

    void display() {
        Node* temp = start;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class BinaryTree {
    TreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    void insert(string val) {
        TreeNode* new_node = new TreeNode(val); // make a new node


        if (root == nullptr) { // If tree is empty, make the new node the root
            root = new_node;
            return;
        }

        TreeNode* temp = root;
        while (temp != new_node) {
            if (temp->data.compare(val) == -1) { // If the new value is smaller than the currently selected node, go to the left, otherwise, go to the right
                if (temp->left == nullptr) // If the spot is free, insert the new element there, if not, continue checking
                    temp->left = new_node;

                temp = temp->left;
            } else {
                if (temp->right == nullptr)
                    temp->right = new_node;

                temp = temp->right;
            }
        }
    }

    TreeNode* findNode(string value) {
        TreeNode* temp = root;

        while (temp->data.compare(value) != 0) {
            if (temp->data.compare(value) == -1) { // If the new value is smaller than the currently selected node, go to the left, otherwise, go to the right
                temp = temp->left;
            }
            else {
                temp = temp->right;
            }
        }

        return temp;
    }

    void remove(string value) {
        TreeNode* temp = findNode(value);

        if (temp->left == nullptr) { // if there is no element to replace with, just remove the element without changing the tree
            if (temp->right != nullptr) { // if the element has a child on its right, move it to the deleted element's place
                TreeNode* remove = temp->right;

                temp->data = remove->data;
                temp->left = remove->left;
                temp->right = remove->right;

                delete remove;

                return;
            }

            delete temp;

            return;
        }

        TreeNode* replaceWith = temp->left; // go left and all the way to the right(quickest way to find the best substitute for the deleted value)
        if (replaceWith->right != nullptr) {
            while (replaceWith->right->right != nullptr) {
                replaceWith = replaceWith->right;
            }

            if (replaceWith->right->left != nullptr) { // if the replacement value has a child to the left, make sure to place it instead of the element you're replacing the deleted element with(it's a bit of a confusing line, I know)
                TreeNode* temp2 = replaceWith->right;

                replaceWith->right = temp2->left;

                replaceWith = temp2;
            }
        }

        temp->data = replaceWith->data;

        delete replaceWith;
    }

    void display() {
        display(root);

        cout << endl;
    }

    void addToDequeue(Dequeue& dequeue) { // add all surnames starting with "Jon" to the start and all surnames starting with "Pet" to the end of the specified dequeue
        addToDequeue(dequeue, root);
    }

    void addToQueueAndRemoveFromTree(Queue& queue) { // add all surnames starting with "Ant" and remove them from the tree
        addToQueueAndRemoveFromTree(queue, root);
    }

private:
    void addToDequeue(Dequeue& dequeue, TreeNode* temp) {
        if (temp == nullptr)
            return;

        addToDequeue(dequeue, temp->left);
        if (temp->data.substr(0, 3) == "Jon") // if the surname starts with "Jon", add it to the start of the dequeue
            dequeue.insertStart(temp->data);

        if (temp->data.substr(0, 3) == "Pet") // if the surname starts with "Pet", add it to the end of the dequeue
            dequeue.insertEnd(temp->data);
        addToDequeue(dequeue, temp->right);
    }

    void addToQueueAndRemoveFromTree(Queue& queue, TreeNode* temp) {
        if (temp == nullptr)
            return;

        addToQueueAndRemoveFromTree(queue, temp->left);

        if (temp->data.substr(0, 3) == "Ant") {
            queue.insert(temp->data);
        }

        addToQueueAndRemoveFromTree(queue, temp->right);

        if (temp->data.substr(0, 3) == "Ant") {
            remove(temp->data);
        }
    }

    void display(TreeNode* temp) {
        if (temp == nullptr)
            return;

        display(temp->left);
        cout << temp->data << " ";
        display(temp->right);
    }
};

int main() {
    Queue q;
    Dequeue d;
    BinaryTree t;

    int N;

    cout << "Enter the number of elements in the list: "; // Get the number of elements in the list
    cin >> N;


    for (int i = 0; i < N; ++i) { // Inserting elements based on user input
        string val;
        cout << "Enter element " << i + 1 << ": ";
        cin >> val;
        t.insert(val);
    }

    cout << "Current tree: ";
    t.display();

    //a
    //b
    t.addToDequeue(d);

    //c
    t.addToQueueAndRemoveFromTree(q);

    //d
    cout << "Resulting queue and dequeue:" << endl;
    q.display();
    d.display();
}
