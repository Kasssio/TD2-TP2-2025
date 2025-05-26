#include "utils.h"
#include <math.h>
#include <float.h>
#define PI 3.14159265358979323846
#define EARTH_RADIUS_KM 6371.0
int strLen(char* src){
    int i=0;
    while (src[i]!=0){
        i++;
    }
    return i;
}
char* strDup(char* src){
    int size = strLen(src);
    int i = 0;
    char* copy = (char*)malloc((size + 1) * sizeof(char));
    while(src[i] != 0){
        copy[i] = src[i];
        i++;
    }
    copy[size] = 0;
    return copy;
}

int strCmp(char* a, char* b){
  int size_a = strLen(a);
  int size_b = strLen(b);
  if (size_a == 0 && size_b == 0){
    return 0;
  }
  if(size_a == 0) return 1;
  if(size_b == 0) return -1;
  int minima_long = 0;
  if (size_a < size_b){
    minima_long = size_a;
  }
  else{
    minima_long = size_b;
  }
  int i = 0;
  int res = 0;
  while (i < minima_long){
    if(a[i] < b[i]){
        res = 1;
        return res; 
    }
    if(a[i]>b[i]){
        res=-1;
      return res;
    }
    i++;
  }
  //si llegamos hasta aca,entonces todos los caracteres son iguales. Por eso, debemos ver el tamaño de cada str 
  if(size_a<size_b){
    res=1;
    return res;
  }
  if (size_a>size_b){
    res=-1;
    return res;
  }
  //si no se cumple ningún if, entonces res sigue siendo 0
  return res;
  
}

struct path* pathNew(){
    struct path* p=(struct path*)malloc(sizeof(struct path));
    p->first=NULL;
    p->last=NULL;
    p->count=0;
    p->length=0;
    return p;
}
void pathAddFirst(struct path* p, char* name, float latitude, float longitude) {
    struct city* newcity = (struct city*) malloc(sizeof(struct city));
    newcity->name = strDup(name);
    newcity->latitude = latitude;
    newcity->longitude = longitude;
    struct node*curr = (struct node*) malloc(sizeof(struct node));
    curr->stop = newcity;
    if(p->count==0){
        p->first = curr;
        p->last = curr;
        p->count++;
        p->length=0;
        return;
    }
    if(p->count == 1){
        p->first = curr;
        curr->next = p -> last;
        p->count++;
        p->length=calculateLength(curr);
        return;
    }
    struct node* tmp = p->first;
    p->first = curr;
    curr->next = tmp;
    p->count++;
    p->length=calculateLength(curr);
    return;
}
void pathAddLast(struct path* p, char* name, float latitude, float longitude) {
    struct city* newcity = (struct city*) malloc(sizeof(struct city));
    newcity->name = strDup(name);
    newcity->latitude = latitude;
    newcity->longitude = longitude;
    struct node* curr = (struct node*) malloc(sizeof(struct node));
    curr->stop = newcity;
    //caso vacio
    if(p->count==0){
        p->first = curr;
        p->last = curr;
        p->count++;
        p->length=0;
        return;
    }
    //caso de un elemento
    if(p->count == 1){
        p->last = curr;
        struct node* curr2 = p->first;
        curr2->next = curr;
        p->count++;
        p->length=calculateLength(curr2);
        return;
    }
    struct node*first=p->first;
    struct node* curr2 = p->last;
    p->last = curr;
    curr2->next = curr;
    p->count++;
    p->length=calculateLength(first);
    return;
}

struct path* pathDuplicate(struct path* p) {
    struct path* newPath = pathNew();
    //Caso donde no hay ningún nodo en la estructura path original
    if (p->first==NULL){ 
      return newPath;
    }
    struct node* curr_p = p->first;
    //Caso donde hay más de un nodo en la estructura path original
    while(curr_p!= NULL){
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        struct city* newCity = (struct city*) malloc(sizeof(struct city));
        newCity->name = strDup(curr_p->stop->name);
        newCity->latitude = curr_p->stop->latitude;
        newCity->longitude = curr_p->stop->longitude;
        newNode->stop = newCity;
        newNode->next = NULL;
        if(newPath->count == 0){ // Caso inicial
            newPath->first = newNode;
            newPath->last = newNode;
            newPath->count++;
        } 
        else { // El resto del while
            newPath->last->next = newNode;
            newPath->last = newNode;
            newPath->count++;
        }
        curr_p = curr_p->next;
    }
    newPath->length = calculateLength(newPath->first);
    return newPath;
}
void pathSwapStops(struct path* p, char* name1, char* name2) {
    struct node* n1 = findNodeCity(p->first, name1);
    struct node* n2 = findNodeCity(p->first, name2);
    if(n1 == NULL || n2 == NULL) {
        return;
    }
    struct city* tmp = n1->stop;
    n1->stop = n2->stop;
    n2->stop = tmp;
    p->length = calculateLength(p->first);
    return;
}

