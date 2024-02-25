// BinaryTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

class Queue {
public:
    QueueItem* start;
    QueueItem* end;
    int size;

    void InsertValue(string value) {
        QueueItem* newValue = new QueueItem();

        newValue->value = value;
        if(end != nullptr) end->nextValue = newValue;

        if (size == 0)
            start = newValue;
        end = newValue;

        size++;
    }

    string ShiftValue() {
        if (size == 0)
            return "";

        QueueItem* old = start;
        string value = old->value;

        start = old->nextValue;

        free(old);

        size--;

        return value;
    }

    void display() {
        QueueItem* current = start;

        while (current != nullptr) {
            cout << current->value << endl;
            current = current->nextValue;
        }
    }
};

class DeQueue {
public:
    DeQueue() {
        begin = CreateElement("");
        stop = CreateElement("");

        begin->nextValue = stop;
        stop->prevValue = begin;
    }

    DeQueueItem* begin;
    DeQueueItem* stop;

    void InsertIntoStart(string value) {
        DeQueueItem* newValue = CreateElement(value);

        newValue->nextValue = begin->nextValue;
        newValue->prevValue = begin;
        begin->nextValue->prevValue = newValue;
        begin->nextValue = newValue;
    }

    void InsertIntoEnd(string value) {
        DeQueueItem* newValue = CreateElement(value);

        newValue->prevValue = stop->prevValue;
        newValue->nextValue = stop;
        stop->prevValue->nextValue = newValue;
        stop->prevValue = newValue;
    }

    string ShiftFromStart() {
        if (begin->nextValue == stop)
            return "";

        DeQueueItem* old = begin->nextValue;
        string value = old->value;

        begin->nextValue = old->nextValue;
        begin->nextValue->prevValue = begin;

        free(old);

        return value;
    }

    string ShiftFromEnd() {
        if (stop->prevValue == begin)
            return "";

        DeQueueItem* old = stop->prevValue;
        string value = old->value;

        stop->prevValue = old->prevValue;
        stop->prevValue->nextValue = stop;

        free(old);

        return value;
    }

    void display() {
        DeQueueItem* current = begin;

        while (current->nextValue != stop) {
            current = current->nextValue;
            cout << current->value << endl;
        }
    }

private:
    DeQueueItem* CreateElement(string value) {
        DeQueueItem* item = new DeQueueItem();

        item->value = value;

        item->nextValue = item->prevValue = nullptr;

        return item;
    }
};

class BinaryTree {
public:
    TreeItem* root;

    void insertItem(string value) {
        TreeItem* newItem = new TreeItem();
        newItem->value = value;

        // assign value to the root if tree is empty
        if (root == nullptr) { 
            root = newItem;

            return;
        } 

        TreeItem* current = root;

        while (current != newItem) {
            if (newItem->value[0] < current->value[0]) {
                if (current->left == nullptr) {
                    current->left = newItem;
                }

                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = newItem;
                }

                current = current->right;
            }
        }
    }

    TreeItem* findItem(string value) {
        TreeItem* current = root;

        while (current->value != value) {
            if (value[0] < current->value[0]) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        return current;
    }

    void removeItem(string value) {
        for
    }
};

struct DeQueueItem {
    string value;
    DeQueueItem* prevValue;
    DeQueueItem* nextValue;
};

struct QueueItem {
    string value;
    QueueItem* nextValue;
};

struct TreeItem {
    string value;
    TreeItem* left;
    TreeItem* right;
};

int main() {
    
}
