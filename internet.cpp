#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <sys/time.h>

struct Node {
    int value;
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
};
struct Node *root;

struct Node *leftMostChild(struct Node *start) {
    if (start->leftChild != NULL) {
        return leftMostChild(start->leftChild);
    }
    return start;
}

//funkcja zwraca wezel o podanej wartosci, badz NULL, gdy taki wezel nie istnieje
struct Node *findNodeByValue(struct Node *start, int value) {
//jezeli wezel ma szukana wartosc to odnalezlismy go
    if (start->value == value) return start;
//jezeli szukana wartosc jest mniejsza to szukamy w lewym poddrzewie o ile istnieje
    else if (value < start->value && start->leftChild != NULL) return findNodeByValue(start->leftChild, value);
//jezeli szukana wartosc jest wieksza to szukamy w prawym poddrzewie o ile istnieje     
    else if (value > start->value && start->rightChild != NULL) return findNodeByValue(start->rightChild, value);
    return NULL;
}

//dodaje wezel o podanej wartosci n, do drzewa o korzeniu start
int dodawanie(int n, struct Node *start) {
//jezeli drzewo jest puste to dodaj korzen
    if (root == NULL) {
        root = (Node *) malloc(sizeof *root);
        root->value = n;
        root->leftChild = NULL;
        root->rightChild = NULL;
        root->parent = NULL;
    }
//jezeli zadana wartosc jest mniejsza od korzenia idz do lewego poddrzewa
    else if (n < start->value) {
//jezeli lewe poddrzewo istnieje wywolaj dla niego ta funkcje rekurencyjnie
        if (start->leftChild != NULL) {
            dodawanie(n, start->leftChild);
        }
//jezeli lewe poddrzewo nie istnieje dodaj nowy wezel o zadanej wartosci
        else {
            Node *nowy = (Node *) malloc(sizeof *root);
            nowy->value = n;
            nowy->leftChild = NULL;
            nowy->rightChild = NULL;
            nowy->parent = start;
            start->leftChild = nowy;
        }
    }
//jezeli zadana wartosc jest wieksza lub rowna korzeniowi idz do prawego poddrzewa   
    else {
//jezeli prawe poddrzewo istnieje wywolaj dla niego ta funkcje rekurencyjnie      
        if (start->rightChild != NULL) {
            dodawanie(n, start->rightChild);
        }
//jezeli prawe poddrzewo nie istnieje dodaj nowy wezel o zadanej wartosci     
        else {
            Node *nowy = (Node *) malloc(sizeof *root);
            nowy->value = n;
            nowy->leftChild = NULL;
            nowy->rightChild = NULL;
            nowy->parent = start;
            start->rightChild = nowy;
        }
    }
    return 0;
}

//usun wezel start
void kasowanie(struct Node *start) {
//jezeli wezel nie ma dzieci
    if (start->leftChild == NULL && start->rightChild == NULL) {
//jezeli wezel jest korzeniem
        if (start->parent == NULL) {
            root = NULL;
        }
//jezeli wezel jest po lewej stronie rodzica,
        else if (start->parent->leftChild == start) {
//usun wezel z lewej strony wezla rodzica
            start->parent->leftChild = NULL;
        } else {
//usun wezel z prawej strony wezla rodzica     
            start->parent->rightChild = NULL;
        }
        delete start;
    }
//jezeli wezel ma tylko jedno dziecko
    else if (start->leftChild == NULL || start->rightChild == NULL) {
//jezeli po lewej stronie nie ma dziecka
        if (start->leftChild == NULL) {
//jezeli wezel jest korzeniem
            if (start->parent == NULL) {
                root = start->rightChild;
            }
//jezeli wezel jest po lewej stronie rodzica
            else if (start->parent->leftChild == start) {
//przyczep z lewej strony rodzica wezel bedacy po prawej stronie usuwanego wezla
                start->parent->leftChild = start->rightChild;
            } else {
//przyczep z prawej strony rodzica wezel bedacy po prawej stronie usuwanego wezla
                start->parent->rightChild = start->rightChild;
            }
        } else {
//jezeli wezel jest korzeniem
            if (start->parent == NULL) {
                root = start->leftChild;
            }
//jezeli wezel jest po lewej stronie rodzica
            else if (start->parent->leftChild == start) {
//przyczep z lewej strony rodzica wezel bedacy po lewej stronie usuwanego wezla
                start->parent->leftChild = start->leftChild;
            } else {
//przyczep z prawej strony rodzica wezel bedacy po prawej stronie usuwanego wezla
                start->parent->rightChild = start->leftChild;
            }
        }
        delete start;
    } else {
//wstaw w miejsce usuwanego elementu - najmniejsza wartosc z prawego poddrzewa
        struct Node *temp;
        temp = leftMostChild(start->rightChild);
        start->value = temp->value;
        kasowanie(temp);
    }
}

void in_order_tree_walk(struct Node *start) {
    if (start->leftChild != NULL) {
        in_order_tree_walk(start->leftChild);
    }

    printf("%d\n", start->value);

    if (start->rightChild != NULL) {
        in_order_tree_walk(start->rightChild);
    }
}

int randomBetween(int bound1, int bound2) {
    int range = abs(bound1 - bound2);
    return std::min(bound1, bound2) + rand() % range;
}

int main(int argc, char *argv[]) {
    int i;
    int size = atoi(argv[1]);
    root = NULL;

    struct timezone _timezone;
    struct timeval _timeValue;

    gettimeofday(&_timeValue, &_timezone);
    srand(_timeValue.tv_usec);

    for (i = 0; i < size; i++) {
        int a = randomBetween(1, 100);
        dodawanie(a, root);
    }
    printf("\n");

    in_order_tree_walk(root);

    printf("Wartość węzła do usunięcia: \n");

    int k;
    scanf("%d", &k);
    kasowanie(findNodeByValue(root, k));

    printf("\n\n");

    in_order_tree_walk(root);

    return 0;
}
