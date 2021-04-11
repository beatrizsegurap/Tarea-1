# Tarea-1
Programa que carga los datos de los bomberos que trabajan en una estacion a partir de un archivo con extension .csv y permite modificar los bomberos con sus datos y la creacion de un
horario con ellos segun su disponibilidad.
Cada bombero contiene su nombre, rut y disponibilidad dentro de los siete dias de la semana.

Para compilar ejecutar comando gcc main.c list.c -o Tarea1
Luego ejecutar Tarea1.exe

ASPECTOS TECNICOS
    * Creamos una estructura de tipo bombero donde almacenamos el nombre, rut y disponibilidad de cada uno, cada uno de ellos dentro de una lista doblemente enlazada
    * Almacenamos el horario en una estrutura por cada dia y almacenada en una lista doblemente enlazada.
MEJORAS:
    * La funcion de crear horario puede ser mejorada haciendo que esta cuente para cada bombero la cantidad de dias que ya ha trabajado para evitar situaciones en las cuales un bombero con 6 dias de disponibilidad y una falta de personal resulten en el bombero asistiendo mas de los 5 dias.

    * La función mostrar horario solo se actualizara en caso de que se despida algun bombero al momento de volver a crear un horario


INTEGRANTES:
* Nicolas Eduardo Zarate Miethe
    Aspectos positivos:Ayuda a resolver errores y dudas.
    Mejorar:Organizar mejor sus tiempos de trabajo. Mejorar el uso de ciertas estructuras.
    Puntaje:

* Ignacio Benjamin Cabrera Salazar
    Aspectos positivos:Busca posibles errores y sus soluciones.
    Mejorar:
    Puntaje:

* Beatriz Macarena Segura Pasten
    Aspectos positivos:Trabaja de manera constante y eficiente, ayuda los demas.
    Mejorar:
    Puntaje:0

* Jose Ignacio Pailamilla Montecinos
    Aspectos positivos:El buen uso del tiempo de trabajo.
    Mejorar:El manejo de algunas estructuras, el detectar errores.
    Puntaje:0
 
