#ifndef _LISTA_HPP_
#define _LISTA_HPP_

#include "cancion.hpp"
#include <string>
#include <fstream>
#include <stdexcept>

template <class T>
class Lista {
private:
    T data[3000];
    int last;

    bool isValidPos(const int&) const;
    void copyAll(const Lista<T>&);
    
    void sortDataMerge(); // cambiar este por el otro
    void sortDataMerge(const int&, const int&, int (cont T&, const T&));

public:
    Lista();
    Lista(const Lista&);

    void inicializa();
    bool vacia() const;
    bool llena() const;
    void inserta(const int&, const T&);
    void elimina(const int&);
    T recupera(const int&) const;
    int primero() const;
    int ultimo() const;
    int anterior(const int&) const;
    int siguiente(const int&) const;
    void anula();

    std::string toString() const;

    void guardarEnArchivo(const std::string& nombreArchivo) const;
    void cargarDesdeArchivo(const std::string& nombreArchivo);

    int busquedaLineal(const T& elemento, int (*cmp)(const T&, const T&)) const;
    int busquedaBinaria(const T& elemento, int (*cmp)(const T&, const T&)) const;

    void sortBubble(int (*cmp)(const T&, const T&));
    void sortInsert(int (*cmp)(const T&, const T&));
    void sortSelect(int (*cmp)(const T&, const T&));
    void sortShell(int (*cmp)(const T&, const T&));
    void sortDataMerge(const int&, const int&);

    
    bool isSort(int (*cmp)(const T&, const T&)) const;

    void swapData(T&, T&);
};

template <class T>
bool Lista<T>::isValidPos(const int& p) const {
    return p >= 0 && p <= last;
}

template <class T>
void Lista<T>::copyAll(const Lista<T>& other) {
    for(int i = 0; i <= other.last; ++i) {
        data[i] = other.data[i];
    }
    last = other.last;
}

template <class T>
Lista<T>::Lista(): last(-1) {}

template <class T>
Lista<T>::Lista(const Lista& other) {
    copyAll(other);
}

template <class T>
void Lista<T>::inicializa() {
    last = -1;
}

template <class T>
bool Lista<T>::vacia() const {
    return last == -1;
}

template <class T>
bool Lista<T>::llena() const {
    return last == 2999;
}

template <class T>
bool Lista<T>::isSort(int (*cmp)(const T&, const T&)) const {
    for (int i = 0; i < last; ++i) {
        if (cmp(data[i], data[i + 1]) > 0) {
            return false;
        }
    }
    return true;
}


template <class T>
void Lista<T>::inserta(const int& p, const T& e) {
    if (llena()) {
        throw std::overflow_error("La lista esta llena, no se puede insertar.");
    }
    if (p != -1 && (p < 0 || p > last + 1)) {
        throw std::out_of_range("Posicion de insercion invalida.");
    }

    int pos = (p == -1) ? last + 1 : p;

    for(int i = last; i >= pos; --i) {
        data[i + 1] = data[i];
    }
    data[pos] = e;
    last++;
}

template <class T>
void Lista<T>::elimina(const int& p) {
    if (!isValidPos(p)) {
        throw std::out_of_range("Posición de eliminación inválida.");
    }
    for(int i = p; i < last; ++i) {
        data[i] = data[i + 1];
    }
    last--;
}

template <class T>
T Lista<T>::recupera(const int& p) const {
    if (!isValidPos(p)) {
        throw std::out_of_range("Posición de recuperación inválida.");
    }
    return data[p];
}

template <class T>
int Lista<T>::primero() const {
    return vacia() ? -1 : 0;
}

template <class T>
int Lista<T>::ultimo() const {
    return last;
}

template <class T>
int Lista<T>::anterior(const int& p) const {
    if (p <= 0 || p > last) {
        return -1;
    }
    return p - 1;
}

template <class T>
int Lista<T>::siguiente(const int& p) const {
    if (p < 0 || p >= last) {
        return -1;
    }
    return p + 1;
}

template <class T>
void Lista<T>::anula() {
    last = -1;
}

template <class T>
std::string Lista<T>::toString() const {
    std::string result = "";
    for(int i = 0; i <= last; ++i) {
        result += std::to_string(i + 1) + ". " + data[i].toString() + "\n";
    }
    return result;
}

template <class T>
void Lista<T>::guardarEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para guardar.");
    }

    for (int i = 0; i <= last; ++i) {
        archivo << data[i];
    }
    archivo.close();
}

template <class T>
void Lista<T>::cargarDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para cargar.");
    }

    anula();
    T cancion;
    while(archivo >> cancion && !llena()) {
        if (!cancion.getNombre().empty()) {
            inserta(ultimo() + 1, cancion);
        }
    }
    archivo.close();
}

template <class T>
void Lista<T>::swapData(T& a, T& b) {
    T aux = a;
    a = b;
    b = aux;
}

