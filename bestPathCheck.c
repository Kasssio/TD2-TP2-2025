#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

struct path* load_cities_from_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }

    struct path* p = pathNew();

    int count = 0;
    char line[1024]; // Buffer line
    char name[1024]; // Buffer city name

    while (fgets(line, sizeof(line), file)) {
        // Remove new line character
        line[strcspn(line, "\n")] = '\0';

        // Parser line
        char *token;
        token = strtok(line, ","); // Name
        strncpy(name, token, 1024);

        token = strtok(NULL, ","); // Latitude
        if (token == NULL) continue;
        float latitude = (float)atof(token);

        token = strtok(NULL, ","); // Longitude
        if (token == NULL) continue;
        float longitude = (float)atof(token);

        pathAddLast(p, name, latitude, longitude);

        count++;
    }
    fclose(file);
    if (count == 0) {
        pathDelete(p);
        return NULL; // No se cargaron ciudades
    }
    printf("Cargadas %d ciudades desde %s\n", count, filename);
    return p;
}

void write_cities_to_csv(struct path* ruta, const char* nombre_archivo) {
    FILE* archivo = fopen(nombre_archivo, "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo para escritura");
        return;
    }

    struct node* nodo_actual = ruta->first;
    while (nodo_actual != NULL) {
        if (nodo_actual->stop != NULL) {
            // Escribir en formato CSV: nombre,latitud,longitud
            fprintf(archivo, "%s,%.3f,%.3f\n",
                    nodo_actual->stop->name,
                    nodo_actual->stop->latitude,
                    nodo_actual->stop->longitude);
        }
        nodo_actual = nodo_actual->next;
    }
    fclose(archivo);
}

void print(struct path* p) {
    printf("    [%s] -> [%s]\n", p->first->stop->name, p->last->stop->name);
    printf("    Longitud total: %.2f km\n", p->length);
    printf("    Cantidad de ciudades: %d\n", p->count);
}

int main(int argc, char *argv[]) {

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Uso: %s <nombre_archivo> [H]\n", argv[0]);
        fprintf(stderr, "  <nombre_archivo>: Nombre del archivo de ciudades.\n");
        fprintf(stderr, "  [H]: Opcional. Si se incluye se ejecuta la heurística.\n");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];

    struct path* p = load_cities_from_csv(filename);
    if (p == NULL) {
        fprintf(stderr, "No se pudieron cargar las ciudades o el archivo esta vacio.\n");
        return 1;
    }


    if(strcmp(argv[2], "H") == 0) {
        printf("Camino Original\n");
        print(p);
        struct path* np = applyHeuristic(p);
        printf("\nNuevo Camino\n");
        print(np);
        write_cities_to_csv(np, "newCitiesOrder.csv");
        pathDelete(np);
    } else {
        print(p);
    }

    pathDelete(p);
    return 0;
}
