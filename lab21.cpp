//COMSC-210-5068, Lab 21, Yang Liu
#include <iostream>
#include <string> 
#include <cstdlib> 
#include <ctime> 
using namespace std;

const int MIN_GOAT_AGE = 1, MAX_GOAT_AGE = 20; 
const int MIN_LIST_SIZE = 5, MAX_LIST_SIZE = 20; 
const int NAME_COUNT = 15, COLOR_COUNT = 15; 

// Goat Class
class Goat {
private:
    int age;
    string name;
    string color;
    static string names[];
    static string colors[];

public:
    //constructor
    Goat() {
        age = rand() % (MAX_GOAT_AGE - MIN_GOAT_AGE + 1) + MIN_GOAT_AGE;
        name = names[rand() % NAME_COUNT];
        color = colors[rand() % COLOR_COUNT];
    }
    //constructor with parameters
    Goat(int a, string n, string c) : age(a), name(n), color(c) {
        if (a < MIN_GOAT_AGE || a > MAX_GOAT_AGE) {
            cout << "Age " << a << " is invalid! Set to " << MIN_GOAT_AGE << '.' << endl;
            age = MIN_GOAT_AGE;
        }
    }

    int getAge() const { return age; }
    string getName() const { return name; }
    string getColor() const { return color; }
};

string Goat::names[] = {
    "Snowy", "Midnight", "Blossom", "Fluffball", "Bean",
    "Bleater", "Chonk", "Hopper", "Joy", "GoodBoy",
    "Strong", "Lassie", "Rascal", "Sweetie", "Goofy"
};

string Goat::colors[] = {
    "White", "Black", "Brown", "Gray", "Spotted",
    "Yellow", "Beige", "Chestnut", "Cream", "Gold",
    "Red", "Purple", "Blue", "Green", "Pink"
};

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(int value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    DoublyLinkedList list;

    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}