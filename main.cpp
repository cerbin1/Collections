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
            if (first->next == NULL) {
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

    bool isSubset(Set *subset) {
        if (subset->first != NULL) {
            Number *temp = subset->first;
            do {
                if (!has(temp->value)) {
                    return false;
                }
                temp = temp->next;
            } while (temp->next != NULL);
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

    Set *unionn(Set *set) {
        Number *temp = set->first;
        while (temp != NULL) {
            add(temp->value);
            temp = temp->next;
        }
        return this;
    }
};

void add(Set *set, int value);

void remove(Set *set, int value);

void print(Set *set);

bool isEmpty(Set *set);

long cardinality(Set *set);

bool isSubset(Set *subset, Set *set);

Set *unionn(Set *first, Set *second);

int main() {
    Set *set = new Set;

    bool end = false;
    int option;
    while (!end) {
        cout << "Podaj opcje: ";
        cin >> option;
        switch (option) {
            case 1:
                int number;
                cin >> number;
                add(set, number);
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
            case 6: {
                Set *subSet = new Set;
                subSet->add(1);
                subSet->add(2);
                subSet->add(3);
                cout << "Czy jest podzbiorem zbioru (1, 2, 3)" << (isSubset(set, subSet) ? "tak" : "nie") << endl;
                break;
            }
            case 7: {
                Set *subset = new Set();
                Set *first = new Set;
                first->add(1);
                first->add(2);
                first->add(3);
                Set *second = new Set();
                second->add(3);
                second->add(4);
                second->add(5);
                subset = unionn(first, second);
                subset->print();
                delete first;
                delete second;
                delete subset;
                break;
            }
            default:
                end = true;
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

Set *unionn(Set *first, Set *second) {

    return first->unionn(second);
}
