//https://github.com/leyvajoaquinn/TPN-3/blob/main/tp3%20original
#include <stdio.h>

int main()
 int calificacion;

    
    printf("Ingrese la calificación del examen: ");
    scanf("%d", &calificacion);

    if (calificacion >= 90) {
        printf("Calificación: A\n");
    }
    else if (calificacion >= 80) {  
        printf("Calificación: B\n");
    } 
    else if (calificacion >= 70) {  
        printf("Calificación: C\n");
    } 
    else if (calificacion >= 60) { 
        printf("Calificación: D\n");
    } 
    else {
        printf("Calificación: F\n");
    
}
