#include <cstdlib>
#include <iostream>

using namespace std;

struct Number {
    int value;
    Number *next = NULL;
};

struct Set {
    Number *first = NULL;

    void add(int value) {
        if (has(value)) {
            return;
        }
        Number *newNumber = new Number();
        newNumber->value = value;
        if (isEmpty()) {
            first = newNumber;
        } else {
            Number *temp;
            temp = first;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNumber;
            newNumber->next = NULL;
        }
    }

    void remove(int value) {
        if (isEmpty()) return;
        if (first->value == value) {
            if (first->next == NULL) {
                first = NULL;
            } else {
                first = first->next;
            }
        } else {
            Number *temp = first;
            while (temp->next != NULL) {
                if (temp->next->value == value) {
                    temp->next = temp->next->next;
                    break;
                }
                temp = temp->next;
            }
        }
    }

    void print() {
        if (isEmpty()) {
            cout << "Nie ma elementow do wypisania." << endl;
        } else {
            cout << "Wypisuje: " << endl;
            Number *temp = first;
            while (temp != NULL) {
                cout << temp->value << endl;
                temp = temp->next;
            }
        }
    }

    bool isEmpty() {
        return first == NULL;
    }

    long cardinality() {
        if (isEmpty()) return 0;
        long sum = 1;

        Number *temp = first;
        while (temp->next != NULL) {
            sum++;
            temp = temp->next;
        }
        return sum;
    }

    bool isSubset(Set *subset) {
        if (subset->isEmpty()) {
            return true;
        }

        Number *temp = subset->first;
        while (temp != NULL) {
            if (!has(temp->value)) return false;
            temp = temp->next;
        }
        return true;
    }

    bool has(int value) {
        Number *temp = first;
        while (temp != NULL) {
            if (temp->value == value) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    Set *createUnion(Set *set) {
        Number *temp = set->first;
        while (temp != NULL) {
            add(temp->value);
            temp = temp->next;
        }
        return this;
    }

    Set *intersection(Set *set) {
        Set *intersected = new Set;

        Number *temp = first;
        while (temp != NULL) {
            if (set->has(temp->value)) {
                intersected->add(temp->value);
            }
            temp = temp->next;
        }
        cout << "Wspolna czesc listy i ciagu: " << endl;
        intersected->print();
        return intersected;
    }
};

void add(Set *set, int value);

void remove(Set *set, int value);

void print(Set *set);

bool isEmpty(Set *set);

long cardinality(Set *set);

bool isSubset(Set *subset, Set *set);

Set *createUnion(Set *first, Set *second);

Set *intersection(Set *first, Set *second);

int main() {
    Set *set = new Set;

    bool end = false;
    int option;
    while (!end) {
        int number;

        cout << "Podaj opcje: ";
        cin >> option;
        switch (option) {
            case 1:
                cin >> number;
                add(set, number);
                break;
            case 2:
                number;
                cin >> number;
                remove(set, number);
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
            case 6: {
                Set *subSet = new Set;
                subSet->add(1);
                subSet->add(2);
                subSet->add(3);
                cout << "Czy jest podzbiorem zbioru (1, 2, 3)" << (isSubset(set, subSet) ? "tak" : "nie") << endl;
                break;
            }
            case 7: { // TODO Add getting numbers to two sets from user
                Set *subset = new Set();
                Set *first = new Set;
                first->add(1);
                first->add(2);
                first->add(3);
                Set *second = new Set();
                second->add(3);
                second->add(4);
                second->add(5);
                subset = createUnion(first, second);
                subset->print();
                delete first;
                delete second;
                delete subset;
                break;
            }
            case 8: {
                Set *first = new Set;
                first->add(1);
                first->add(2);
                first->add(3);
                first->add(4);
                Set *second = new Set;
                second->add(5);
                second->add(1);
                second->add(4);
                second->add(15);
                intersection(first, second)->print(); // TODO add getting data from input
                delete first, second;
                break;
            }
            default:
                end = true;
                delete set;
                break;
        }
    }
}

bool isSubset(Set *set, Set *subset) {
    return set->isSubset(subset);
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

Set *createUnion(Set *first, Set *second) {
    return first->createUnion(second);
}

Set *intersection(Set *first, Set *second) {
    return first->intersection(second);
}
