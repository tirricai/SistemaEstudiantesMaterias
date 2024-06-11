#ifndef CEJP_NODO_MATERIAESTUDIANTE_H
#define CEJP_NODO_MATERIAESTUDIANTE_H
#include "materias.h"
typedef struct structNodoMateriaEstudiante {
    Materia *materia;
    int nota;
    struct structNodoMateriaEstudiante *proximo;
} NodoMateriaEstudiante;

NodoMateriaEstudiante *crearNuevoNodoMateriaEstudiante(Materia *materia, int nota);
int getNota(NodoMateriaEstudiante *nodo);
char* obtenerNombreMateriaNodo(NodoMateriaEstudiante *nodo);
#endif