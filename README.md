# Tarea-1
Programa que carga los datos de los bomberos que trabajan en una estacion a partir de un archivo con extension .csv y permite modificar los bomberos con sus datos y la creacion de un
horario con ellos segun su disponibilidad.
Cada bombero contiene su nombre, rut y disponibilidad dentro de los siete dias de la semana.

Para compilar ejecutar comando gcc main.c list.c -o Tarea1
Luego ejecutar Tarea1.exe

Repositorio en GitHub https://github.com/beatrizsegurap/Tarea-1.git

ASPECTOS TECNICOS
    * Creamos una estructura de tipo bombero donde almacenamos el nombre, rut y disponibilidad de cada uno, cada uno de ellos dentro de una lista doblemente enlazada
    * Almacenamos el horario en una estrutura por cada dia y almacenada en una lista doblemente enlazada.
MEJORAS:
    * La funcion de crear horario puede ser mejorada haciendo que esta cuente para cada bombero la cantidad de dias que ya ha trabajado para evitar situaciones en las cuales un bombero con 6 dias de disponibilidad y una falta de personal resulten en el bombero asistiendo mas de los 5 dias.

    * La función mostrar horario solo se actualizara en caso de que se despida algun bombero al momento de volver a crear un horario


INTEGRANTES:
* Nicolas Eduardo Zarate Miethe
    Aspectos positivos:
    -Siempre atento a lo que sucede en los errores del codigo para poder solucionarlos
    - Plantea soluciones a diversos problemas. 
    Mejorar:Organizar mejor sus tiempos de trabajo. Mejorar el uso de ciertas estructuras.
    Puntaje:

* Ignacio Benjamin Cabrera Salazar
    Aspectos positivos:
    - Siempre disponible para avanzar en el trabajo.
    - Dispuesto a ayudar al grupo en lo que haga falta.
    - Busca soluciones a posibles problemas.
    Mejorar: 
    - Tratar de llevarse más trabajo, ya que a comparación del resto del grupo hicieron más partes del codigo.
    - Falta de dominio en el tema TDA.
    Puntaje:0

* Beatriz Macarena Segura Pasten
    Aspectos positivos: Mantiene el codigo ordenado y entendible, con los comentarios pertinentes. Toma la iniciativa y ayuda a resolver errores que se presentan a los demas integrantes.
    Ayuda constantemente y trabaja de forma eficaz y constante
    Mejorar: La organizacion con los demas integrantes del equipo para distribuir mejor lo que debia hacer cada uno. Comprender mejor lo solicitado en la tarea antes de programar, debio modificar varias partes por mal uso del tda en el avance.
    Puntaje:0

* Jose Ignacio Pailamilla Montecinos
    Aspectos positivos: buen manejo del tiempo
    Mejorar: el uso de algunas estructuras, y identificar los errores.
    Puntaje:0
 
