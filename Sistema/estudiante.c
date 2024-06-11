#include <stdio.h>
#include <malloc.h>
#include "fechas.h"
#include "estudiante.h"
#include "lista_materiasEnCurso.h"
#include "nodo_materiaestudiante.h"
#include "materias.h"
#include <string.h>

Estudiante *crearEstudiante(char *nombre, int dni, Fecha *fechaNacimiento){
    Estudiante *nuevoEstudiante = malloc(sizeof(Estudiante));
    nuevoEstudiante->nombre = nombre;
    nuevoEstudiante->dni = dni;
    nuevoEstudiante->fechaNacimiento = fechaNacimiento;
    nuevoEstudiante->listaEnCurso = crearNuevaListaMateriasEnCurso();
    return nuevoEstudiante;
}

void asignarNombre(Estudiante *estudiante) {
    printf("Ingrese el nombre para el estudiante: ");
    char nuevoNombre[100];

    scanf("%s", nuevoNombre);

    estudiante->nombre = malloc(strlen(nuevoNombre) + 1);
    if (estudiante->nombre == NULL) {
        printf("Error: sin memoria para almacenar el nuevo nombre.\n");
        return;
    }
    strcpy(estudiante->nombre, nuevoNombre);

    printf("Nombre del estudiante: %s\n", estudiante->nombre);
}

void asignarDNI(Estudiante *estudiante) {
    printf("Ingrese el DNI: ");
    scanf("%d", &estudiante->dni);
    printf("DNI: %d\n", estudiante->dni);
}

