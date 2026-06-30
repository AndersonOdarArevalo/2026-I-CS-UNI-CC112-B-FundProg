#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#include <string>

enum Apoyo { // Cap.4 - Pag. 66
    CONSTANTE,
    VARIABLE,
    OPERADOR,
    FUNCION
};

struct Nodo {
    Apoyo tipo;
    double valorNumerico;
    std::string Texto;
    
    Nodo* izq;
    Nodo* der;

    Nodo(Apoyo t);
    ~Nodo();
};

class Analizador {
private:
    std::string expresion;
    size_t posicion;

    char CaracterActual();
    void SiguientePosicion();
    
    Nodo* TercerNivel();
    Nodo* SegundoNivel();
    Nodo* PrimerNivel();

public:
    Analizador();
    Nodo* CrearArbol(std::string expTexto); // Cap. 17 - Pag. 857
    void LimpiarArbol(Nodo* raiz);
};

#endif