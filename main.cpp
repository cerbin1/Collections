#include <cstdlib>
#include <iostream>

using namespace std;

struct Number {
    int value;
    Number *next;

    Number() {
        next = NULL;
    }
};

struct Set {
    Number *first = NULL;

    void add(int value) {
        Number *newNumber = new Number();
        newNumber->value = value;
        if (first == NULL) {
            first = newNumber;
        } else if (isNotADuplication(value)) {
            Number *temp;
            temp = first;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNumber;
            newNumber->next = NULL;
        }
    }

    bool isNotADuplication(int value) {
        if (first->value == value) {
            return false;
        }
        Number *temp = first;
        while (temp->next != NULL) {
            if (temp->value == value) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    void display() {
        if (first != NULL) {
            Number *temp = first;
            cout << "Wypisuje: " << endl;
            while (true) {
                cout << temp->value << endl;
                temp = temp->next;
                if (temp == NULL) {
                    break;
                }
            }
        }
    }
};

void add(Set *set, int value);

void print(Set *set);

int main() {
    Set *set = new Set;

    bool end = false;
    int option;
    while (!end) {
        cout << "Podaj opcje: ";
        cin >> option;
        switch (option) {
            case 1:
                add(set, 15);
                break;
            case 3:
                print(set);
                break;
            default:
                end = true;
                break;
        }
    }
}

void print(Set *set) {
    set->display();
}

void add(Set *set, int value) {
    set->add(value);
}