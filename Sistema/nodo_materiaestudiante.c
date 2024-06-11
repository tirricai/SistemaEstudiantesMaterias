#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include "nodo_materiaestudiante.h"
#include "materias.h"

NodoMateriaEstudiante *crearNuevoNodoMateriaEstudiante(Materia *materia, int nota) {
    NodoMateriaEstudiante *nuevoNodo = malloc(sizeof(NodoMateriaEstudiante));
    if (nuevoNodo != NULL) {
        nuevoNodo->materia = materia;
        nuevoNodo->nota = nota;
        nuevoNodo->proximo = NULL;
    }
    return nuevoNodo;
}
int getNota(NodoMateriaEstudiante *nodo){
    return nodo->nota;
}
char *obtenerNombreMateriaNodo(NodoMateriaEstudiante *nodo){
    return obtenerNombreMateria(nodo->materia);
}
