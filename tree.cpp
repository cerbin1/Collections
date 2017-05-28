#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <iomanip>

struct Node {
    int value;
    Node *parent = NULL;
    Node *leftChild = NULL;
    Node *rightChild = NULL;

    std::string hint;

    Node(int _value) {
        value = _value;
    }

    Node(int _value, Node *_parent) {
        value = _value;
        parent = _parent;
    }

    ~Node() {
        delete leftChild;
        delete rightChild;
    }

    void replaceInParentWith(Node *node) {
        if (parent != NULL) {
            if (parent->leftChild == this) {
                parent->leftChild = node;
            }
            if (parent->rightChild == this) {
                parent->rightChild = node;
            }
        }
    }
};

struct Tree {
    Node *root;

    ~Tree() {
        delete root;
    }

    void addValue(int value) {
        if (root == NULL) {
            root = new Node(value);
        } else {
            addValueToNode(root, value);
        }
    }

    void removeValue(int value) {
        if (root == NULL) return;

        Node *toRemove = search(value);
        if (toRemove == NULL) return;

        if (toRemove == root) {
            root = NULL;
            return;
        }

        toRemove->replaceInParentWith(NULL);

        if (toRemove->leftChild != NULL) {
            iterateAndAddTo(toRemove->leftChild, toRemove->parent);
        }
        if (toRemove->rightChild != NULL) {
            iterateAndAddTo(toRemove->rightChild, toRemove->parent);
        }

        delete toRemove;
    }

    void iterateAndAddTo(Node *start, Node *destination) {
        if (start->leftChild != NULL) {
            iterateAndAddTo(start->leftChild, destination);
        }

        addValueToNode(destination, start->value);

        if (start->rightChild != NULL) {
            iterateAndAddTo(start->rightChild, destination);
        }
    }

    Node *search(int value) {
        if (root == NULL) {
            return NULL;
        }
        return searchFromNode(root, value);
    }

    Node *findMax() {
        if (root == NULL) {
            return NULL;
        }
        return findMaxFromNode(root);
    }

    void transplant(Node *source, Node *destination) {
        if (source == NULL || destination == NULL) return;

        if (destination == root) {
            root = source;
        } else {
            destination->replaceInParentWith(source);
            source->parent = destination->parent;
        }
        delete destination;
    }

    void print() {
        if (root != NULL) {
            printNode(root);
        }
    }

    void visualize() {
        if (root != NULL) {
            std::cout << std::endl;
            visualizeNode(root, 0);
            std::cout << std::endl;
        }
    }

    Node *findPredecessor(const int value) {
        if (root == NULL) {
            return NULL;
        }
        Node *lastBiggest = NULL;
        findPredecessorFromNode(root, &lastBiggest, value);
        return lastBiggest;
    }

    void findPredecessorFromNode(Node *start, Node **lastBiggest, const int value) {
        if (start == NULL) {
            return;
        }

        if (value <= start->value) {
            findPredecessorFromNode(start->leftChild, lastBiggest, value);
            return;
        }

        if (value > start->value) {
            if (*lastBiggest == NULL) {
                *lastBiggest = start;
            } else {
                if ((*lastBiggest)->value < start->value) {
                    *lastBiggest = start;
                }
            }
            findPredecessorFromNode(start->rightChild, lastBiggest, value);
        }
    }

    void addValueToNode(Node *start, int value) {
        if (value < start->value) {
            if (start->leftChild == NULL) {
                start->leftChild = new Node(value, start);
            } else {
                addValueToNode(start->leftChild, value);
            }
        } else {
            if (start->rightChild == NULL) {
                start->rightChild = new Node(value, start);
            } else {
                addValueToNode(start->rightChild, value);
            }
        }
    }

    void printNode(Node *start) {
        if (start->leftChild != NULL) {
            printNode(start->leftChild);
        }

        std::cout << start->value << ", ";

        if (start->rightChild != NULL) {
            printNode(start->rightChild);
        }
    }

    Node *searchFromNode(Node *start, int value) {
        if (start->value == value) {
            return start;
        }

        if (value < start->value && start->leftChild != NULL) {
            return searchFromNode(start->leftChild, value);
        }

        if (value > start->value && start->rightChild != NULL) {
            return searchFromNode(start->rightChild, value);
        }

        return NULL;
    }

