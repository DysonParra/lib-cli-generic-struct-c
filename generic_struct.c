/*
 * @fileoverview    {FileName}
 *
 * @version         2.0
 *
 * @author          Dyson Arley Parra Tilano <dysontilano@gmail.com>
 *
 * @copyright       Dyson Parra
 * @see             github.com/DysonParra
 *
 * History
 * @version 1.0     Implementation done.
 * @version 2.0     Documentation added.
 */
#include "generic_struct.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

CALLING void printArray(char* array);
CALLING void sprintArray(char* output, char* input);
CALLING void UpdateGenericStrucsLevels(GenericStruct* root, int level);
CALLING void getGenericStructPrintOut(GenericStruct* generic, int position, int open, int debug, char* output);

#if (!defined STATIC_LIB_) && (!defined NO_DLL_MAIN_)
/**
 * Entrada principal de la dll (creado si no se indica que es biblioteca estática)
 *
 * @param instance identificador del módulo.
 * @param reason   razón de la llamada.
 * @param reserved argumento reservado.
 * @return {@code TRUE} si se completó exitosamente la llamada, caso contrario {@code FALSE}.
 */
BOOL APIENTRY DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    /*
     * Evalúa la razón de la llamada a la dll.
     */
    switch (reason) {
        /*
         * Se cargó la dll en el proceso actual.
         */
        case DLL_PROCESS_ATTACH:
            // printf("%s\n", "DLL_PROCESS_ATTACH");
            break;

        /*
         * Se liberó la dll en el proceso actual.
         */
        case DLL_PROCESS_DETACH:
            // printf("%s\n", "DLL_PROCESS_DETACH");
            break;

        /*
         * Se cargó la dll en un nuevo hilo.
         */
        case DLL_THREAD_ATTACH:
            // printf("%s\n", "DLL_THREAD_ATTACH");
            break;

        /*
         * Se liberó la dll en el nuevo hilo.
         */
        case DLL_THREAD_DETACH:
            // printf("%s\n", "DLL_THREAD_DETACH");
            break;
    }

    return TRUE;
}
#endif

/**
 * FIXME: Definición de {@code printArray}.
 * Imprime un array sin los caracteres de escape.
 */
