#ifndef _UTILS_HH_
#define _UTILS_HH_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0

// --- Structs ----------------------------------------------------------------

struct city {
    char* name;
    float latitude;
    float longitude;
};

struct node {
    struct city* stop;
    struct node* next;
};

struct path {
    struct node* first;
    struct node* last;
    float length;
    int count;
};

// --- Path --------------------------------------------------------------

struct path* pathNew();

void pathAddFirst(struct path* p, char* name, float latitude, float longitude);

void pathAddLast(struct path* p, char* name, float latitude, float longitude);

struct path* pathDuplicate(struct path* p);

void pathSwapStops(struct path* p, char* name1, char* name2);

void pathRemoveCity(struct path* p, char* name);

void pathDelete(struct path* p);

void pathPrint(struct path* p);

// --- Auxiliar functions ------------------------------------------------

float calculateLength(struct node* n);

float distance(struct city* c1, struct city* c2);

struct node* findNodeCity(struct node* n, char* name);

void freeNodeCity(struct node* node,struct path* p);

// --- Strings -----------------------------------------------------------

int strLen(char* src);

char* strDup(char* src);

int strCmp(char* a, char* b);

// --- Heuristic ---------------------------------------------------------

struct path* applyHeuristic(struct path* p);

#endif

