#include "Analizador.h"
#include <cmath>
#include <cctype>
#include <cstdlib>

Analizador::Analizador() : expresion(""), posicion(0) {
}

Nodo::Nodo(Apoyo t)
    : tipo(t), valorNumerico(0), Texto(""), izq(nullptr), der(nullptr) {}

Nodo::~Nodo() {
    if (izq != nullptr) {
        delete izq;
    }
    if (der != nullptr) {
        delete der;
    }
}

char Analizador::CaracterActual() {
    if (posicion < expresion.length()) {
        return expresion[posicion];
    }
    return '\0';
}

void Analizador::SiguientePosicion() {
    if (posicion < expresion.length()) {
        posicion++;
    }
}

Nodo* Analizador::CrearArbol(std::string expTexto) {
    expresion = expTexto;
    posicion = 0;
    
    return TercerNivel();
}

void Analizador::LimpiarArbol(Nodo* raiz) {
    if (raiz != nullptr) {
        delete raiz;
    }
}

Nodo* Analizador::TercerNivel() {
    Nodo* nodoIzquierdo = SegundoNivel();

    while (CaracterActual() == '+' || CaracterActual() == '-') {
        char operador = CaracterActual();
        SiguientePosicion();

        Nodo* nuevoNodo = new Nodo(OPERADOR);
        nuevoNodo->Texto = operador;
        
        nuevoNodo->izq = nodoIzquierdo;
        nuevoNodo->der = SegundoNivel();

        nodoIzquierdo = nuevoNodo;
    }

    return nodoIzquierdo;
}

Nodo* Analizador::SegundoNivel() {
    Nodo* nodoIzquierdo = PrimerNivel();

    while (CaracterActual() == '*' || CaracterActual() == '/') {
        char operador = CaracterActual();
        SiguientePosicion();

        Nodo* nuevoNodo = new Nodo(OPERADOR);
        nuevoNodo->Texto = operador;

        nuevoNodo->izq = nodoIzquierdo;
        nuevoNodo->der = PrimerNivel();

        nodoIzquierdo = nuevoNodo;
    }

    return nodoIzquierdo;
}

Nodo* Analizador::PrimerNivel() {
    char actual = CaracterActual();

    if (isdigit(actual) || actual == '.') { // Part. 4 - Pag. 1020
        std::string numeroTexto = "";
        
        while (isdigit(CaracterActual()) || CaracterActual() == '.') {
            numeroTexto += CaracterActual();
            SiguientePosicion();
        }

        Nodo* nuevoNodo = new Nodo(CONSTANTE);
        nuevoNodo->valorNumerico = std::stod(numeroTexto);
        return nuevoNodo;
    }
    
    if (actual == 'x' || actual == 'X') {
        Nodo* nuevoNodo = new Nodo(VARIABLE);
        nuevoNodo->Texto = "x";
        SiguientePosicion();
        return nuevoNodo;
    }

    if (actual == '(') {
        SiguientePosicion();
        
        Nodo* nodoInterno = TercerNivel();
        
        if (CaracterActual() == ')') {
            SiguientePosicion();
        }
        return nodoInterno;
    }

    if (isalpha(actual)) {
        std::string funcionNombre = "";
        while (isalpha(CaracterActual())) { // Part. 4 - Pag. 1020
            funcionNombre += CaracterActual();
            SiguientePosicion();
        }

        if (funcionNombre == "sin" || funcionNombre == "cos" || funcionNombre == "tan" ||
            funcionNombre == "exp" || funcionNombre == "log" || funcionNombre == "ln") {
            Nodo* nuevoNodo = new Nodo(FUNCION);
            nuevoNodo->Texto = funcionNombre;
            
            nuevoNodo->der = PrimerNivel(); 
            return nuevoNodo;
        }
    }

    return nullptr;
}