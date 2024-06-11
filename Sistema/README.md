# CEJP
Repositorio para el TP final de AyP III - Programación de bajo nivel

# Clase Estudiante
    La clase estudiante se compone de 4 atributos principales:
        1. char *nombre = para almacenar el nombre de manera dinamica
        2. int dni 
        3. Fecha *fechadenacimiento
        4. listaMateriasEnCurso = es una lista que almacena las materias en curso justamente
   
### Metodos correspondientes a estudiante
        
    CrearEstudiante()
        Recibe por parametro el nombre, el dni y la fecha de nacimiento
        Devuelve NULL, en caso de que no haya memoria o un objeto de tipo estudiante

    AsignarNombre() - AsignarDNI() - AsignarFechaDeNacimiento()
        Estas funciones reciben por parametro un estudiante y modifican el atributo correspondiente

    ModificarEstudiante()
        Recibe un estudiante por parametro, dentro contiene un menu que le permite al usuario modificar 
        el nombre, el dni o la fecha de nacimiento del estudiante

    AnotarseEnMateria()
        Recibe por parametro un estudiante y una materia
        Dentro de esta funcion se llama a las funciones puedeAnotarse y estaCursando:       
            *puedeAnotarse verifica que el estudiante haya cursado las correlativas correspondientes y que las haya aprobado
            *estaCursando verifica si el estudiante la esta cursando actualmente
        Una vez que se validan estos controles y puedo anotar al estudiante a la materia, agrego esta materia a la lista de materias
        en curso del estudiante

    setNota()
        Recibe por parametro un estudiante
        Busca la materia en la lista de materias en curso del estudiante y modifica la nota del nodo que corresponde con esa materia

    imprimirDatosEstudiante()
        Un simple print de los datos del estudiante

    calcularPromedioEstudiante()
        Recibe un estudiante, recorre la lista de materias en curso y calcula el promedio en base a eso

# Clase Materia
    La clase materia esta compuesta por 3 atributos:
        1. char *nombre = un puntero a char para el nombre
        2. int id 
        3. id_correlativas[5] = me permite almacenar el id de las materias correlativas | Cuando se crea una nueva
            materia, las posiciones del array se inicializan en -1

### Metodos correspondientes a materia
    crearMateria()
        Recibe por parametro el nombre y el id y los inicializa
    
    modificarIDMateriaGeneral() - modificarNombreMateriaGeneral()
        Reciben una materia y se setean los atributos correspondientes
    
    obtenerNombreMateria() - obtenerIDMateria()
        Un get para obtener cada atributo
    
    imprimirDatosMateria()
        Un print
    
    agregarCorrelativas()
        Recibe la materia y su correlativa, el id de la materia correlativa es agregada al array de id_correlativa de
        la materia pasada por parametro, en caso de que el array este ocupado, lanza un print con el error.

# Clase Fecha
    Decidimos el uso de una estructura para las fechas, para poder manejarlas de una manera mas personalizada
    Fecha se compone de tres atributos enteros, dia, mes y anio

### Metodos de la clase Fecha
    validacionFecha()
        Verifica que la fecha ingresada primero, sea correcta y segundo que sea coherente (no vamos a crear personas
        que nacieron antes del 1900) para poner un limite.
    
        Se valida el anio, el mes y el dia (en el caso de los dias, tenemos un array con la cantidad de dias de cada mes, para
        que la fecha sea correcta)
        
        Retorna 1 en caso de que la fecha sea valida y 0 en caso de que no.

    crearFecha()
        Se invoca a malloc para pedir memoria para este nuevo objeto, se asigna el dia, mes y anio elegido por el usuario
        al nuevo objeto fecha, y se valida que este objeto sea correcto. Finalmente se devuelve un objeto fecha correcto.

    calcularEdad()
        Se le pasa una fecha por parametro y calcula la edad correspondiente (en dias, meses y anios)
            (Se restan anios, meses y dias y se obtiene el valor positivo de cada uno)

    obtenerFechaActual()
        devuelve un objeto Fecha con la fecha actual

    esBiesto()
        Me permite saber si un anio en especifico es bisiesto o no

