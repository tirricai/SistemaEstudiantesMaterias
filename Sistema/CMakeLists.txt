cmake_minimum_required(VERSION 3.27)
project(Sistema)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sistema main.c
        estudiante.c
        fechas.c
        lista_estudiantes.c
        lista_materias.c
        lista_materiasEnCurso.c
        materias.c
        nodo_estudiante.c
        nodo_materia.c
        nodo_materiaestudiante.c
)
