#include <stdio.h>
#include "fechas.h"
#include <malloc.h>
#include <time.h>

int validacionFecha(Fecha *fecha){
    if(fecha->anio < 1900 || fecha->anio > 2100){
        return 0;
    }
    if(fecha->mes < 1 || fecha->mes > 12){
        return 0;
    }
    if(fecha->dia < 1 || fecha->dia > 31){
        return 0;
    }

    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (fecha->dia > diasPorMes[fecha->mes - 1]) {
        return 0;
    }

    return 1;
}
Fecha *crearFecha(int dia, int mes, int anio) {
    Fecha *nuevaFecha = malloc(sizeof(Fecha));
    if (nuevaFecha == NULL) {
        printf("Error: No se pudo asignar memoria para la nueva fecha.\n");
        return NULL;
    }

    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;

    if (!validacionFecha(nuevaFecha)) {
        printf("Error: La fecha ingresada no es valida.\n");
        free(nuevaFecha);
        return NULL;
    }

    return nuevaFecha;
}
Fecha *obtenerFechaActual() {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    Fecha *fechaActual = malloc(sizeof(Fecha));
    if (fechaActual == NULL) {
        printf("Error: No se pudo asignar memoria para la fecha actual.\n");
        return NULL;
    }

    fechaActual->dia = tm->tm_mday;
    fechaActual->mes = tm->tm_mon + 1;
    fechaActual->anio = tm->tm_year + 1900;

    return fechaActual;
}
int esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int obtenerDiasEnMes(int mes, int anio) {
    if (mes < 1 || mes > 12) {
        printf("Error: Mes invalido.\n");
        return -1;
    }

    int dias_por_mes[] = {31, 28 + esBisiesto(anio), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return dias_por_mes[mes - 1];
}

Fecha *calcularEdad(Fecha *fechaNacimiento) {
    Fecha *fechaActual = obtenerFechaActual();
    if (fechaActual == NULL) {
        printf("Error: No se pudo obtener la fecha actual.\n");
        return NULL;
    }

    int anios = fechaActual->anio - fechaNacimiento->anio;
    int meses = fechaActual->mes - fechaNacimiento->mes;
    int dias = fechaActual->dia - fechaNacimiento->dia;

    if (meses < 0 || (meses == 0 && dias < 0)) {
        anios--;
        meses += 12;
    }
    if (dias < 0) {
        meses--;
        dias += obtenerDiasEnMes(fechaActual->mes - 1, fechaActual->anio);
    }

    Fecha *edad = malloc(sizeof(Fecha));
    if (edad == NULL) {
        printf("Error: No se pudo asignar memoria para la estructura de fecha.\n");
        free(fechaActual);
        return NULL;
    }

    edad->anio = anios;
    edad->mes = meses;
    edad->dia = dias;

    free(fechaActual);
    return edad;
}
int compararFechas(Fecha fecha1, Fecha fecha2) {
    if (fecha1.anio < fecha2.anio)
        return -1;
    else if (fecha1.anio > fecha2.anio)
        return 1;
    else {
        if (fecha1.mes < fecha2.mes)
            return -1;
        else if (fecha1.mes > fecha2.mes)
            return 1;
        else {
            if (fecha1.dia < fecha2.dia)
                return -1;
            else if (fecha1.dia > fecha2.dia)
                return 1;
            else
                return 0;
        }
    }
}