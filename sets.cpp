#include <cstdlib>
#include <iostream>

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
            std::cout << "Zbior jest pusty." << std::endl;
        } else {
            std::cout << "Zbior zawiera: " << std::endl;
            Number *temp = first;
            while (temp != NULL) {
                std::cout << temp->value << ", ";
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
        Set *unification = new Set;
        Number *temp = first;
        while (temp != NULL) {
            unification->add(temp->value);
            temp = temp->next;
        }

        temp = set->first;
        while (temp != NULL) {
            unification->add(temp->value);
            temp = temp->next;
        }
        return unification;
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
        return intersected;
    }
};

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

int main() {
    Set *set = new Set;

    while (true) {
        std::cout << "Podaj opcje: ";

        int option;
        std::cin >> option;

        switch (option) {
            case 1: {
                int number;
                std::cin >> number;
                set->add(number);
                break;
            }
            case 2: {
                int number;
                std::cin >> number;
                set->remove(number);
                break;
            }
            case 3:
                set->print();
                break;
            case 4:
                std::cout << "Zbior jest: " << (set->isEmpty() ? "pusty" : "niepusty") << std::endl;
                break;
            case 5:
                std::cout << "Wielkosc zbioru: " << set->cardinality() << std::endl;
                break;
            case 6: {
                Set *subSet = new Set;
                subSet->add(1);
                subSet->add(2);
                subSet->add(3);
                std::cout << "Czy ma podzbior (1, 2, 3): " << (set->isSubset(subSet) ? "tak" : "nie") << std::endl;
                break;
            }
            case 7: {
                Set *first = new Set;
                first->add(1);
                first->add(2);
                first->add(3);

                Set *second = new Set();
                second->add(3);
                second->add(4);
                second->add(5);

                Set *unionSet = first->createUnion(second);
                unionSet->print();

                delete first, second, unionSet;
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

                Set *intersectionSet = first->intersection(second);
                intersectionSet->print();

                delete first, second, intersectionSet;
                break;
            }
            default:
                delete set;
                return 0;
        }
    }
}