# Lista Estudiantes
    Compuesta por NodoEstudiante (Estudiante, *proximo, *prev), almacena todos los estudiantes que se vayan creando.

### Metodos de lista estudiantes
    crearListaEstudiantes()
        Se comprueba que haya memoria y devuelve una lista
    agregarEstudiante()
        Agrega un estudiante a la lista, preferentemente siempre al final
    eliminarEstudiante()
        Comprueba si el estudiante es el primero o ultimo de la lista, en caso de que no este en estas posiciones de la lista,
        la recorre buscando al estudiante y lo elimina
    imprimirListaEstudiantes()
        Print de la lista
    buscarEstudiantePorDNI()
        Busca en la lista de estudiantes, el dni pasado por parametro.
        Se recorre la lista, en caso de que coincida el dni con el dni del estudiante, se retorna al estudiante corres-
        pondiente
    buscarEstudiantesPorNombre()
        Al igual que el metodo anterior, se busca que coincida el nombre pasado por parametro con el del estudiante mientras
        se recorre la lista, en caso de encontrarlo lo devuelvo, si no lo encuentro, devuelvo NULL.
    buscarEstudiantesPorRangoEdad()
        Se le pasa por parametro la lista y dos parametros mas: el minimo de edad y el maximo
        Se arma una lista con los estudiantes dentro de este rango. 
        Con la funcion calcularEdad (de Fecha) se calcula la edad, y si corresponde se agrega a la lista
    imprimirListaEstudiantesPaginada()
        Print con paginado, se pone un limite de 5 elementos por pagina
    exportarACSV
        Como su nombre lo indica, permite exportar a los estudiantes, con su Nombre, DNI y el id de materias en curso a un
        CSV
# Lista Materias
    Compuesto por NodoMateria (Materia y proximo)
    Aqui se almacenan todas las materias que se vayan creando, para tenerlas organizadas.

### Metodos de la lista materias
    crearNuevaListaMaterias()
        Verifica si hay memoria disponible
        Devuelve NULL en caso de que no haya memoria o una lista de materias vacia
    agregarMateria()
        Verifica que haya memoria y agrega la materia pasada por parametro, en el lugar que corresponda
    imprimirMaterias()
        Print de los datos de las materias
    eliminarMateriaListaGeneral()
        Esta funcion es muy importante, recibe por parametro una lista de materias, una lista de estudiantes y la materia
        en cuestion para eliminarla
        Esta funcion primeramente busca la materia en la lista de las materias en curso de cada estudiante, para eliminarla,
        ya que si una materia es eliminada, no puedo cursarla.
        Una vez que se elimina de la lista de cada estudiante, se elimina de su lista de materias
    buscarMateriaPorId() -    buscarMateriaPorNombre()
        Se pasa el id/nombre por parametro, se busca el match entre el id/nombre del buscado y el de la materia de la lista que estoy iterando
        En caso de que coincidan, devuelvo la materia
    modificarNombreMateria()
        Un set para el nombre de la materia
    imprimirListaMateriasPaginada()
        Print con paginado
        
# Lista En Curso
    Almacena las materias en curso de cada estudiante
    Compuesta por NodoMateriaEstudiante (almacena la materia, la nota y un puntero al proximo)

### Metodos de la lista en curso
    crearNuevaListaMateriaEnCurso()
        Verifica si hay memoria y devuelve NULL o una lista de materias en curso
    agregarMateriaEnCurso()
        Agregar una materia a la lista de materias en curso
    imprimirListaMateriasEnCurso()
        Print de las materias en curso del estudiante
    modificarNota()
        Se busca la materia que coincida con el id pasado por parametro, en caso de que haya coincidencia, se encontro
        la materia y se setea la nota
    eliminarMateriaEnCurso()
        Se elimina la materia pasada por parametro
        Se itera la lista buscando que coincida el id de la materia pasada por parametro con la de la lista
        Si hay match, se elimina de la lista de materias en curso.

#### Trabajo realizado por: Juan Pablo Miguel, Enzo Mauas, Camila Di Mario, Pedro De Gaspari