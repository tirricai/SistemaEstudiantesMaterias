#include <stdio.h>
#include <malloc.h>
#include "lista_materias.h"
#include <string.h>

ListaMaterias *crearNuevaListaMaterias() {
    ListaMaterias *lista = malloc(sizeof(ListaMaterias));
    if (lista == NULL) {
        printf("Error al asignar memoria para la lista.\n");
        return NULL;
    }
    lista->head = NULL;
    lista->tail = NULL;
    return lista;
}

void agregarMateria(ListaMaterias *lista, Materia *materia) {
    if (lista == NULL || materia == NULL) {
        printf("Error: La lista o la materia no pueden ser nulos.\n");
        return;
    }

    NodoMateria *nuevoNodo = malloc(sizeof(NodoMateria));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria para el nodo.\n");
        return;
    }

    nuevoNodo->materia = materia;
    nuevoNodo->proximo = NULL;

    if (lista->head == NULL) {
        lista->head = nuevoNodo;
        lista->tail = nuevoNodo;
    } else {
        lista->tail->proximo = nuevoNodo;
        lista->tail = nuevoNodo;
    }
}

void imprimirMaterias(ListaMaterias *lista) {
    if (lista == NULL) {
        printf("La lista no puede ser nula.\n");
        return;
    }
    printf("Materias disponibles:\n");
    NodoMateria *cursor = lista->head;
    while (cursor != NULL) {
        printf("| ID: %d | Nombre: %s  | \n", cursor->materia->id, cursor->materia->nombre);

        printf("| Correlativas ID: ");
        for (int i = 0; i < sizeof(cursor->materia->id_correlativas)/(sizeof(int)) ; ++i) {
            if (cursor->materia->id_correlativas[i] == -1){
                break;
            }
            printf("[%d] | ",cursor->materia->id_correlativas[i]);
        }
        printf("\n");
        cursor = cursor->proximo;
    }
    printf("\n");
}

void eliminarMateriaListaGeneral(ListaMaterias *lista_materias, ListaEstudiante *lista_estudiantes, Materia *materia) {
    if (lista_materias == NULL || lista_materias->head == NULL) {
        printf("Error: Lista de materias vacía o no inicializada.\n");
        return;
    }

    NodoEstudiante *nodo_estudiante = lista_estudiantes->head;
    while (nodo_estudiante != NULL) {
        eliminarMateriaEnCurso(nodo_estudiante->estudiante->listaEnCurso, materia);
        nodo_estudiante = nodo_estudiante->proximo;
    }

    NodoMateria *cursor = lista_materias->head;
    NodoMateria *anterior_materia = NULL;

    while (cursor != NULL) {
        if (obtenerIDMateria(cursor->materia) == materia->id) {
            if (anterior_materia == NULL) {
                lista_materias->head = cursor->proximo;
                if (cursor == lista_materias->tail) {
                    lista_materias->tail = NULL;
                }
            } else {
                anterior_materia->proximo = cursor->proximo;
                if (cursor == lista_materias->tail) {
                    lista_materias->tail = anterior_materia;
                }
            }
            free(cursor->materia);
            free(cursor);
            lista_materias->size--;
            return;
        }
        anterior_materia = cursor;
        cursor = cursor->proximo;
    }

    printf("Materia con ID %d no encontrada en la lista general.\n", materia->id);
}

Materia *buscarMateriaPorNombre(ListaMaterias *lista, char *nombre) {
    if (lista == NULL || nombre == NULL) {
        printf("La lista o el nombre no pueden ser nulos.\n");
        return NULL;
    }
    NodoMateria *cursor = lista->head;
    while (cursor != NULL) {
        if (strcmp(cursor->materia->nombre, nombre) == 0) {
            return cursor->materia;
        }
        cursor = cursor->proximo;
    }
    printf("No se encontro materia con nombre %s.\n", nombre);
    return NULL;
}

Materia *buscarMateriaPorId(ListaMaterias *lista, int id) {
    if (lista == NULL) {
        printf("La lista no puede ser nula.\n");
        return NULL;
    }
    NodoMateria *cursor = lista->head;
    while (cursor != NULL) {
        if (cursor->materia->id == id) {
            return cursor->materia;
        }
        cursor = cursor->proximo;
    }
    printf("No se encontro materia con ID %d.\n", id);
    return NULL;
}
void modificarNombreMateria(ListaMaterias *lista) {
    if (lista == NULL) {
        printf("La lista no puede ser nula.\n");
        return;
    }

    int id;
    printf("Ingrese el ID de la materia que desea modificar: \n");
    scanf("%d", &id);

    Materia *materia = buscarMateriaPorId(lista, id);
    if (materia == NULL) {
        printf("Materia con ID %d no encontrada.\n", id);
        return;
    }

    printf("Materia encontrada: %s\n", materia->nombre);

    char nuevoNombre[30];
    printf("Ingrese el nuevo nombre para la materia:");
    scanf("%s", nuevoNombre);

    materia->nombre = malloc(strlen(nuevoNombre) + 1);
    if (materia->nombre == NULL) {
        printf("Error: sin memoria para almacenar el nuevo nombre.\n");
        return;
    }
    strcpy(materia->nombre, nuevoNombre);

    printf("Nuevo nombre de la materia: %s\n", materia->nombre);
}
void imprimirListaMateriasPaginada(ListaMaterias *lista) {
    if (lista == NULL || lista->head == NULL) {
        printf("La lista de materias está vacía.\n");
        return;
    }

    NodoMateria *actual = lista->head;
    int contador = 0;

    while (actual != NULL) {
        if (contador == 5) {
            printf("[--------------------------------]\n");
            printf("Presione alguna tecla para ver la siguiente pagina...");
            limpiarBuffer();
            getchar();
            contador = 0;
        }

        printf("[--------------------------------]\n");
        imprimirDatosMateria(actual->materia);
        printf("Correlativas ID: [");
        for (int i = 0; i < sizeof(actual->materia->id_correlativas) / sizeof(int); ++i) {
            if (actual->materia->id_correlativas[i] == -1) {
                break;
            }
            printf("%d", actual->materia->id_correlativas[i]);
            if (actual->materia->id_correlativas[i + 1] != -1) {
                printf(",");
            }
        }
        printf("]\n");
        contador++;

        actual = actual->proximo;
    }

    if (contador > 0) {
        printf("[--------------------------------]\n");
    }
}