void asignarFechaDeNacimiento(Estudiante *estudiante) {
    int dia, mes, anio;
    printf("Ingrese el nuevo dia de nacimiento: ");
    scanf("%d", &dia);
    printf("Ingrese el nuevo mes de nacimiento: ");
    scanf("%d", &mes);
    printf("Ingrese el nuevo anio de nacimiento: ");
    scanf("%d", &anio);

    Fecha *nuevaFecha = crearFecha(dia, mes, anio);

    if(nuevaFecha != NULL){
        free(estudiante->fechaNacimiento);
        estudiante->fechaNacimiento = nuevaFecha;
        printf("\n");
        printf("Fecha de nacimiento actualizada a: %d/%d/%d\n",
               estudiante->fechaNacimiento->dia,
               estudiante->fechaNacimiento->mes,
               estudiante->fechaNacimiento->anio);
    }
    return;
}
void modificarEstudiante(Estudiante *estudiante) {
    int opcion;
    do {
        printf("\nSeleccione lo que desea modificar:\n");
        printf("1. Nombre\n");
        printf("2. DNI\n");
        printf("3. Fecha de nacimiento\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                asignarNombre(estudiante);
                break;
            case 2:
                asignarDNI(estudiante);
                break;
            case 3:
                asignarFechaDeNacimiento(estudiante);
                break;
            case 4:
                printf("Saliendo del menu...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4);
}

void anotarseEnMateria(Estudiante *estudiante, Materia *materia) {
    if (estudiante == NULL || materia == NULL) {
        printf("Error: Estudiante o materia no pueden ser nulos.\n");
        return;
    }

    if (estudiante->listaEnCurso->head == NULL) {
        estudiante->listaEnCurso = crearNuevaListaMateriasEnCurso();
        if (estudiante->listaEnCurso == NULL) {
            printf("Error: No se pudo crear la lista de materias en curso.\n");
            return;
        }
    }
    int puedeanotarse = puedeAnotarse(estudiante, materia);

    if (puedeanotarse == 0 && estaCursando(estudiante,materia) != 0){
        NodoMateriaEstudiante *nuevoNodo = crearNuevoNodoMateriaEstudiante(materia, -1);
        if (nuevoNodo == NULL) {
            printf("Error: No se pudo crear el nodo para la materia en curso.\n");
            return;
        }
        agregarMateriaEnCurso(estudiante->listaEnCurso, nuevoNodo);
        printf("El estudiante %s se ha anotado en la materia %s.\n", estudiante->nombre, materia->nombre);
    }
}

int puedeAnotarse(Estudiante *estudiante, Materia *materia){
    NodoMateriaEstudiante *current;
    int aux = 0;

    for (int i = 0; i < sizeof(materia->id_correlativas)/(sizeof(int)) ; ++i) {
        if (materia->id_correlativas[i] == -1){
            return 0;
        }
        current = estudiante->listaEnCurso->head;
        while(current != NULL){
            printf("Nota: %d\n",current->nota);
            printf("%s\n",current->materia->nombre);
            printf("%d\n",materia->id_correlativas[i]);
            if (materia->id_correlativas[i] == current->materia->id){
                if (current->nota <= 4){
                    printf("No se puede anotar debido a no haber aprobado la materia %d\n",materia->id_correlativas[i]);
                    return -1;
                }
                aux = 1;
            }
            current = current->proximo;
        }
        if (aux == 0){
            printf("No se pudo anotar debido a no haber cursado la materia: %d\n", materia->id_correlativas[i]);
            return -1;
        }
        aux = 0;
    }

    if (estudiante->listaEnCurso->head == NULL && materia->id_correlativas[0] == -1){
        return 0;
    }

    return 0;
}

int estaCursando(Estudiante *estudiante, Materia *materia){
    if (estudiante == NULL || materia == NULL){
        return -1;
    }

    NodoMateriaEstudiante *current = estudiante->listaEnCurso->head;

    while (current != NULL && current->materia->id != materia->id){
        current = current->proximo;
    }
    if (current == NULL){
        return -1;
    }
    return 0;
}

void setNota(Estudiante *estudiante) {
    if (estudiante == NULL) {
        printf("Error: Estudiante nulo.\n");
        return;
    }

    if (estudiante->listaEnCurso == NULL || estudiante->listaEnCurso->head == NULL) {
        printf("El estudiante no tiene materias para modificar.\n");
        return;
    }

    printf("Materias en curso para %s:\n", estudiante->nombre);
    imprimirListaMateriasEnCurso(estudiante->listaEnCurso);

    int opcion;
    printf("Seleccione el id de la materia a la que desea asignar la nota: ");
    scanf("%d", &opcion);

    NodoMateriaEstudiante *cursor = estudiante->listaEnCurso->head;
    while(cursor != NULL){
        if (cursor->materia->id == opcion){
            int nuevaNota;
            printf("Ingrese la nueva nota para la materia %s: \n", cursor->materia->nombre);
            scanf("%d", &nuevaNota);
            if (nuevaNota > cursor->nota){
                cursor->nota = nuevaNota;
                printf("Nota actualizada correctamente para la materia %s.\n", cursor->materia->nombre);
                return;
            }
            printf("La nota previa de %s es mayor a la nota actual\n", cursor->materia->nombre);
            return;
        }
        cursor = cursor->proximo;
    }

    if (cursor == NULL) {
        printf("Error: Materia no encontrada.\n");
        return;
    }
}
void imprimirDatosEstudiante(Estudiante *estudiante){
    if (estudiante == NULL) {
        printf("Estudiante no encontrado.\n");
        return;
    }
    printf("[--------------------------------]\n");
    printf("Nombre: %s - DNI: %d - Fecha de nacimiento: %d/%d/%d\n",
           estudiante->nombre,
           estudiante->dni,
           estudiante->fechaNacimiento->dia,
           estudiante->fechaNacimiento->mes,
           estudiante->fechaNacimiento->anio);

    NodoMateriaEstudiante *cursor = estudiante->listaEnCurso->head;
    if (cursor == NULL){
        printf("Actualmente sin materias en curso\n");
        return;
    }
    printf("| Lista de materias en curso: |\n");
    while (cursor != NULL) {
        imprimirDatosMateria(cursor->materia);
        printf("| Nota: %d |\n", cursor->nota);
        cursor = cursor->proximo;
    }
}

float calcularPromedioEstudiante(Estudiante *estudiante) {
    if (estudiante == NULL || estudiante->listaEnCurso == NULL || estudiante->listaEnCurso->head == NULL) {
        printf("El estudiante no tiene materias en curso.\n");
        return 0.0;
    }

    NodoMateriaEstudiante *actual = estudiante->listaEnCurso->head;
    int sum = 0;
    int cantidadMaterias = 0;

    while (actual != NULL) {
        if (actual->nota != -1) {
            sum += actual->nota;
            cantidadMaterias++;
        }
        actual = actual->proximo;
    }

    if (cantidadMaterias == 0) {
        return 0.0;
    }

    return (float)sum / cantidadMaterias;
}