#include <iostream>
#include <vector>
#include <bits/stdc++.h>

struct Heap {
private:
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
        // dodaj nowy element na koniec vectora
        elements.push_back(key);

        // uzyj get element oraz wywołaj heapify_up()
        heapify_up(size() - 1);
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
    Heap heap;

    heap.insert(3);
    heap.insert(2);
    heap.insert(15);

    std::cout << "Size is " << heap.size() << std::endl;

    std::cout << heap.top() << " ";
    heap.pop();

    std::cout << heap.top() << " ";
    heap.pop();

    heap.insert(5);
    heap.insert(4);
    heap.insert(45);

    std::cout << std::endl << "Size is " << heap.size() << std::endl;

    std::cout << heap.top() << " ";
    heap.pop();

    std::cout << heap.top() << " ";
    heap.pop();

    std::cout << heap.top() << " ";
    heap.pop();

    std::cout << heap.top() << " ";
    heap.pop();

    std::cout << std::endl << std::boolalpha << heap.empty() << std::endl;

    try {
        // zwroc najmniejszy element
        heap.top();
    }
    catch (std::out_of_range &e) {
        std::cout << "Blad z funkcja wyciaganiem najwyzszczego elementu";
    }

    try {
        // usun najwyzszy element
        heap.pop();
    }
    catch (std::out_of_range &e) {
        std::cout << "Error: " << e.what();
    }

    return 0;
}
