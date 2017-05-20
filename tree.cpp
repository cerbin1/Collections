#include <stdio.h>
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
};

struct Tree {
    struct Node *root;

    void addValue(int value) {
        addValue(root, value);
    }

    Node *findNodeByValue(int value) {
        return findNodeByValue(root, value);
    }

    void printNodes() {
        cout << endl;
        printNodes(root);
        cout << endl;
    }

    void visualize() {
        cout << endl;
        visualize(root, 0);
        cout << endl;
    }

    void addValue(Node *start, int value) {
        if (root == NULL) {
            root = new Node(value);
            return;
        }

        if (value < start->value) {
            if (start->leftChild != NULL) {
                addValue(start->leftChild, value);
            } else {
                Node *newNode = new Node(value);
                newNode->parent = start;
                start->leftChild = newNode;
            }
        } else {
            if (start->rightChild != NULL) {
                addValue(start->rightChild, value);
            } else {
                Node *newNode = new Node(value);
                newNode->parent = start;
                start->rightChild = newNode;
            }
        }
    }

    Node *findNodeByValue(Node *start, int value) {
        if (start->value == value) {
            return start;
        }

        if (value < start->value && start->leftChild != NULL) {
            return findNodeByValue(start->leftChild, value);
        }

        if (value > start->value && start->rightChild != NULL) {
            return findNodeByValue(start->rightChild, value);
        }

        return NULL;
    }

    Node *findMax(Node *node) {
        if (node->rightChild != NULL) {
            return findMax(node->rightChild);
        }
        return node;
    }

    void printNodes(struct Node *start) {
        if (start->leftChild != NULL) {
            printNodes(start->leftChild);
        }

        std::cout << start->value << ", ";

        if (start->rightChild != NULL) {
            printNodes(start->rightChild);
        }
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
    Tree *tree = new Tree();

    std::cout << "Podaj ilosc wezlow: ";
    int size;
    std::cin >> size;

    for (int i = 0; i < size; i++) {
        int randomValue = randomBetween(1, 100);
        tree->addValue(randomValue);
    }
    std::cout << std::endl;

    std::cout << "Wartosci drzewa: " << std::endl;
    tree->printNodes();

    if (size > 4) {
        std::cout << std::endl << "Wizualizacja: " << std::endl;
        tree->visualize();
    }

    std::cout << tree->findMax(tree->root);

    return 0;
}
