/*
 * @fileoverview {FileName} se encarga de realizar tareas especificas.
 *
 * @version             1.0
 *
 * @author              Dyson Arley Parra Tilano <dysontilano@gmail.com>
 * Copyright (C) Dyson Parra
 *
 * @History v1.0 --- La implementacion de {FileName} fue realizada el 31/07/2022.
 * @Dev - La primera version de {FileName} fue escrita por Dyson A. Parra T.
 */
#include "generic_struct.h"
#include "tester.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Entrada principal del sistema.
 *
 * @param argc cantidad de argumentos pasados en la linea de comandos.
 * @param argv argumentos de la linea de comandos.
 * @return {0} si el programa se ejecutó correctamente.
 */
int main(int argc, char** argv) {
    char output[50] = "";

    GenericStruct* one = newGenericStruct("Root", NULL, 1, NULL, NULL);
    GenericStruct* two = newGenericStruct("value2", one, 0, NULL, NULL);
    GenericStruct* tre = newGenericStruct("value3", one, 0, NULL, NULL);
    GenericStruct* fur = newGenericStruct("value4", one, 0, NULL, NULL);
    GenericStruct* fiv = newGenericStruct("value5", one, 0, NULL, NULL);
    GenericStruct* six = newGenericStruct("value6", tre, 0, NULL, NULL);
    printGenericStruct(output, "w+", one, 1, 0);
    printGenericStruct(output, "w+", one, 1, 1);
    // printGenericStruct(output, "w+", NULL, 1, 1);

    // printGenericStruct(output, "w+", list1->generic, 1, 0);
    // printGenericStruct(output, "w+", list1->generic, 1, 1);

    // addChild(list1->generic, item1->generic);
    // printGenericStruct(output, "w+", list1->generic, 1, 0);
    // printGenericStruct(output, "w+", list1->generic, 1, 1);
    /*-
    //printGenericStruct(output, "w+", item1, 1, 1);
    m3u8MetadataItem* item4 = newM3u8MetadataItem("name4", "value4", item2, 1);
    printGenericStruct(output, "w+", item1->generic, 1, 0);
    printGenericStruct(output, "w+", item1->generic, 1, 1);
    */

    return 0;
}
