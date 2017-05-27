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
        addValue(root, value);
    }

    Node *search(int value) {
        return search(root, value);
    }

    Node *findMax() {
        return findMax(root);
    }

    void print() {
        print(root);
        std::cout << std::endl;
    }

    void visualize() {
        std::cout << std::endl;
        visualize(root, 0);
        std::cout << std::endl;
    }


    void addValue(Node *start, int value) {
        if (root == NULL) {
            root = new Node(value);
            return;
        }

        if (value < start->value) {
            if (start->leftChild == NULL) {
                start->leftChild = new Node(value, start);
            } else {
                addValue(start->leftChild, value);
            }
        } else {
            if (start->rightChild == NULL) {
                start->rightChild = new Node(value, start);
            } else {
                addValue(start->rightChild, value);
            }
        }
    }

    void print(struct Node *start) {
        if (start->leftChild != NULL) {
            print(start->leftChild);
        }

        std::cout << start->value << ", ";

        if (start->rightChild != NULL) {
            print(start->rightChild);
        }
    }

    Node *search(Node *start, int value) {
        if (start->value == value) {
            return start;
        }

        if (value < start->value && start->leftChild != NULL) {
            return search(start->leftChild, value);
        }

        if (value > start->value && start->rightChild != NULL) {
            return search(start->rightChild, value);
        }

        return NULL;
    }

    Node *findMax(Node *node) {
        if (node->rightChild != NULL) {
            return findMax(node->rightChild);
        }
        return node;
    }

    Node *findPredecessor(Node *node) {
        return node->parent;
    }

    void visualize(Node *node, int indent) {
        if (node != NULL) {
            if (node->rightChild) {
                visualize(node->rightChild, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (node->rightChild) std::cout << " /\n" << std::setw(indent) << ' ';
            std::cout << node->value << "\n ";
            if (node->leftChild) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                visualize(node->leftChild, indent + 4);
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
    std::cout << "Podaj ilosc wezlow: ";
    int size;
    std::cin >> size;

    for (int i = 0; i < size; i++) {
        int randomValue = randomBetween(1, 100);
        std::cout << randomValue << ",";
        tree->addValue(randomValue);
    }

    std::cout << std::endl;
    std::cout << "Root is " << tree->root->value << std::endl;
    std::cout << "left is " << tree->root->leftChild->value << std::endl;
    std::cout << "right is " << tree->root->rightChild->value << std::endl;

    std::cout << std::endl << "Wartosci drzewa: " << std::endl;
    tree->print();

    if (size > 4) {
        std::cout << std::endl << "Wizualizacja: " << std::endl;
        tree->visualize();
    }

    delete tree;

    tree = new Tree();
    std::cout << std::endl << "Podaj opcje: ";
    while (true) {
        int choice;
        std::cin >> choice;
        int value;
        switch (choice) {
            case 1:
                std::cin >> value;
                tree->addValue(value);
                break;
            case 2:
                std::cout << "Wartosci drzewa: " << std::endl;
                tree->print();
                break;
            case 3:
                value;
                std::cin >> value;
                std::cout << "Referencja klucza: " << tree->search(value) << std::endl;
                break;
            case 4:
                std::cout << "Max wartosc: " << tree->findMax() << std::endl;
                break;
            case 5:
                value;
                std::cin >> value;
                if (tree->findPredecessor(tree->search(value)) != NULL) {
                    std::cout << "Max element, mniejszy od podanej wartosci: "
                              << tree->findPredecessor(tree->search(value))->value << std::endl;
                }
                break;
            default:
                delete tree;
                return 0;
        }
    }
}