    Node *findMaxFromNode(Node *node) {
        if (node->rightChild != NULL) {
            return findMaxFromNode(node->rightChild);
        }
        return node;
    }

    void visualizeNode(Node *node, int indent) {
        if (node != NULL) {
            if (node->rightChild != NULL) {
                visualizeNode(node->rightChild, indent + 4);
            }
            if (indent > 0) {
                std::cout << std::setw(indent) << ' ';
            }
            if (node->rightChild != NULL) {
                std::cout << " /\n" << std::setw(indent) << ' ';
            }
            std::cout << node->value;
            if (!node->hint.empty()) {
                std::cout << ": " << node->hint;
            }
            std::cout << std::endl << " ";
            if (node->leftChild != NULL) {
                std::cout << std::setw(indent) << ' ' << " \\" << std::endl;
                visualizeNode(node->leftChild, indent + 4);
            }
        }
    }
};

int randomBetween(int bound1, int bound2) {
    int range = abs(bound1 - bound2);
    return std::min(bound1, bound2) + rand() % range;
}

int main() {
    Tree *tree = new Tree();;
    std::cout << "Wygenerujemy testowe drzewo. Podaj ilosc wezlow:  ";
    int size;
    std::cin >> size;

    for (int i = 0; i < size; i++) {
        int randomValue = randomBetween(1, 100);
        tree->addValue(randomValue);
    }

    while (true) {
        std::cout << std::endl << "- - - - - - - - - " << std::endl;
        std::cout << "Podaj opcje: " << std::endl;
        std::cout << " 1) Dodaj liczbe..." << std::endl;
        std::cout << " 2) Usun liczbe..." << std::endl;
        std::cout << " 3) Pokaz liczby" << std::endl;
        std::cout << " 4) Pokaz drzewo" << std::endl;
        std::cout << " 5) Wyszukaj (referencje)..." << std::endl;
        std::cout << " 6) Przenies..." << std::endl;
        std::cout << " 7) Najwyzsza wartosc" << std::endl;
        std::cout << " 8) Najwyzsza wartosc, mniejsza niz..." << std::endl;

        int choice;
        std::cin >> choice;
        int value;
        switch (choice) {
            case 1:
                std::cout << "Podaj wartosc do dodania:";
                std::cin >> value;
                tree->addValue(value);
                break;

            case 2:
                std::cout << "Podaj wartosc do usuniecia:";
                std::cin >> value;
                tree->removeValue(value);
                break;

            case 3:
                std::cout << "Wartosci drzewa: " << std::endl;
                tree->print();
                std::cout << std::endl;
                break;

            case 4:
                std::cout << "Wizualizacja drzewa: " << std::endl;
                tree->visualize();
                break;

            case 5: {
                std::cout << "Podaj wartosc do wyszukania: ";
                std::cin >> value;
                Node *node = tree->search(value);
                if (node != NULL) {
                    node->hint = "I found it";
                }
                std::cout << "Referencja klucza: " << node << std::endl;
                break;
            }

            case 6: {
                std::cout << "Podaj wartosc ktora chcesz przeniesc: ";
                std::cin >> value;
                Node *source = tree->search(value);

                std::cout << "Podaj wartosc DO ktorej chcesz przeniesc: ";
                std::cin >> value;
                Node *destination = tree->search(value);

                tree->transplant(source, destination);
                break;
            }

            case 7: {
                Node *maxNode = tree->findMax();
                if (maxNode == NULL) {
                    std::cout << "Max wartosc: Nie istnieje" << std::endl;
                } else {
                    std::cout << "Max wartosc: " << maxNode->value << std::endl;
                }
                break;
            }

            case 8: {
                std::cout << "Podaj wartosc do wyszkuania:";
                std::cin >> value;

                Node *maxNodePredecessor = tree->findPredecessor(value);

                if (maxNodePredecessor == NULL) {
                    std::cout << "Najwiekszy element, mniejszy od podanej wartosci: "
                              << "Nie istnieje"
                              << std::endl;
                } else {
                    std::cout << "Najwiekszy element, mniejszy od podanej wartosci: "
                              << maxNodePredecessor->value
                              << std::endl;
                }
                break;
            }

            default:
                std::cout << "Nieznana wartosc: " << choice << ". Zamykanie aplikacji";
                delete tree;
                return 0;
        }
    }
}
