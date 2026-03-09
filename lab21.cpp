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
        Goat data;
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
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

    void push_back(Goat value) {
        Node* newNode = new Node(value);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty" << endl;
            return;
        }
        while (current) {
            cout << "    "  << current->data.getName() << " (" 
                 << current->data.getColor() << ", " 
                 << current->data.getAge() << ")" << endl;
            current = current->next;
        }
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty" << endl;
            return;
        }
        while (current) {
            cout << "    "  << current->data.getName() << " (" 
                 << current->data.getColor() << ", " 
                 << current->data.getAge() << ")" << endl;
            current = current->prev;
        }
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
    srand(time(0));

    DoublyLinkedList list;
    int randomSize = rand() % (MAX_LIST_SIZE - MIN_LIST_SIZE + 1) + MIN_LIST_SIZE;

    // Add random Goats use default constructor
    for (int i = 0; i < randomSize; ++i) {
        list.push_back(Goat());
    }

    // Add a custom Goat with parameterized constructor
    cout << "--- Add a custom goat (parameterized constructor) ---" << endl;
    Goat customGoat(5, "Luna", "Silver");
    list.push_front(customGoat);

    // Print results
    cout << "Forward: " << endl;
    list.print();

    cout << endl;

    cout << "Backward: " << endl;
    list.print_reverse();

    return 0;
}