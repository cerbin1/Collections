#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct Node {
    int value;
    struct Node *parent;
    struct Node *leftChild;
    struct Node *rightChild;
};
struct Node *root;

struct Node *leftMostChild(struct Node *start) {
    if (start->leftChild != NULL)
        return leftMostChild(start->leftChild);
    else
        return start;
}

//funkcja zwraca wezel o podanej wartosci, badz NULL, gdy taki wezel nie istnieje
struct Node *szukaj(struct Node *start, int wartosc) {
//jezeli wezel ma szukana wartosc to odnalezlismy go
    if (start->value == wartosc) return start;
//jezeli szukana wartosc jest mniejsza to szukamy w lewym poddrzewie o ile istnieje
    else if (wartosc < start->value && start->leftChild != NULL) return szukaj(start->leftChild, wartosc);
//jezeli szukana wartosc jest wieksza to szukamy w prawym poddrzewie o ile istnieje     
    else if (wartosc > start->value && start->rightChild != NULL) return szukaj(start->rightChild, wartosc);
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

//przejdz drzewo w kolejnosci zaczynajac od wezla start
void in_order_tree_walk(struct Node *start) {
    if (start->leftChild != NULL) //jezeli ma dzieci po lewej stronie wywolaj funkcje rekurencyjnie
        in_order_tree_walk(start->leftChild);

    printf("%d\n", start->value); //wypisz wartosc

    if (start->rightChild != NULL) //jezeli ma dzieci po prawej stronie wywolaj rekurencyjnie
        in_order_tree_walk(start->rightChild);
}

//lsouje wartosc w przedziale od a do b
int losowanie(int a, int b) {
    if (a < b)
        return a + (int) ((b - a + 1.0) * (rand() / (RAND_MAX + 1.0)));
    else {
        fprintf(stderr, "złe wartości");
        return -1;
    }
}

//przklad uzycia drzewa BST
int main(int argc, char *argv[]) {
    int i;
//pobierz rozmiar drzewa z parametru wejsciowego
    int a, k, size = atoi(argv[1]);
    root = NULL;

    struct timezone tz;
    struct timeval tv;

    gettimeofday(&tv, &tz);
    srand(tv.tv_usec);

//losuj wartosc elementow
    for (i = 0; i < size; i++) {
        a = losowanie(1, 100);
        dodawanie(a, root);
    }
    printf("\n");

//przejdz drzewo w kolejnosci
    in_order_tree_walk(root);

//usun wartosc z drzewa
    printf("Wartość węzła do usunięcia: \n");
    scanf("%d", &k);
    kasowanie(szukaj(root, k));
    printf("\n\n");

//przejdz drzewo w kolejnosci
    in_order_tree_walk(root);

    return 0;
}