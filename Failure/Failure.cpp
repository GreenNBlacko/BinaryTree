#include <iostream>

using namespace std;

struct Node {
    Node(int value) {
        data = value;
    }

    int data;
    Node* next;
};

struct BiNode {
    BiNode(int value) {
        data = value;
    }

    int data;
    BiNode* prev;
    BiNode* next;
};

class CircularLinkedList {
public:
    Node* start = nullptr;
    Node* end = nullptr;

    void Insert(int value) {
        Node* newValue = new Node(value);

        if (end != nullptr)
            end->next = newValue;

        newValue->next = start;
        end = newValue;

        if (start == nullptr)
            start = newValue;
    }

    int RemoveAfter(Node* node) {
        Node* temp = node->next;

        node->next = temp->next;

        int value = temp->data;

        delete temp;

        return value;
    }

    void display() {
        Node* current = start;

        cout << current->data << " ";

        while (current != end) {
            current = current->next;

            cout << current->data << " ";
        }

        cout << endl;
    }
};

class BiCircularLinkedList {
public:
    BiNode* start = nullptr;
    BiNode* end = nullptr;

    void InsertStart(int value) {
        BiNode* newValue = new BiNode(value);

        if (start != nullptr)
            start->prev = newValue;

        if (end != nullptr)
            end->next = newValue;

        newValue->prev = end;
        newValue->next = start;
        start = newValue;

        if (end == nullptr)
            end = newValue;
    }

    void InsertEnd(int value) {
        BiNode* newValue = new BiNode(value);

        if (start != nullptr)
            start->prev = newValue;

        if (end != nullptr)
            end->next = newValue;

        newValue->prev = end;
        newValue->next = start;
        end = newValue;

        if (start == nullptr)
            start = newValue;
    }

    void InsertBefore(int value, BiNode* node) {
        if (start == nullptr || end == nullptr || node == start)
            InsertStart(value);

        BiNode* newValue = new BiNode(value);

        newValue->next = node;
        newValue->prev = node->prev;
        node->prev->next = newValue;
        node->prev = newValue;
    }

    void InsertAfter(int value, BiNode* node) {
        if (start == nullptr || end == nullptr || node == end)
            InsertEnd(value);

        BiNode* newValue = new BiNode(value);

        newValue->prev = node;
        newValue->next = node->next;
        node->next->prev = newValue;
        node->next = newValue;
    }

    int RemoveStart() {
        BiNode* temp = start;

        int value = temp->data;

        end->next = start->next;
        start->next->prev = end;

        delete temp;

        return value;
    }

    int RemoveEnd() {
        BiNode* temp = end;

        int value = temp->data;

        start->prev = end->prev;
        end->prev->next = start;

        delete temp;

        return value;
    }

    int Remove(BiNode* node) {
        if (node == start)
            return RemoveStart();
        if (node == end)
            return RemoveEnd();

        node->prev->next = node->next;
        node->next->prev = node->prev;

        int value = node->data;

        delete node;

        return value;
    }

    BiNode* Max() {
        BiNode* current = start;

        BiNode* max = current;

        while (current != end) {
            current = current->next;

            if (current->data > max->data)
                max = current;
        }

        return max;
    }

    double Average() {
        BiNode* current = start;

        if (current == nullptr)
            return 0;

        int count = 1;
        double sum = current->data;

        while (current != end) {
            current = current->next;

            sum += current->data;
            count++;
        }

        return sum / count;
    }

    BiNode* ElementAt(int index) {
        BiNode* current = start;

        for (int i = 0; i < index + 1 && current != end; i++)
            current = current->next;

        return current;
    }

    BiNode* Find(int value) {
        BiNode* current = start;

        while (current->data != value && current != end)
            current = current->next;

        return current;
    }

    BiNode* FindLast(int value) {
        BiNode* item;
        BiNode* current = item = start;

        while (current != end) {
            current = current->next;

            if (current->data == value)
                item = current;
        }

        return item;
    }

    void display() {
        BiNode* current = start;

        cout << current->data << " ";

        while (current != end) {
            current = current->next;

            cout << current->data << " ";
        }

        cout << endl;
    }
};

int main() {
    BiCircularLinkedList list;
    CircularLinkedList list2;

    char choice;
    bool running = true;

    while (running) {
        cout << "Rinkites veiksma:\n";
        cout << "a. Ivedimas\n";
        cout << "b. Iterpimas pries nurodyta elementa\n";
        cout << "c. Pasalinimas\n";
        cout << "d. Didziausio elemento radimas\n";
        cout << "e. Visi skaiciai nuo paskutinio 0 i vienkrypti sarasa\n";
        cout << "f. Apskaičiuoja kiek elementu yra didesniu uz saraso vidurki\n";
        cout << "g. Pasalina visus elementus tarp treciojo ir priespaskutinio ir juos atspausdina\n";
        cout << "h. Iseiti\n";

        cin >> choice;

        switch (choice) {
        default:
            cout << "Netinkamas pasirinkimas. Bandykite dar kartą." << endl;
            break;

        case 'a': {
            int value;
            cout << "Iveskite skaičiu: ";
            cin >> value;
            list.InsertEnd(value);
            cout << "Sarasas po įterpimo: ";
            list.display();
            break;
        }
            
        case 'b': {
            int newValue, target;
            cout << "Iveskite naują skaičiu: ";
            cin >> newValue;
            cout << "Iveskite norimą vietą pries kuria iterpti: ";
            cin >> target;
            list.InsertBefore(newValue, list.ElementAt(target));
            cout << "Sarašas po iterpimo: ";
            list.display();
            break;
        }
            
        case 'c': {
            int valueToRemove;
            cout << "Iveskite skaiciu, kuri norite pasalinti: ";
            cin >> valueToRemove;
            list.Remove(list.Find(valueToRemove));
            cout << "Sarasas po pasalinimo: ";
            list.display();
            break;
        }
            
        case 'd': {
            cout << "Didziausias skaicius sarase: " << list.Max()->data << endl;
            break;
        }
            
        case 'e': {
            BiNode* item = list.FindLast(0);

            while (item != list.end) {
                item = item->next;

                list2.Insert(item->data);
            }

            cout << "Sarasas po perkelimo: ";
            list2.display();
            break;
        }
            
        case 'f': {
            double avg = list.Average();

            Node* current = list2.start;

            if (current == nullptr)
                continue;

            int count = (current->data > avg ? 1 : 0);

            while (current != list2.end) {
                current = current->next;

                count += (current->data > avg ? 1 : 0);
            }

            cout << "Elementy, didesniu uz vidurki, kiekis: " << count << endl;
            break;
        }
            
        case 'g': {
            cout << "Elementai tarp treciojo ir priespaskutinio elemento: ";
            Node* current = list2.start->next->next;

            while (current->next != list2.end) {
                cout << list2.RemoveAfter(current) << " ";
            }
            cout << endl;
            break;
        }
            
        case 'h': {
            running = false;
            break;
        }
        }
    }

    return 0;
}


