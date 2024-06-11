#ifndef CEJP_LISTA_MATERIASENCURSO_H
#define CEJP_LISTA_MATERIASENCURSO_H
#include "nodo_materiaestudiante.h"
#include "materias.h"

typedef struct structlistaMateriasEnCurso {
    NodoMateriaEstudiante *head;
    NodoMateriaEstudiante *tail;
    int size;
} listaMateriasEnCurso;

listaMateriasEnCurso *crearNuevaListaMateriasEnCurso();
void agregarMateriaEnCurso(listaMateriasEnCurso *lista, NodoMateriaEstudiante *nodo);
void imprimirListaMateriasEnCurso(listaMateriasEnCurso *lista);
void modificarNota(listaMateriasEnCurso *lista, int idMateria, int nota);
void eliminarMateriaEnCurso(listaMateriasEnCurso *lista, Materia *materia);

#endif
