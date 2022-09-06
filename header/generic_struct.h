#ifndef GENERIC_STRUCT_H_

#define GENERIC_STRUCT_H_

/* Includes for the header file */

#ifdef __cplusplus
#define LANGUAGE extern "C"
#elif defined __GNUC__
#define LANGUAGE extern
#endif

#ifdef GENERIC_STRUCT_STATIC_
#define DLLIMPORT
#elif defined BUILDING
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

#define CALLING __cdecl
//#define CALLING __stdcall

/* Macros and definitions for the source file. */
#ifdef GENERIC_STRUCT_DEFINITIONS_
#define elif else if
#define null NULL
#define String char*
#endif

DLLIMPORT typedef struct GenericStruct GenericStruct;
LANGUAGE DLLIMPORT CALLING char* setValue(char* value);
LANGUAGE DLLIMPORT CALLING GenericStruct* newGenericStruct(char* identifier, GenericStruct* ref, int brother, void* concrete, void (*getPrintValue)(GenericStruct*, int, int, int, char*));
LANGUAGE DLLIMPORT CALLING void addGenericStructChild(GenericStruct* father, GenericStruct* newChild);
LANGUAGE DLLIMPORT CALLING int findGenericStructMaxLevel(GenericStruct* firstGenericStruct, int level);
LANGUAGE DLLIMPORT CALLING void printGenericStruct(char* fileSource, char* openType, GenericStruct* root, int childs, int debug);

struct GenericStruct {
    /* Es el nivel de la estructura. */
    int level;
    /* Es el identicador de la estructura para las busquedas. */
    char* identifier;
    /* Es la cantidad de hijos del  la estructura. */
    int numberChilds;
    /* Es el padre de la estructura. */
    GenericStruct* father;
    /* Es el anterior hermano de la estructura. */
    GenericStruct* prevBrother;
    /* Es el próximo hermano del la estructura. */
    GenericStruct* nextBrother;
    /* Es el primer hijo del la estructura. */
    GenericStruct* firstChild;
    /* Es el puntero al tipo concreto. */
    void* concrete;
    /* Es el puntero a la función imprimir para el objeto concreto. */
    void (*getPrintValue)(GenericStruct*, int, int, int, char*);
};

#if !defined BUILDING
#undef LANGUAGE
#undef DLLIMPORT
#undef CALLING
#endif

#endif
