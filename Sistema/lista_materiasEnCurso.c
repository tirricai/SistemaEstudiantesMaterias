#include <stdio.h>
#include <malloc.h>
#include "lista_materiasEnCurso.h"
#include "nodo_materiaestudiante.h"
listaMateriasEnCurso *crearNuevaListaMateriasEnCurso() {
    listaMateriasEnCurso *lista = malloc(sizeof(listaMateriasEnCurso));
    if (lista != NULL) {
        lista->head = NULL;
        lista->tail = NULL;
        lista->size = 0;
    }
    return lista;
}

void agregarMateriaEnCurso(listaMateriasEnCurso *lista, NodoMateriaEstudiante *nuevoNodo) {
    if (lista->head == NULL) {
        lista->head = nuevoNodo;
        lista->tail = nuevoNodo;
    } else {
        lista->tail->proximo = nuevoNodo;
        lista->tail = nuevoNodo;
    }
    lista->size++;
}

void imprimirListaMateriasEnCurso(listaMateriasEnCurso *lista) {
    if (lista == NULL || lista->head == NULL) {
        printf("El estudiante no se encuentra cursando ninguna materia\n");
        return;
    }
    NodoMateriaEstudiante *cursor = lista->head;
    while (cursor != NULL) {
        printf("%d | %s | Nota: %d\n", obtenerIDMateria(cursor->materia), obtenerNombreMateriaNodo(cursor), getNota(cursor));
        cursor = cursor->proximo;
    }
}

void modificarNota(listaMateriasEnCurso *lista, int idMateria, int nota) {
    NodoMateriaEstudiante *cursor = lista->head;
    while (cursor != NULL) {
        if (cursor->materia->id == idMateria) {
            cursor->nota = nota;
            return;
        }
        cursor = cursor->proximo;
    }
    printf("Materia con ID %d no encontrada.\n", idMateria);
}

void eliminarMateriaEnCurso(listaMateriasEnCurso *lista, Materia *materia) {
    if (lista == NULL || lista->head == NULL) {
        printf("Error: lista vacia");
        return;
    }

    NodoMateriaEstudiante *cursor = lista->head;
    NodoMateriaEstudiante *anterior = NULL;

    while (cursor != NULL) {
        if (cursor->materia->id == materia->id) {
            if (anterior == NULL) {
                lista->head = cursor->proximo;
                if (cursor == lista->tail) {
                    lista->tail = NULL;
                }
            } else {
                anterior->proximo = cursor->proximo;
                if (cursor == lista->tail) {
                    lista->tail = anterior;
                }
            }
            free(cursor);
            lista->size--;
            return;
        }
        anterior = cursor;
        cursor = cursor->proximo;
    }
}
