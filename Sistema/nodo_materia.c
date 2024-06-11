#include <stdio.h>
#include <malloc.h>
#include "nodo_materia.h"

NodoMateria *crearNuevoNodoMateria(Materia *materia) {
    NodoMateria *nuevoNodo = malloc(sizeof(NodoMateria));
    nuevoNodo->materia = materia;
    nuevoNodo->nota = -1;
    nuevoNodo->proximo = NULL;
    return nuevoNodo;
}