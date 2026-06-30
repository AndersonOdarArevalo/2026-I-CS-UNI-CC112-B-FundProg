#include "Evaluador.h"
#include <cmath>
#include <iostream>

Evaluador::Evaluador() {}

double Evaluador::evaluar(Nodo* raiz, double valorX) {
    if (raiz == nullptr) {
        return 0.0;
    }

    switch (raiz->tipo) {
        
        case CONSTANTE:
            return raiz->valorNumerico;

        case VARIABLE:
            return valorX;

        case OPERADOR: {
            double izqVal = evaluar(raiz->izq, valorX);
            double derVal = evaluar(raiz->der, valorX);

            if (raiz->Texto == "+") return izqVal + derVal;
            if (raiz->Texto == "-") return izqVal - derVal;
            if (raiz->Texto == "*") return izqVal * derVal;
            if (raiz->Texto == "/") {
                if (derVal == 0.0) {
                    std::cerr << "Error: División por cero detectada.\n"; // Cap. 6 - Pag. 139
                    return 0.0;
                }
                return izqVal / derVal;
            }
            break;
        }

        case FUNCION: {
            double argVal = evaluar(raiz->der, valorX);

            if (raiz->Texto == "sin") return std::sin(argVal);
            if (raiz->Texto == "cos") return std::cos(argVal);
            if (raiz->Texto == "tan") return std::tan(argVal);
            if (raiz->Texto == "exp") return std::exp(argVal);
            if (raiz->Texto == "log") return std::log10(argVal);
            if (raiz->Texto == "ln")  return std::log(argVal);
            break;
        }
    }

    return 0.0;
}