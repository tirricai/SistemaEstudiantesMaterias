#ifndef CEJP_ESTUDIANTE_H
#define CEJP_ESTUDIANTE_H
#include "fechas.h"
#include "lista_materiasEnCurso.h"
#include "materias.h"

typedef struct Estudiante {
    char *nombre;
    int dni;
    Fecha *fechaNacimiento;
    listaMateriasEnCurso *listaEnCurso;
} Estudiante;

Estudiante *crearEstudiante(char *nombre, int dni, Fecha *fechaNacimiento);
void asignarNombre(Estudiante *estudiante);
void asignarDNI(Estudiante *estudiante);
void asignarFechaDeNacimiento(Estudiante *estudiante);
void modificarEstudiante(Estudiante *estudiante);
void anotarseEnMateria(Estudiante *estudiante, Materia *materia);
void setNota(Estudiante *estudiante);
void imprimirDatosEstudiante(Estudiante *estudiante);
void anotarseEnMateria(Estudiante *estudiante, Materia *materia);
int puedeAnotarse(Estudiante *estudiante, Materia *materia);
int estaCursando(Estudiante *estudiante, Materia *materia);
float calcularPromedioEstudiante(Estudiante *estudiante);

#endif
