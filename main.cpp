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

    void remove(int value) {
        if (first == NULL) return;
        if (first->value == value) {
            if (first->value == NULL) {
                first = NULL;
            } else {
                first = first->next;
            }
            return;
        }
        Number *temp = first;
        while (temp->next != NULL) {
            if (temp->next->value == value) {
                temp->next = temp->next->next;
                break;
            }
            temp = temp->next;
        }
    }

    void print() {
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

    bool isEmpty() {
        return first == NULL;
    }

    long cardinality() {
        if (first == NULL) return 0;
        long sum = 1;

        Number *temp = first;
        while (temp->next != NULL) {
            sum++;
            temp = temp->next;
        }
        return sum;
    }
};

void add(Set *set, int value);

void remove(Set *set, int value);

void print(Set *set);

bool isEmpty(Set *set);

long cardinality(Set *set);

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
            case 2:
                remove(set, 15);
                break;
            case 3:
                print(set);
                break;
            case 4:
                cout << "Zbior jest: " << (isEmpty(set) ? "pusty" : "niepusty") << endl;
                break;
            case 5:
                cout << "Wielkosc zbioru: " << cardinality(set) << endl;
                break;
            default:
                end = true;
                break;
        }
    }
}

void add(Set *set, int value) {
    set->add(value);
}

void remove(Set *set, int value) {
    set->remove(value);
}

void print(Set *set) {
    set->print();
}

bool isEmpty(Set *set) {
    return set->isEmpty();
}

long cardinality(Set *set) {
    return set->cardinality();
}
