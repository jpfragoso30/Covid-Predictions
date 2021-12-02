# Covid-Predictions

## La evolución de las muertes y la aplicación de vacunas en México en el tiempo

**Taller de Aplicaciones**
_Juan Pablo Fragoso, Regina Morfín, Sebastían Sedano, Santiago Zamora_

### Contexto

El surgimiento y propagación del COVID-19 ha provocado una de las peores crisis en la
historia moderna, desde un grave deterioro de la economía mundial, hasta el colapso
de sistemas de salud alrededor del mundo. Sin embargo, la consecuencia más grave
que ha dejado esta pandemia ha sido la devastadora cifra de vidas perdidas, que fluctúa
con el paso del tiempo manteniéndose en niveles alarmantes, superando
continuamente a cualquier tratamiento para los síntomas ocasionados por el virus.

**En México, llegó a ser la principal causa de muerte a inicios y mediados del 2020.**

La llegada de una vacuna significó la promesa de una baja considerable en el número
de personas infectadas y de pérdida de vida, por lo que decidimos aplicar los
conocimientos adquiridos durante el curso para predecir, con base en datos de
vacunación y de defunciones, el ritmo en que los decesos por síntomas de COVID-19
sean mínimos en proporción a la cantidad de personas con un esquema de vacunación
completo.

Estudios muestran que las vacunas contra el COVID-19 son efectivas para prevenir el
virus, y para evitar condiciones de salud y síntomas graves. La vacuna es crucial para
regresar a la vida lo más “normal” posible. La vacuna enseña al sistema inmunológico a
identificar y defenderse contra el virus. La vacuna de Pfizer es un 95% efectiva en la
prevención de la COVID-19. Moderna tiene efectividad contra el virus del 94,1%.
AstraZeneca, alcanza un 76% de eficacia. La vacuna de Johnson & Johnson, demostró
una eficacia del 72%. La vacuna ha generado controversia, con muchas personas
corriendo a aplicársela y gente que se rehúsa a ponérsela. A medida que se ha vacunado
la gente, ha sido posible regresar a actividades laborales, educacionales y recreativas.
En algunos países se ha abandonado el uso de cubre-bocas y ha nivel mundial, se ha ido
reintegrando la convivencia social.

### El proyecto consiste en analizar los datos de la cantidad de vacunas y muertes por COVID en México a través del tiempo.

-   [x] Se lee un archivo .csv con las aplicaciones de vacunas y otro con las muertes.
-   [x] Los datos son leídos en el DataShell.
-   [ ] Los datos son procesados con ecuaciones de Euler.
-   [x] Se genera un archivo .csv con los resultados.
-   [x] Los resultados son graficados para ser visualizados con facilidad.

---

## Modos de Ejecucion

### Modo Automatizado

Al descargar todo lo contenido en este repositorio, lo unico que se debe realizar para poder tener una ejecucion rapida de la aplicacion, es tener una base de datos en el formato de la base contenida en CsvEntr, y ejecutar el comando
`make app` o `make`
para ejecutar la aplicacion sin tener que realizar todos los comandos previos.

### Modo Semi-Automatizado

Para eliminar el posible cache guardado al compilar en un usuario diferente
`make clearCache`.

Para eliminar otros archivos generados por la compilacion
`make clean`.

Para compilar y generar el ejecutable
`make compile`.

Para ejecutar la aplicacion
`make execute`.

### Modo Manual

En este modo se tiene que tener en mente todo lo mencionado anterior, se puede limpiar el cache y otros archivos generados, y para realizar la compilacion de la aplicacion, se debe de navegar a los archivos del codigo fuente con
`cd src/build`
y ejecutar los comandos
`cmake ..`
`make`
dentro de este directorio.

Acto siguiente debe ser dirigirse al directorio de build en el root, por lo que se ejecuta
`cd ../../`
y ahora se puede dirigir a build con
`cd build`
para poder realizar los comandos que usamos previamente
`cmake ..`
`make`.

Esto deberia generar el ejecutable, que se puede ejecutar con
`./COVID_PREDICTIONS`.

### Documentacion
https://docs.google.com/document/d/1P0O0_q3sPRlncjsWMo1ecGuPVoOq8769YW-r99BYwKM/edit?usp=sharing
