#include <iostream>
#include <vector>
#include <bits/stdc++.h>

struct Heap {
private:
    int capacity;
    std::vector<int> elements;

    // zwroc rodzica elementu elements[i]
    // nie wywoluj tej funkcji dla "roota" (najwyzszego rodzica)
    int _parent(int i) {
        return (i - 1) / 2;
    }

    // zwroc lewe dziecko elementu elements[i]
    int _left(int i) {
        return 2 * i + 1;
    }

    // zwroc prawe dziecko elementu elements[i]
    int _right(int i) {
        return 2 * i + 2;
    }

    // Recursywny algorytm Heapify_do()
    // węzeł na indexie "i" i jego dwoje bezpośrednich dzieci łamie własność kopca
    void heapify_down(int i) {
        // pobierz lewe i prawe dziecko węzła na indexie "i"
        int left = _left(i);
        int right = _right(i);

        int smallest = i;

        // porownaj elements[i] z jego lewym i prawym dzieckiem
        // oraz znajdz najmniejsza wartosc
        if (left < size() && elements[left] < elements[i]) {
            smallest = left;
        }

        if (right < size() && elements[right] < elements[smallest]) {
            smallest = right;
        }

        // zmnień miejscami z dzieckiem mającym mniejszą wartosc oraz
        // wywolaj heapify_down na dziecku
        if (smallest != i) {
            std::swap(elements[i], elements[smallest]);
            heapify_down(smallest);
        }
    }

    // rekursywny algorytm heapify_up()
    void heapify_up(int i) {

        // sprawdz czy element jest na indexie "i" i czy jego rodzic "łaamie
        // własność poprawnosci sterty

        if (i && elements[_parent(i)] > elements[i]) {
            // zamień miejscami dwa elementy jeśli własność nie jest zachowana
            std::swap(elements[i], elements[_parent(i)]);

            // wywołaj heapify_up() na rodzicu
            heapify_up(_parent(i));
        }
    }

public:
    Heap(int _capacity) {
        if (_capacity < 0) {
            _capacity = 0;
        }
        capacity = _capacity;
    }

    // zwroc rozmiar kopca
    unsigned int size() {
        return elements.size();
    }

    // funkcja sprawdzajaca czy lista jest pusta
    bool empty() {
        return size() == 0;
    }

    // dodaj wartosc klucza do kopca
    void insert(int key) {
        if (size() < capacity) {
            // dodaj nowy element na koniec vectora
            elements.push_back(key);

            // uzyj get element oraz wywołaj heapify_up()
            heapify_up(size() - 1);
        }
    }

    // funkcja usuwajaca najwyzszy element
    void pop() {
        if (!empty()) {

            // zamien najwyzszego rodzica "root" z ostatnim elementem
            // vectora
            elements[0] = elements.back();
            elements.pop_back();

            // wywołaj heapify_down() na elemencie "root" najwyższym rodzicu
            heapify_down(0);
        }
    }

    // funkcja zwracająca najwyższą wartość
    int top() {
        return elements.at(0);
    }
};

int main() {
    Heap *heap = NULL;

    while (true) {
        std::cout << "Dostepne opcje: " << std::endl;

        if (heap == NULL) {
            std::cout << "1) Stworz kopiec" << std::endl;
            std::cout << "2) Wyjdz z programu" << std::endl;
        } else {
            std::cout << "1) Dodaj liczbe" << std::endl;
            std::cout << "2) Pokaz gorny element" << std::endl;
            std::cout << "3) Usun gorny element" << std::endl;
            std::cout << "4) Pokaz rozmiar kopca" << std::endl;
            std::cout << "5) Czy kopiec pusty" << std::endl;
            std::cout << "6) Usun kopiec" << std::endl;
            std::cout << "7) Wyjdz z programu" << std::endl;
        }

        std::cout << "Podaj opcje: ";
        int choice;
        std::cin >> choice;

        if (heap == NULL) {
            switch (choice) {
                case 1:
                    std::cout << "Podaj nowy rozmiar kopca: ";
                    int size;
                    std::cin >> size;
                    heap = new Heap(size);
                    break;

                case 2:
                    delete heap;
                    return 0;

                default:
                    std::cout << "Niepoprawna opcja" << std::endl;
            }
        } else {
            switch (choice) {
                case 1:
                    std::cout << "Podaj liczbe do dodania: ";
                    int number;
                    std::cin >> number;
                    heap->insert(number);
                    break;
                case 2:
                    try {
                        int top = heap->top();
                        std::cout << "gorny element to '" << top << "'" << std::endl;
                    }
                    catch (std::out_of_range &e) {
                        std::cout << "Blad z funkcja wyciaganiem najwyzszczego elementu" << std::endl;
                    }
                    break;
                case 3:
                    try {
                        heap->pop();
                        std::cout << "gorny element usuniety" << std::endl;
                    }
                    catch (std::out_of_range &e) {
                        std::cout << "Blad z funkcja usuwania najwyzszczego elementu" << std::endl;
                    }
                    break;

                case 4:
                    std::cout << "Rozmiar kopca to: " << heap->size() << " elementow" << std::endl;
                    break;
                case 5:

                    std::cout << "Czy kopiec pusty: " << (heap->empty() ? "tak" : "nie") << std::endl;
                    break;

                case 6:
                    delete heap;
                    heap = NULL;
                    break;

                case 7:
                    delete heap;
                    return 0;

                default:
                    std::cout << "Niepoprawna opcja" << std::endl;
            }
        }
    }
}
