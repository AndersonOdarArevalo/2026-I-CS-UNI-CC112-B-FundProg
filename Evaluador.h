#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "Analizador.h"

class Evaluador {
public:
    Evaluador();

    double evaluar(Nodo* raiz, double valorX);
};

#endif