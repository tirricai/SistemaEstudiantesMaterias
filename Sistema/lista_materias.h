#ifndef CEJP_LISTA_MATERIAS_H
#define CEJP_LISTA_MATERIAS_H
#include "nodo_materia.h"
#include "lista_estudiantes.h"

typedef struct structLista {
    NodoMateria *head;
    NodoMateria *tail;
    int size;
} ListaMaterias;

ListaMaterias *crearNuevaListaMaterias();
void agregarMateria(ListaMaterias *lista, Materia *materia);
void imprimirMaterias(ListaMaterias *lista);
void eliminarMateriaListaGeneral(ListaMaterias *lista, ListaEstudiante *lista_estudiantes, Materia *materia);
Materia *buscarMateriaPorId(ListaMaterias *lista, int id);
Materia *buscarMateriaPorNombre(ListaMaterias *lista, char *nombre);
void modificarNombreMateria(ListaMaterias *lista);
void imprimirListaMateriasPaginada(ListaMaterias *lista);
#endif
