#ifndef CEJP_FECHAS_H
#define CEJP_FECHAS_H

typedef struct Fecha{
    int dia;
    int mes;
    int anio;
} Fecha;

int validacionFecha(Fecha *fecha);
Fecha *crearFecha(int dia, int mes, int anio);
Fecha *calcularEdad(Fecha *fechaNacimiento);
Fecha *obtenerFechaActual();
int esBisiesto(int anio);
int obtenerDiasEnMes(int mes, int anio);
int compararFechas(Fecha fecha1, Fecha fecha2);
#endif
