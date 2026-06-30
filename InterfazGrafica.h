#ifndef INTERFAZ_GRAFICA_H
#define INTERFAZ_GRAFICA_H

#include "Analizador.h"
#include "Evaluador.h"
#include <string>

class InterfazGrafica {
private:
    Analizador analizador;
    Evaluador evaluador;

    void limpiarPantalla();
    void Cabecera();
    void Graficar(Nodo* raiz, double xMin, double xMax);

public:
    InterfazGrafica();

    void BuclePrincipal();
};

#endif