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
        printNodes(root);
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

    void removeNode(Node *start) {
        if (start->leftChild == NULL && start->rightChild == NULL) {
            if (start->parent == NULL) {
                root = NULL;
            } else if (start->parent->leftChild == start) {
                start->parent->leftChild = NULL;
            } else {
                start->parent->rightChild = NULL;
            }
            delete start;
        } else if (start->leftChild == NULL || start->rightChild == NULL) {
            if (start->leftChild == NULL) {
                if (start->parent == NULL) {
                    root = start->rightChild;
                } else if (start->parent->leftChild == start) {

                    start->parent->leftChild = start->rightChild;
                } else {

                    start->parent->rightChild = start->rightChild;
                }
            } else {
                if (start->parent == NULL) {
                    root = start->leftChild;
                } else if (start->parent->leftChild == start) {
                    start->parent->leftChild = start->leftChild;
                } else {
                    start->parent->rightChild = start->leftChild;
                }
            }
            delete start;
        } else {
            Node *temp = findLeftMostChild(start->rightChild);
            start->value = temp->value;
            removeNode(temp);
        }
    }

    Node *findLeftMostChild(Node *start) {
        if (start->leftChild != NULL) {
            return findLeftMostChild(start->leftChild);
        }
        return start;
    }

    void printNodes(struct Node *start) {
        if (start->leftChild != NULL) {
            printNodes(start->leftChild);
        }

        printf("%d\n", start->value);

        if (start->rightChild != NULL) {
            printNodes(start->rightChild);
        }
    }

    void visualize() {
        visualize(root, 0);
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

    printf("Podaj ilosc wzlow: ");
    int size;
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        int randomValue = randomBetween(1, 100);
        tree->addValue(randomValue);
    }
    printf("\n");

    tree->visualize();

    printf("Wartość węzła do usunięcia: \n");

    int k;
    scanf("%d", &k);
    tree->removeNode(tree->findNodeByValue(k));

    printf("\n\n");

    tree->visualize();

    return 0;
}