CALLING void printArray(char* array) {
// Crea macro para imprimir caracteres de escape.
#define printChar(character)      \
    case character:               \
        printf("%s", #character); \
        break

    for (int i = 0; i < strlen(array); i++) {   // Recorre el array de entrada.
        switch (array[i]) {                     // Evalua el caracter actual.
            printChar('\n');                    // Imprime el caracter de escape.
            printChar('\r');                    // Imprime el caracter de escape.
            printChar('\t');                    // Imprime el caracter de escape.
            printChar('\a');                    // Imprime el caracter de escape.
            printChar('\b');                    // Imprime el caracter de escape.
            printChar('\v');                    // Imprime el caracter de escape.
                // printChar('\?');             // Imprime el caracter de escape.
                // printChar('\"');             // Imprime el caracter de escape.

            default:                            // Si no es un caracter de escape.
                printf("%c", array[i]);         // Imprime el caracter actual.
                break;                          // Termina de evaluar el caracter actual.
        }
    }

#undef printChar                                // Borra macro para imprimir caracteres de escape.
}

/**
 * FIXME: Definición de {@code sprintArray}.
 * Copia un array de entrada en otro sin los caracteres de escape.
 */
CALLING void sprintArray(char* output, char* input) {
// Crea macro para imprimir caracteres de escape.
#define printChar(character)                                \
    case character:                                         \
        sprintf(&output[strlen(output)], "%s", #character); \
        break

    for (int i = 0; i < strlen(input); i++) {                       // Recorre el array de entrada.
        switch (input[i]) {                                         // Evalua el caracter actual.
            printChar('\n');                                        // Imprime el caracter de escape.
            printChar('\r');                                        // Imprime el caracter de escape.
            printChar('\t');                                        // Imprime el caracter de escape.
            printChar('\a');                                        // Imprime el caracter de escape.
            printChar('\b');                                        // Imprime el caracter de escape.
            printChar('\v');                                        // Imprime el caracter de escape.
                // printChar('\?');                                 // Imprime el caracter de escape.
                // printChar('\"');                                 // Imprime el caracter de escape.

            default:                                                // Si no es un caracter de escape.
                sprintf(&output[strlen(output)], "%c", input[i]);   // Imprime el caracter actual.
                break;                                              // Termina de evaluar el caracter actual.
        }
    }

#undef printChar                                                    // Borra macro para imprimir caracteres de escape.
}

/**
 * FIXME: Definición de {@code UpdateGenericStrucsLevels}.
 * Actualiza el nivel de un GenericStruct y sus descendientes.
 */
CALLING void UpdateGenericStrucsLevels(GenericStruct* root, int level) {
    GenericStruct* aux;                                                 // Crea apuntador a un GenericStruct para recorrer los hermanos del JsonItem.
    aux = root;                                                         // A aux le lleva una copia del GenericStruct parámetro.

    if (aux != NULL)                                                    // Si el GenericStruct parámetro no está vacío.
        while (aux != NULL) {                                           // Recorre los hermanos de aux.
            aux->level = level;

            if (aux->numberChilds)                                      // Si aux tiene hijos.
                UpdateGenericStrucsLevels(aux->firstChild, level + 1);  // Cuenta cada uno de los hijos de aux.

            aux = aux->nextBrother;                                     // Pasa al siguiente hermano de aux.
        }
}

/**
 * FIXME: Definición de {@code setValue}.
 * Obtiene un string con el valor indicado en el heap.
 */
LANGUAGE DLLIMPORT CALLING char* setValue(char* value) {
    int valueSize = 0;                                          // Crea variable que dirá la cantidad de caracteres del valor del XmlItem a crear.
    char* newValue;

    if (value != NULL) {                                        // Si se indicó valor.
        valueSize = strlen(value) + 1;                          // A valueSize le lleva la cantidad de letras de value.
        newValue = (char*)malloc(valueSize * sizeof(char));     // Reserva espacio en el heap para el valor.
        memcpy(newValue, value, valueSize);                     // Asigna valor al item actual.
    } else
        newValue = (char*)calloc(1, sizeof(char));              // Pone como valor el caracter nulo.

    return newValue;
}

/**
 * FIXME: Definición de {@code newGenericStruct}.
 * Crea un nuevo GenericStruct y asociarlo a un GenericStruct parámetro brother que dirá si es un hermano (diferente a 0), o un hijo (0).
 */
LANGUAGE DLLIMPORT CALLING GenericStruct* newGenericStruct(char* identifier, GenericStruct* ref, int brother, void* concrete, void (*getPrintValue)(GenericStruct*, int, int, int, char*)) {
    GenericStruct* nuevo;                                       // Declara un nuevo GenericStruct.
    nuevo = (GenericStruct*)malloc(sizeof(GenericStruct));      // Inicializa el GenericStruct en el heap.

    nuevo->concrete = concrete;                                 // Inicializa la estrucura concreta.
    nuevo->identifier = setValue(identifier);

    nuevo->getPrintValue = (getPrintValue != NULL) ? getPrintValue : getGenericStructPrintOut;

    nuevo->level = 1;                                           // Inicializa el campo level en 1 por defecto.
    nuevo->numberChilds = 0;                                    // Inicializa el campo numberChilds de nuevo en 0.

    nuevo->father = NULL;                                       // A nuevo le pone su padre en NULL.
    nuevo->prevBrother = NULL;                                  // A nuevo le pone su anterior hermano en NULL.
    nuevo->nextBrother = NULL;                                  // A nuevo le pone su siguiente hermano en NULL.
    nuevo->firstChild = NULL;                                   // A nuevo le pone su primer hijo en NULL.

    if (ref != NULL && brother) {                               // Si se indicó que se creará un hermano de la estructura de referencia.
        nuevo->level = ref->level;                              // A nuevo le pone el mismo nivel que su hermano.
        GenericStruct* last = ref;                              // Crea la estructura apuntando a ref.

        while (last->nextBrother != NULL)                       // Mientras no encuentre al último hemano de ref.
            last = last->nextBrother;                           // A last le lleva su siguiente hermano.

        nuevo->prevBrother = last;                              // A nuevo le pone su anterior hermano como last.
        last->nextBrother = nuevo;                              // A last le pone su siguiente hermano como nuevo.

        if (ref->father != NULL) {                              // Si ref tiene padre.
            nuevo->father = ref->father;                        // A nuevo le pone el mismo padre que tiene ref.
            nuevo->father->numberChilds++;                      // Aumenta la cantidad de hijos del padre de nuevo.
        }
    }
    elif (ref != NULL && !brother) {                            // Si se indicó que se creará un hijo de la estructura de referencia.
        nuevo->level = ref->level + 1;                          // A nuevo le pone un nivel más su padre.
        nuevo->father = ref;                                    // Pone ref como el padre de nuevo.
        nuevo->father->numberChilds++;                          // Aumenta la cantidad de hijos del padre de nuevo.

        if (ref->firstChild == NULL) {                          // Si ref no tiene hijos.
            ref->firstChild = nuevo;                            // Pone que nuevo es el primer hijo de ref.
        } else {                                                // Si ref ya tenía hijos.
            GenericStruct* child = ref->firstChild;             // Crea la estructura apuntando al primer hijo de ref.
            while (child->nextBrother != NULL)                  // Mientras no encuentre al último hermano de child (último hijo de ref).
                child = child->nextBrother;                     // A child le lleva su siguiente hermano.

            nuevo->prevBrother = child;                         // Pone que el anterior hermano de nuevo es child.
            child->nextBrother = nuevo;                         // Pone que el siguiente hermano de child es nuevo.
        }
    }

    return nuevo;
}

/**
 * FIXME: Definición de {@code addGenericStructChild}.
 * Asigna un nuevo hijo a un GenericStruct.
 */
LANGUAGE DLLIMPORT CALLING void addGenericStructChild(GenericStruct* father, GenericStruct* newChild) {
    if (father != NULL && newChild != NULL) {                   // Si ninguno de los GenericStruct es NULL.
        newChild->father = father;                              // Pone father como el padre de newChild.
        newChild->father->numberChilds++;                       // Aumenta la cantidad de hijos de father.

        if (father->firstChild == NULL)                         // Si father no tiene hijos.
            father->firstChild = newChild;                      // Pone que newChild es el primer hijo de father.
        else {                                                  // Si father ya tenía hijos.
            GenericStruct* child = father->firstChild;          // Crea GenericStruct apuntando al primer hijo de father.
            while (child->nextBrother != NULL)                  // Mientras no encuentre al último hermano de child (último hijo de father).
                child = child->nextBrother;                     // A child le lleva su siguiente hermano.

            newChild->prevBrother = child;                      // Pone que el anterior hermano de newChild es child.
            child->nextBrother = newChild;                      // Pone que el siguiente hermano de child es newChild.
        }

        UpdateGenericStrucsLevels(newChild, father->level + 1); // Actualiza los niveles de newChild y sus descendientes.
    }
}

/**
 * TODO: Definición de {@code getGenericStructPrintOutDebug}.
 */
CALLING void getGenericStructPrintOutDebug(GenericStruct* generic, int position, int open, char* output) {
    if (generic == NULL || position == 0)       // void.
        output[0] = 0;
    else {
        switch (position) {
            case 1:                             // first.
                if (open)
                    sprintf(output, "{\"%s\": \"first\"", generic->identifier);
                else
                    sprintf(output, "}");
                break;
            case 2:                             // middle.
                if (open)
                    sprintf(output, "{\"%s\": \"middle\"", generic->identifier);
                else
                    sprintf(output, "}");
                break;
            case 3:                             // last.
                if (open)
                    sprintf(output, "{\"%s\": \"last\"", generic->identifier);
                else
                    sprintf(output, "}");
                break;
            case 4:                             // onlyOne.
                if (open)
                    sprintf(output, "{\"%s\": \"onlyOne\"", generic->identifier);
                else
                    sprintf(output, "}");
                break;
        }
    }
}

/**
 * TODO: Definición de {@code getGenericStructPrintOutDefault}.
 */
CALLING void getGenericStructPrintOutDefault(GenericStruct* generic, int position, int open, char* output) {
    if (generic == NULL || position == 0)   // void.
        output[0] = 0;
    else {
        switch (position) {
            case 1:                         // first.
                if (open)
                    sprintf(output, "{\"first\":");
                else
                    sprintf(output, "\"first\"}");
                break;
            case 2:                         // middle.
                if (open)
                    sprintf(output, ",{\"middle\":");
                else
                    sprintf(output, "\"middle\"}");
                break;
            case 3:                         // last.
                if (open)
                    sprintf(output, ",{\"last\":");
                else
                    sprintf(output, "\"last\"}");
                break;
            case 4:                         // onlyOne.
                if (open)
                    sprintf(output, "{\"onlyOne\":");
                else
                    sprintf(output, "\"onlyOne\"}");
                break;
        }
    }
}

/**
 * TODO: Definición de {@code getGenericStructPrintOutAsObjectNoLf}.
 */
CALLING void getGenericStructPrintOutAsObjectNoLf(GenericStruct* generic, int position, int open, char* output) {
    if (generic == NULL || position == 0)   // void.
        output[0] = 0;
    else {
        switch (position) {
            case 1:                         // first.
                if (open)
                    sprintf(output, "{\"%s\": ", generic->identifier);
                else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null}");
                break;
            case 2:                         // middle.
                if (open)
                    sprintf(output, ", {\"%s\": ", generic->identifier);
                else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null}");
                break;
            case 3:                         // last.
                if (open)
                    sprintf(output, ", {\"%s\": ", generic->identifier);
                else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null}");
                break;
            case 4:                         // onlyOne.
                if (open)
                    sprintf(output, "{\"%s\": ", generic->identifier);
                else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null}");
                break;
        }
    }
}

