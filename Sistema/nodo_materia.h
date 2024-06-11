#ifndef CEJP_NODO_MATERIA_H
#define CEJP_NODO_MATERIA_H
#include "materias.h"

typedef struct structNodoMateria {
    Materia *materia;
    struct structNodoMateria *proximo;
} NodoMateria;

NodoMateria *crearNuevoNodoMateria(Materia *materia);

#endif