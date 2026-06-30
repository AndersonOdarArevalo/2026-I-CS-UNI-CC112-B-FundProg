#include "InterfazGrafica.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

InterfazGrafica::InterfazGrafica() {}

void InterfazGrafica::limpiarPantalla() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void InterfazGrafica::Cabecera() {
    std::cout << "==================================================\n";
    std::cout << "       INTERPRETE Y GRAFICADOR MATEMATICO        \n";
    std::cout << "==================================================\n\n";
}

void InterfazGrafica::Graficar(Nodo* raiz, double xMin, double xMax) {
    if (raiz == nullptr) return;

    const int ANCHO = 100;  
    const int ALTO = 40;    
    char matriz[ALTO][ANCHO];

    const double LIMITE_Y_MAX = 5;
    const double LIMITE_Y_MIN = -5;

    int EjeY = -1;
    if (xMin <= 0 && xMax >= 0) {
        double columnaDecimal = (0.0 - xMin) * (ANCHO - 1) / (xMax - xMin);
        EjeY = columnaDecimal;
    }
    
    int EjeX = -1;
    if (LIMITE_Y_MIN <= 0 && LIMITE_Y_MAX >= 0) {
        double filaDecimal = (0.0 - LIMITE_Y_MIN) * (ALTO - 1) / (LIMITE_Y_MAX - LIMITE_Y_MIN);
        EjeX = (ALTO - 1) - filaDecimal;
    }

    for (int i = 0; i < ALTO; ++i) {
        for (int j = 0; j < ANCHO; ++j) {
            if (i == EjeX && j == EjeY) matriz[i][j] = '+';
            else if (i == EjeX) matriz[i][j] = '-';
            else if (j == EjeY) matriz[i][j] = '|';
            else matriz[i][j] = ' ';
        }
    }

    int filasGuardadas[ANCHO];

    for (int col = 0; col < ANCHO; ++col) {
        double x = xMin + (col * (xMax - xMin) / (ANCHO - 1));
        double y = evaluador.evaluar(raiz, x);

        if (std::isnan(y) || std::isinf(y)) {
            filasGuardadas[col] = -1; 
            continue;
        }

        if (y > LIMITE_Y_MAX) y = LIMITE_Y_MAX;
        if (y < LIMITE_Y_MIN) y = LIMITE_Y_MIN;

        double filaMapeada = (y - LIMITE_Y_MIN) * (ALTO - 1) / (LIMITE_Y_MAX - LIMITE_Y_MIN);
        int fila = (ALTO - 1) - filaMapeada;
        
        if (fila < 0) fila = 0;
        if (fila >= ALTO) fila = ALTO - 1;

        filasGuardadas[col] = fila;
    }

    for (int col = 0; col < ANCHO; ++col) {
        int filaActual = filasGuardadas[col];

        if (filaActual == -1) continue;

        if (col == 0 || filasGuardadas[col - 1] == -1) {
            matriz[filaActual][col] = '*';
        } else {
            int filaAnterior = filasGuardadas[col - 1];
            int inicio = std::min(filaAnterior, filaActual);
            int fin = std::max(filaAnterior, filaActual);

            for (int f = inicio; f <= fin; ++f) {
                matriz[f][col] = '*';
            }
        }
    }

    std::cout << "\n   ^ Y (Max: " << LIMITE_Y_MAX << ")\n";
    for (int i = 0; i < ALTO; ++i) {
        std::cout << "   | "; 
        for (int j = 0; j < ANCHO; ++j) {
            std::cout << matriz[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "   +";
    for (int j = 0; j < ANCHO; ++j) std::cout << "-";
    std::cout << "> X\n";
    std::cout << "     Rango Evaluado X: [" << xMin << " : " << xMax << "]\n\n";
}

void InterfazGrafica::BuclePrincipal() {
    std::string ecuacion = "sin(x)";
    Nodo* raizActual = analizador.CrearArbol(ecuacion);

    int opcion = 0;
    while (opcion != 3) {
        limpiarPantalla();
        Cabecera();
        std::cout << "  Ecuacion activa actual: f(x) = " << ecuacion << "\n\n";
        std::cout << "  1. Ingresar nueva ecuacion matematica\n";
        std::cout << "  2. Visualizar grafica en terminal\n";
        std::cout << "  3. Salir del programa\n\n";
        std::cout << "  Seleccione una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::cout << "\nDigite la ecuacion (ej: 2*cos(x), sin(x)+ln(x)): ";
            std::cin.ignore();
            std::getline(std::cin, ecuacion);
            
            analizador.LimpiarArbol(raizActual);
            raizActual = analizador.CrearArbol(ecuacion);
            std::cout << "Arbol de sintaxis actualizado. Presione Enter para continuar...";
            std::cin.get();
        } 
        else if (opcion == 2) {
            if (raizActual != nullptr) {
                Graficar(raizActual, -15.7, 15.7);
            } else {
                std::cout << "\nError: No hay una ecuacion valida cargada.\n";
            }
            std::cout << "Presione Enter para regresar al menu...";
            std::cin.ignore();
            std::cin.get();
        }
    }
    analizador.LimpiarArbol(raizActual);
}