/**
 * TODO: Definición de {@code getGenericStructPrintOutAsObjectWithLf}.
 */
CALLING void getGenericStructPrintOutAsObjectWithLf(GenericStruct* generic, int position, int open, char* output) {
    if (generic == NULL || position == 0)   // void.
        output[0] = 0;
    else {
        char tab[10] = "\t";
        switch (position) {
            case 1:                         // first.
                if (open) {
                    sprintf(output, "\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s{\n", output);
                    for (int i = 0; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s\"%s\": ", output, generic->identifier);
                } else if (generic->numberChilds) {
                    sprintf(output, "\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                } else {
                    sprintf(output, "null\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                }
                break;
            case 2:                         // middle.
                if (open) {
                    sprintf(output, ",\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s{\n", output);
                    for (int i = 0; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s\"%s\": ", output, generic->identifier);
                } else if (generic->numberChilds) {
                    sprintf(output, "\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                } else {
                    sprintf(output, "null\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                }
                break;
            case 3:                         // last.
                if (open) {
                    sprintf(output, ",\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s{\n", output);
                    for (int i = 0; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s\"%s\": ", output, generic->identifier);
                } else if (generic->numberChilds) {
                    sprintf(output, "\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                } else {
                    sprintf(output, "null\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                }
                break;
            case 4:                         // onlyOne.
                if (open) {
                    sprintf(output, "\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s{\n", output);
                    for (int i = 0; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s\"%s\": ", output, generic->identifier);
                } else if (generic->numberChilds) {
                    sprintf(output, "\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                } else {
                    sprintf(output, "null\n");
                    for (int i = 1; i < generic->level; i++)
                        sprintf(output, "%s%s", output, tab);
                    sprintf(output, "%s}", output);
                }
                break;
        }
    }
}

/**
 * TODO: Definición de {@code getGenericStructPrintOutNoLf}.
 */
CALLING void getGenericStructPrintOutNoLf(GenericStruct* generic, int position, int open, char* output) {
    if (generic == NULL || position == 0)   // void.
        output[0] = 0;
    else {
        switch (position) {
            case 1:                         // first.
                if (open) {
                    sprintf(output, "\"%s\": ", generic->identifier);
                    if (generic->numberChilds)
                        sprintf(output, "%s { ", output);
                } else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null");
                break;
            case 2:                         // middle.
                if (open) {
                    sprintf(output, ", \"%s\": ", generic->identifier);
                    if (generic->numberChilds)
                        sprintf(output, "%s { ", output);
                } else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null");
                break;
            case 3:                         // last.
                if (open) {
                    sprintf(output, ", \"%s\": ", generic->identifier);
                    if (generic->numberChilds)
                        sprintf(output, "%s { ", output);
                } else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null");
                break;
            case 4:                         // onlyOne.
                if (open) {
                    if (generic->father != NULL)
                        sprintf(output, "\"%s\": ", generic->identifier);
                    if (generic->numberChilds)
                        sprintf(output, "%s { ", output);
                } else if (generic->numberChilds)
                    sprintf(output, " }");
                else
                    sprintf(output, "null");
                break;
        }
    }
}

/**
 * TODO: Definición de {@code getGenericStructPrintOut}.
 */
CALLING void getGenericStructPrintOut(GenericStruct* generic, int position, int open, int debug, char* output) {
    if (!debug) {
        // getGenericStructPrintOutDefault(generic, position, open, output);
        // getGenericStructPrintOutAsObjectNoLf(generic, position, open, output);
        getGenericStructPrintOutAsObjectWithLf(generic, position, open, output);
        // getGenericStructPrintOutNoLf(generic, position, open, output);
    } else
        getGenericStructPrintOutDebug(generic, position, open, output);
}

/**
 * FIXME: Definición de {@code findGenericStructMaxLevel}.
 * Obtiene la mayor profundidad de un GenericStruct.
 */
LANGUAGE DLLIMPORT CALLING int findGenericStructMaxLevel(GenericStruct* firstGenericStruct, int level) {
    GenericStruct* aux;                                                     // Crea apuntador a un GenericStruct para recorrer los hermanos del GenericStruct.
    aux = firstGenericStruct;                                               // A aux le lleva una copia del GenericStruct parámetro.

    if (aux != NULL)                                                        // Si el GenericStruct parámetro no está vacío.
        while (aux != NULL) {                                               // Recorre los hermanos de aux.
            if (aux->level > level)                                         // Si el nivel de aux es mayor que level.
                level = aux->level;                                         // A level le lleva el nivel de aux.

            if (aux->numberChilds)                                          // Si aux tiene hijos.
                level = findGenericStructMaxLevel(aux->firstChild, level);  // Busca el nivel de cada uno de los hijos de aux.

            aux = aux->nextBrother;                                         // Pasa al siguiente hermano de aux.
        }

    return level;                                                           // Devuelve el mayor nivel encontrado.
}

/**
 * FIXME: Definición de {@code printAllGenericStruct}.
 * Muestra una estructura genérica, childs dice si imprime todos sus hijos y brother dice si imprime todos sus hermanos, tab1 indica la cantidad de tabulaciones antes de imprimir cada estructura.
 */
CALLING void printAllGenericStruct(FILE* file, GenericStruct* firstGeneric, int childs, int brothers, int tab1, int tab2, int debug) {
    char printer[8000] = "";                                                                    // Crea variable para almacenar lo que se va a imprimir ya sea en un archivo o en pantalla.
    char output[8000] = "";                                                                     // Crea variable para almacenar el valor a imprimir de la estructura genérica.
    int position = 0;                                                                           // Crea variable para almacenar el valor de la posición de cada estructura genérica en la lista.

#define print(...) sprintf(&printer[strlen(printer)], __VA_ARGS__)                              // crea macro almacenar la salida de sprintf en printer.
#define prtArray(input) sprintArray(&printer[strlen(printer)], input)                           // crea macro almacenar la salida de sprintArray en printer.

    GenericStruct* aux;                                                                         // Crea apuntador a un GenericStruct para recorrer los hermanos del GenericStruct.
    aux = firstGeneric;                                                                         // A aux le lleva una copia del GenericStruct parámetro.

    if (aux == NULL || (aux->father == NULL && aux->level != 1)) {                              // Si el GenericStruct parámetro está vacío o es un GenericStruct inválido (borrado).
        if (debug)                                                                              // Si está en modo debug.
            sprintf(printer, "No Items.\n");                                                    // Almacena mensaje a imprimir.
        else                                                                                    // Si no está en modo debug.
            printer[0] = 0;                                                                     // Almacena mensaje a imprimir ("").

        if (file == NULL)                                                                       // Si el apuntador al archivo no es válido.
            printf("%s", printer);                                                              // Imprime que no hay GenericStruct.
        else                                                                                    // Si el apuntador a archivo indicado es válido.
            fprintf(file, "%s", printer);                                                       // Imprimer en el archivo que no hay GenericStruct.
    } else {                                                                                    // Si el GenericStruct parámetro no está vacío.
        while (aux != NULL) {                                                                   // Recorre los hermanos de aux.
            printer[0] = 0;                                                                     // Pone vacío el array con los valores a imprimir.
            output[0] = 0;                                                                      // Pone vacío el array con los valores a imprimir d ela estructura genérica.
            position = 0;                                                                       // Reinicia position.

            if (debug) {                                                                        // Si está en modo debug.
                print("%2d  ", aux->level);                                                     // Imprime el nivel de aux.

                for (int i = 0; i < (tab1)*9; i++)                                              // Recorre 9 veces parámetro tab1.
                    print(" ");                                                                 // Imprime un espacio.

                print("%p %p ", aux->father, aux);                                              // Imprime direcciones de memoria del GenericStruct anterior y del actual.
                print("%p %p  ", aux->prevBrother, aux->nextBrother);                           // Imprime direcciones de memoria del GenericStruct siguiente y el padre.

                for (int i = 0; i < (tab2)*9; i++)                                              // Recorre 9 veces parámetro tab2.
                    print(" ");                                                                 // Imprime un espacio.

                print("%2d  ", aux->level);                                                     // Imprime el nivel de aux.
                print("\"%2d\"  ", aux->numberChilds);                                          // Imprime cantidad de hijos del GenericStruct actual.
            }

            if (aux->getPrintValue == NULL && aux->identifier == NULL)                          // No hay función y no hay identificador.
                output[0] = 0;
            else if (aux->getPrintValue == NULL && aux->identifier != NULL)                     // No hay función, pero hay identificador.
                sprintf(output, "%s", aux->identifier);
            else {
                if ((aux->prevBrother == NULL && aux->nextBrother == NULL) || !brothers)        // Only one.
                    position = 4;
                else if (aux->prevBrother != NULL && aux->nextBrother == NULL)                  // Last.
                    position = 3;
                else if (aux->prevBrother == NULL && aux->nextBrother != NULL)                  // First.
                    position = 1;
                else // Middle.
                    position = 2;

                aux->getPrintValue(aux, position, 1, debug, output);
            }

            if (debug) {                                                                        // Si está en modo debug.
                prtArray(output);
                if (position) {
                    aux->getPrintValue(aux, position, 0, debug, output);
                    prtArray(output);
                }
                print("  ");                                                                    // Imprime espacios.
                print("\n");                                                                    // Imprime salto de línea.
            } else                                                                              // Sino está en modo debug.
                sprintf(&printer[strlen(printer)], "%s", output);

            if (file == NULL)                                                                   // Si no se indicó un archivo de salida.
                printf("%s", printer);                                                          // Muestra el contenido del array con la información del generic actual en pantalla.
            else                                                                                // Si se indicó un archivo de salida.
                fprintf(file, "%s", printer);                                                   // Escribe el contenido del array con la información del generic actual en el archivo.

            if (aux->numberChilds && childs)                                                    // Si aux tiene hijos y se indicó imprimir hijos.
                printAllGenericStruct(file, aux->firstChild, 1, 1, tab1 + 1, tab2 - 1, debug);  // Imprime cada uno de los hijos de aux.

            if (!debug) {
                aux->getPrintValue(aux, position, 0, debug, output);
                printer[0] = 0;
                sprintf(&printer[strlen(printer)], "%s", output);
                if (file == NULL)                                                               // Si no se indicó un archivo de salida.
                    printf("%s", printer);                                                      // Muestra el contenido del array con la información del generic actual en pantalla.
                else                                                                            // Si se indicó un archivo de salida.
                    fprintf(file, "%s", printer);                                               // Escribe el contenido del array con la información del generic actual en el archivo.
            }

            if (brothers)                                                                       // Si se indicó imprimir hermanos.
                aux = aux->nextBrother;                                                         // Pasa al siguiente hermano de aux.
            else                                                                                // Si se indicó no imprimir hermanos.
                break;                                                                          // Sale del ciclo.
        }
    }

#undef print                                                                                    // Borra la macro para almacenar la salida de sprintf en printer.
#undef prtArray                                                                                 // Borra la macro para almacenar la salida de sprintArray en printer.
}

/**
 * FIXME: Definición de {@code printGenericStruct}.
 * Invoca al método que imprime los GenericStruct.
 */
LANGUAGE DLLIMPORT CALLING void printGenericStruct(char* fileSource, char* openType, GenericStruct* root, int childs, int debug) {
    FILE* file = fopen(fileSource, openType);           // Crea un archivo en la ruta indicada por fileSource.

    if (!childs || root == NULL)                                                                                              // Si indicó no imprimir los hijos del GenericStruct o el GenericStruct está vacío.
        printAllGenericStruct(file, root, childs, 0, 0, 0, debug);                                                            // Imprime los GenericStruct.
    else                                                                                                                      // Si indicó imprimir los hijos del GenericStruct.
        printAllGenericStruct(file, root, childs, 0, 0, findGenericStructMaxLevel(root->firstChild, 0) - root->level, debug); // Imprime los GenericStruct.

    if (file == NULL)                                   // Si el apuntador al archivo no es válido.
        printf("\n");                                   // Imprime salto de línea en pantalla.
    else                                                // Si el apuntador a archivo indicado es válido.
        fprintf(file, "\n");                            // Imprime salto de línea en el archivo.

    fclose(file);                                       // Cierra el archivo indicado por fileSource.
}