void pathRemoveCity(struct path* p, char* name) {
    if(p->first == NULL){
        return;
    }
    struct node* curr = p->first;
    struct node* prev = NULL;

    struct node* target = findNodeCity(p->first, name);
    //caso en donde no esta la lista de ciudades el nombre a borrar
    if(target == NULL) return;
     //Caso 1: Hay solo un nodo
    if(p->count == 1){
        if(curr == target){ //caso de borrar el primero y el ultimo a la vez
            freeNodeCity(curr,p);
            p->first = NULL;
            p->last = NULL;
            p->length = 0;
            p->count = 0;
        }
        return;
    }
    // Caso 2: Hay más de un nodo

    //Caso 2.1: se borra el primero
    if(curr == target){
        p->first = curr->next;
        freeNodeCity(curr,p);
        p->length = calculateLength(p->first);
        return;
    }
    //Caso 2.2: se borra el último
    if(p->last == target){ 
        while(curr->next != NULL){
            prev = curr;
            curr = curr->next;
        }
      //llego al ultimo nodo
        p->last = prev;
        freeNodeCity(curr, p);
        prev->next = NULL;
        p->length = calculateLength(p->first);
        return;
     }
     //Caso 2.3: No se borra ni el primero ni el ultimo
    while(curr != NULL && curr != target){
        prev = curr;
        curr = curr->next;
    }
    if(curr == NULL){
        return; // salgo del while porque puede ser que ya termine de recorrer
    }
    // si sali del while es porque encontro el nodo
    prev->next = curr->next;
    freeNodeCity(curr,p);
    p->length=calculateLength(p->first);
    return;  
  }

void pathDelete(struct path* p) {
  //caso vacio
    if(p->first == NULL){
        free(p);
        return;
    }
  struct node*curr = p->first;
    if(p->count == 1){ 
        free(curr->stop->name);
        free(curr->stop);
        free(curr);
        free(p);
        return;
    }
    struct node*siguiente = NULL;
    while(curr->next != NULL){
        free(curr->stop->name);
        free(curr->stop);
        siguiente = curr->next;
        free(curr);
        curr = siguiente;  
    }
  // liberar el último nodo
    free(curr->stop->name);
    free(curr->stop);
    free(curr);
    free(p);
    return;
}

void pathPrint(struct path* p) {
    if(p->first == 0) {
        printf("[null] -> [null], ");
    } else {
        printf("[%s] -> [%s], ", p->first->stop->name, p->last->stop->name);
    }
    printf("Count=%i, Length=%f\n", p->count, p->length);
    struct node* curr = p->first;
    while (curr) {
        printf("%s (%f,%f) \n", curr->stop->name, curr->stop->latitude, curr->stop->longitude);
        curr = curr->next;
    }
}

// --- Auxiliar functions -----------------------------------------------------

float calculateLength(struct node* n) {
    if(n==NULL) return 0.0;
  struct node*curr=n; //apunto al primer nodo de la lista;
  if(curr->next==NULL) return 0.0;
  float suma= 0.0;
    while(curr->next != NULL){
        suma= suma + distance(curr->stop, curr->next->stop);
        curr = curr->next;
    }
    return suma;
}
struct node* findNodeCity(struct node* n, char* name) {
    if(n == NULL) return NULL;
    struct node* curr = n;
    while(curr != NULL && strCmp(curr->stop->name, name) != 0){
        curr = curr->next;
    }
    return curr;
}

void freeNodeCity(struct node* node, struct path* path){
    free(node->stop->name);
    free(node->stop);
    free(node);
    path->count--;
    return;
}

float distance(struct city* c1, struct city* c2) {
    // Formula de Haversine
    // Calcula la distancia entre dos puntos en la superficie de una esfera
    // R es el radio de la Tierra

    double degrees2radians = PI / 180.0;

    double lat1 = c1->latitude * degrees2radians;
    double lon1 = c1->longitude * degrees2radians;
    double lat2 = c2->latitude * degrees2radians;
    double lon2 = c2->longitude * degrees2radians;

    double dlat = lat2-lat1;
    double dlon = lon2-lon1;

    double a = sin(dlat/2.0) * sin(dlat/2.0) + cos(lat1) * cos(lat2) * sin(dlon/2) * sin(dlon/2);

    double R = EARTH_RADIUS_KM;

    double c = 2 * atan2(sqrt(a), sqrt(1.0-a));

    double d = R * c;

    return (float)d;
}

// --- Heuristic ---------------------------------------------------------

struct path* applyHeuristic(struct path* p) {
    struct node* curr_i = p->first;
    struct node* curr_j;
    int min = distance(curr_i->stop,curr_j->stop);
    while(curr_i != NULL){
        curr_j = curr_i->next;
        while(curr_j != NULL){
            int length = distance(curr_i->stop, curr_j->stop);
            if(length < min){
                min = length;
                pathSwapStops(p, curr_i->stop->name, curr_j->stop->name);
            }
            curr_j = curr_j->next;
        }
        curr_i = curr_i->next;
    }
    return p;
    
}