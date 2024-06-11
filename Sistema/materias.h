#ifndef CEJP_MATERIA_H
#define CEJP_MATERIA_H
typedef struct MateriaStruct {
    char *nombre;
    int id;
    int id_correlativas[5];
} Materia;

void limpiarBuffer();
Materia* crearMateria(char *nombre, int id);
void modificarIDMateriaGeneral(Materia *materia);
void modificarNombreMateriaGeneral(Materia *materia);
char *obtenerNombreMateria(Materia *materia);
int obtenerIDMateria(Materia *materia);
void imprimirDatosMateria(Materia *materia);
void agregarCorrelativas(Materia *materia,Materia *correlativa);
#endif
