#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <iomanip>

struct Node {
    int value;
    struct Node *parent = NULL;
    struct Node *leftChild = NULL;
    struct Node *rightChild = NULL;

    Node(int _value) {
        value = _value;
    }

    Node(int _value, Node *_parent) {
        value = _value;
        parent = _parent;
    }
};

struct Tree {
    struct Node *root;

    void addValue(int value) {
        if (root == NULL) {
            root = new Node(value);
        } else {
            addValueToNode(root, value);
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

    Node *findPredecessor(Node *node) {
        return node->parent;
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

    void printNode(struct Node *start) {
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
            if (node->rightChild) {
                visualizeNode(node->rightChild, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (node->rightChild) {
                std::cout << " /\n" << std::setw(indent) << ' ';
            }
            std::cout << node->value << "\n ";
            if (node->leftChild) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
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
        std::cout << "Podaj opcje: " << std::endl;
        std::cout << "1) Add value..." << std::endl;
        std::cout << "2) Show values" << std::endl;
        std::cout << "3) Show tree" << std::endl;
        std::cout << "4) Search (reference)..." << std::endl;
        std::cout << "5) Max value" << std::endl;
        std::cout << "6) Max value, smaller than..." << std::endl;

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
                std::cout << "Wartosci drzewa: " << std::endl;
                tree->print();
                std::cout << std::endl;
                break;

            case 3:
                std::cout << "Wizualizacja drzewa: " << std::endl;
                tree->visualize();
                break;

            case 4:
                std::cout << "Podaj wartosc do wyszukania: ";
                std::cin >> value;
                std::cout << "Referencja klucza: " << tree->search(value) << std::endl;
                break;

            case 5: {
                Node *maxNode = tree->findMax();
                if (maxNode == NULL) {
                    std::cout << "Max wartosc: Nie istnieje" << std::endl;
                } else {
                    std::cout << "Max wartosc: " << maxNode->value << std::endl;
                }
                break;
            }

            case 6: {
                std::cout << "Podaj wartosc do wyszkuania:";
                std::cin >> value;

                Node *maxNodePredecessor = tree->findPredecessor(tree->search(value));

                if (maxNodePredecessor != NULL) {
                    std::cout << "Najwiekszy element, mniejszy od podanej wartosci: "
                              << maxNodePredecessor->value
                              << std::endl;
                }
                break;
            }

            default:
                std::cout << "Zamykanie aplikacji";
                delete tree;
                return 0;
        }
    }
}
