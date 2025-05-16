
# Proyecto Sequence Classifier

Este repositorio contiene un clasificador de secuencias biológicas (ADN, ARN, proteínas) con pruebas automáticas usando GoogleTest.

---

## Script de ejecución: `run.sh`

Este script automatiza la compilación, ejecución de tests y la ejecución del programa principal con un archivo FASTA de entrada.

---

### Permisos

Antes de usar el script, dale permiso de ejecución con:

```bash
chmod +x run.sh
````

---

### Comandos disponibles

Ejecuta el script con uno de los siguientes comandos:

| Comando                             | Descripción                                                                                               |
| ----------------------------------- | --------------------------------------------------------------------------------------------------------- |
| `./run.sh all`                      | Limpia, configura, compila todo el proyecto y ejecuta los tests con `test_runner`.                        |
| `./run.sh test`                     | Solo ejecuta los tests compilados con `test_runner` (sin recompilar).                                     |
| `./run.sh ctest`                    | Ejecuta los tests usando `ctest` en modo verbose para salida detallada (sin recompilar).                  |
| `./run.sh main <archivo_fasta.txt>` | Ejecuta el programa principal `main_app` con el archivo FASTA especificado dentro del directorio `data/`. |

---

### Ejemplos de uso

* Ejecutar todo el flujo (limpiar, compilar y testear):

```bash
./run.sh all
```

* Solo correr los tests ya compilados con el binario `test_runner`:

```bash
./run.sh test
```

* Correr los tests usando CTest (más detallado):

```bash
./run.sh ctest
```

* Ejecutar el programa principal con un archivo FASTA de prueba llamado `example.fasta` ubicado en `data/`:

```bash
./run.sh main example.fasta
```

Si el archivo no existe en `data/`, el script mostrará un error.

---

### Requisitos

* Tener instalado CMake.
* Tener instalado un compilador C++ compatible (gcc, clang).
* Tener permisos para ejecutar el script (`chmod +x run.sh`).
* El directorio `data/` debe contener los archivos FASTA para pruebas y ejecución.

---

### Notas

* El script crea un directorio `build/` donde se compila todo el proyecto.
* Los tests están basados en GoogleTest y pueden ejecutarse con `test_runner` o con `ctest`.
* Usa el script para facilitar el flujo de desarrollo y pruebas.

---

