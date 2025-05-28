#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    // Caso string vacío
    int len = strLen("");
    printf("strLen(\"\") -> \"%i\"\n", len);

    // Caso string con un caracter
    len = strLen("A");
    printf("strLen(\"A\") -> \"%i\"\n", len);
    len = strLen("z");
    printf("strLen(\"z\") -> \"%i\"\n", len);

    // Caso palabras completas
    len = strLen("hola");
    printf("strLen(\"hola\") -> \"%i\"\n", len);
    len = strLen("abcdefghijklmnopqrstuvwxyz0123456789 -"); // 38
    printf("strLen(\"abcdefghijklmnopqrstuvwxyz0123456789 -\") -> \"%i\"\n", len);
    printf("\n");

    // strDup
    // Caso string vacío
    char* dup = strDup("");
    printf("strDup(\"\") -> \"%s\"\n", dup);
    free(dup);

    // Caso string con un caracter
    dup = strDup("A");
    printf("strDup(\"A\") -> \"%s\"\n", dup);
    free(dup);

    dup = strDup("z");
    printf("strDup(\"z\") -> \"%s\"\n", dup);
    free(dup);

    // strCmp

    printf("strCmp entre vacíos: %i\n", strCmp("",""));
    printf("strCmp entre dos strings de un elemento: %i\n", strCmp("1","2"));
    printf("strCmp entre dos iguales hasta un caracter: Topa y Topo -> %i\n", strCmp("Topa","Topo"));
    printf("strCmp entre dos iguales hasta un caracter: Topo y Topa -> %i\n", strCmp("Topo","Topa"));
    printf("strCmp entre dos iguales hasta un caracter: Gato y Gata -> %i\n", strCmp("Gato","Gata"));
    printf("strCmp entre dos iguales hasta un caracter: Gata y Gato -> %i\n", strCmp("Gata","Gato"));
    printf("strCmp entre dos iguales: Perro y Perro -> %i\n", strCmp("Perro","Perro"));

    // pathNew
    struct path* p1 = pathNew();
    struct path* p2 = pathNew();
    struct path* p3 = pathNew();
    struct path* p4 = pathNew();
    struct path* p5 = pathNew();
    pathAddLast(p4,"Hiroshima",34.385,132.455);
    pathAddLast(p4,"Huelva",37.261,-6.944);
    pathAddLast(p4,"Hradec Králové",50.209,15.832);
    pathAddLast(p4,"Hobart",-42.882,147.325);
    pathAddLast(p4,"Horta",38.520,-28.600);
    pathAddLast(p4,"Houston",29.760,-95.369);
    pathAddLast(p4,"Hyderabad",17.385,78.486);
    pathAddFirst(p5,"Zalaegerszeg",46.844,16.840);

    // pathAddFirst
    printf("-----------Añado ciudades a p1 con pathAddFirst-----------\n");
    pathAddFirst(p1, "Paris", 48.857, 2.352);
    pathPrint(p1);
    pathAddFirst(p1, "Buenos Aires", -34.600, -58.382);
    pathPrint(p1);
    pathAddFirst(p1, "Zaragoza", 41.648, -889.000);
    pathPrint(p1);

    // pathAddLast
    printf("-----------Añado ciudades a p2 con pathAddLast------------\n");
    pathAddLast(p2, "Madrid", 40.417, -3.703);
    pathPrint(p2);
    pathAddLast(p2, "Tokio", 35.689, 139.692);
    pathPrint(p2);
    pathAddLast(p2, "Port au Prince",18.539,-72.337);
    pathPrint(p2);

    // pathDuplicate
    printf("---Duplicamos p3 (primero vacio, luego con un elemento) y p1---\n");
    struct path* np = pathDuplicate(p3);
    pathAddFirst(p3, "Provence",43.834,6.083);
    struct path* np2 = pathDuplicate(p3);
    struct path* np3 = pathDuplicate(p1);
    pathPrint(np2);
    pathPrint(np3);
    pathDelete(np);
    pathDelete(np2);
    pathDelete(np3);

    // pathSwapStops
    pathAddFirst(p3, "Gwangyang",34.951,127.700);
    pathSwapStops(p1, "Buenos Aires", "Buenos Aires");
    printf("--------------------Swap stops con una ciudad----------------------\n");
    pathPrint(p1);
    printf("-------------------------Cambio ciudades---------------------------\n");
    pathSwapStops(p3,"Provence", "Gwangyang");
    pathPrint(p3);
    printf("---------------------Cambio ciudades p2 y p4-----------------------\n");
    pathSwapStops(p2,"Madrid","Port au Prince");
    pathPrint(p2);
    // pathSwapStops(p4,"Houston","Huelva");
    //pathPrint(p4);
    printf("-----------------------Borro primera ciudad---------------------\n");
    pathAddLast(p1,"Lublin",51.246,22.568);
    pathRemoveCity(p1, "Zaragoza");
    pathPrint(p1);
    printf("----------------------Borro ultima ciudad-----------------------\n");
    pathAddFirst(p2,"Nottingham",52.954,-1.158);
    pathPrint(p2);
    pathRemoveCity(p2,"Madrid");
    pathPrint(p2);
    printf("-------------------Borramos ciudad intermedia-------------------\n");
    pathAddFirst(p3,"Abu Dhabi",24.453,54.377);
    pathAddFirst(p3,"Albacete",38.994,-1.855);
    printf("Antes de borrar en p3: \n");
    pathPrint(p3);
    pathRemoveCity(p3,"Provence");
    printf("Despues de borrar en p3: \n");
    pathPrint(p3);
    pathRemoveCity(p2,"Nottingham");
    pathRemoveCity(p2,"Tokio");
    printf("------------------Borramos la unica ciudad de p2----------------\n");
    pathPrint(p2);

    struct path* p = pathNew();
    pathAddLast(p, "A", 1, 1);
    pathAddLast(p, "E", 5, 5);
    pathAddLast(p, "D", 4, 4);
    pathAddLast(p, "C", 3, 3);
    pathAddLast(p, "B", 2, 2);
    pathAddLast(p, "F", 6, 6);


    printf("Este es p antes: %f\n", p->length);
    pathPrint(p);
    struct path* h = applyHeuristic(p);
    printf("Este es p ahora (creamos la copia en h): %f\n", h->length);
    pathPrint(h);



    // Borro todo
    pathDelete(p1);
    pathDelete(p2);
    pathDelete(p3);
    pathDelete(p4);
    pathDelete(p5);
    pathDelete(p);
    pathDelete(h);
    return 0;
}