template <class T>
void Lista<T>::sortBubble(int (*cmp)(const T&, const T&)) {
    int i = last, j;
    bool flag;
    do {
        flag = false;
        j = 0;
        while(j < i) {
            if(cmp(data[j], data[j + 1]) > 0) {
                swapData(data[j], data[j + 1]);
                flag = true;
            }
            j++;
        }
        i--;
    } while (flag);
}

template <class T>
void Lista<T>::sortSelect(int (*cmp)(const T&, const T&)) {
    int i = 0, j, m;
    
    while(i < last) {
        m = i;
        j = i + 1;
        
        while(j <= last) {
            if(cmp(data[j], data[m]) < 0) {
                m = j;
            }
            j++;
        }
        if(m != i) {
            swapData(data[i], data[m]);
        }
        i++;
    }
}

template <class T>
void Lista<T>::sortInsert(int (*cmp)(const T&, const T&)) {
    int i = 1, j;
    T aux;
    
    while (i <= last) {
        aux = data[i];
        j = i;
        
        while(j > 0 && cmp(aux, data[j - 1]) < 0) {
            data[j] = data[j-1];
            j--;
        }
        if(i != j) {
            data[j] = aux;
        }
        i++;
    }
}

template <class T>
void Lista<T>::sortShell(int (*cmp)(const T&, const T&)) {
    float fact = 0.5f;
    int dif = (last + 1) * fact;
    int i, j;
    
    while(dif > 0) {
        i = dif;
        while (i <= last) {
            j = i;
            while(j >= dif && cmp(data[j], data[j - dif]) < 0) {
                swapData(data[j-dif], data[j]);
                j -= dif;
            }
            i++;
        }
        dif *= fact;
    }
}

template <class T>
int Lista<T>::busquedaLineal(const T& elemento, int (*cmp)(const T&, const T&)) const {
    for(int i = 0; i <= last; ++i) {
        if(cmp(data[i], elemento) == 0) {
            return i;
        }
    }
    return -1;
}

template <class T>
int Lista<T>::busquedaBinaria(const T& elemento, int (*cmp)(const T&, const T&)) const {
    int i = 0;
    int j = last;
    int medio;
    
    while(i <= j) {
        medio = (i + j) / 2;
        int comparacion = cmp(data[medio], elemento);
        if(comparacion == 0) {
            return medio;
        }
        if(comparacion < 0) {
            i = medio + 1;
        } else {
            j = medio - 1;
        }
    }
    return -1;
}

template <class T>
void Lista<T>::sortDataMerge() {
    this->sortDataMerge(0, this->last);
}

template <class T>
void Lista<T>::sortDataMerge(const int& leftedge, const int& rightedge) {
    if (leftedge >= rightedge){ // criterio de paro
        return;
    }
    int m(leftedge + rightedge) / 2;

    // divide y venceras
    this->sortDataMerge(leftedge, m);
    this->sortDataMerge(m + 1, rightedge);

    // intercalacion 
    static T tmp[data.size()]; // arreglo temporal (se reutiliza el mismo espacio de memoria)
    for (int z(leftedge); z <= rightedge; z++) {
        tmp[z] = this->data[z];
    }
    int i(leftedge), j(m + 1), x(rightedge);
    while(i <= m && j<= rightedge) {
        // iteraciones internas
        while(i <= m && tmp && tmp[i] <= tmp[j]) {
            this->data[x++] = tmp[i++];
        }
        if (i <= m) {
            while(j <= rightedge && tmp[j] <= tmp[i]) {
                this->data[x++] = tmp[j++]
            }
        }
    }
    while(i <= m) {
        this->data[x++] = tmp[i++];
    }

    // codigo faltante
    
}
/* incorporar esta
template <class T> // añadir este
void Lista<T>::sortDataMerge(int cmp(const &T rightedge, const &T leftedge)) {
    this->sortDataMerge(0, this->last);
}


template <class T>
void Lista<T>::sortDataMerge(const int& leftedge, const int& rightedge) {
    if (leftedge >= rightedge){ // criterio de paro
        return;
    }
    int m(leftedge + rightedge) / 2;

    // divide y venceras
    this->sortDataMerge(leftedge, m, cmp);
    this->sortDataMerge(m + 1, rightedge, cmp);

    // intercalacion 
    static T tmp[data.size()]; // arreglo temporal (se reutiliza el mismo espacio de memoria)
    for (int z(leftedge); z <= rightedge; z++) {
        tmp[z] = this->data[z];
    }
    int i(leftedge), j(m + 1), x(rightedge);
    while(i <= m && j<= rightedge) {
        // iteraciones internas
        while(i <= m && tmp && tmp[i] <= tmp[j]) {
            this->data[x++] = tmp[i++];
        }
        if (i <= m) {
            while(j <= rightedge && tmp[j] <= tmp[i]) {
                this->data[x++] = tmp[j++]
            }
        }
    }
    while(i <= m) {
        this->data[x++] = tmp[i++];
    }

    // codigo faltante
    
}
*/
#endif