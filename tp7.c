//https://github.com/leyvajoaquinn/tp7.c/tree/main
#include <stdio.h>

#define TAM 5

int main() {
    int codigos[TAM];
    float precios[TAM];
    int i;

    for (i = 0; i < TAM; i++) {
        printf("Ingrese el código de barras (1-999999999): ");
        scanf("%d", &codigos[i]);

        while (codigos[i] <= 0 || codigos[i] > 999999999) {
            printf("Error. El código de barras debe estar entre 1 y 999999999\n");
            printf("Ingrese el código de barras (1-999999999): ");
            scanf("%d", &codigos[i]);
        }

        printf("Ingrese el precio: ");
        scanf("%f", &precios[i]);

        while (precios[i] < 0) {
            printf("Error. El precio no puede ser negativo\n");
            printf("Ingrese el precio: ");
            scanf("%f", &precios[i]);
        }
    }

    printf("\nCódigo\t\tPrecio\n");
    for (i = 0; i < TAM; i++) {
        printf("%d\t\t%.2f\n", codigos[i], precios[i]);
    }

    int indiceMayor = 0, indiceMenor = 0;
    for (i = 1; i < TAM; i++) {
        if (precios[i] > precios[indiceMayor]) {
            indiceMayor = i;
        }
        if (precios[i] < precios[indiceMenor]) {
            indiceMenor = i;
        }
    }

    printf("\nMás caro: [%d] %.2f\n", codigos[indiceMayor], precios[indiceMayor]);
    printf("Más barato: [%d] %.2f\n", codigos[indiceMenor], precios[indiceMenor]);

    return 0;
}
