#include <stdio.h>
//https://github.com/leyvajoaquinn/TPN-5/tree/main
//https://github.com/leyvajoaquinn/TPN-3/blob/main/tp3
int main()
{   
    float promedio=0;
    int estudiantes, max=0 ,min=100;
	do{
	    printf("ingrese el numero de estudiantes: ");
	    scanf("%d", &estudiantes);
	}while(estudiantes<0);
	
    float calificaciones[estudiantes];

    for(int i=0; i<estudiantes;++i){
      do{  
        printf("ingrese la nota del estudiante %d: ", i+1);
	    scanf("%f", &calificaciones[i]);
	        if(calificaciones[i]<0 || calificaciones[i]>100){
	            printf("la nota debe ser entre 0 y 100\n");
	    }
          
      }while(calificaciones[i]<0 || calificaciones[i]>100);
	    
	    if (calificaciones[i]>max){
	        max=calificaciones[i];
	    }
	    if(calificaciones[i]<min){
	        min=calificaciones[i];
	        }
	    promedio=promedio + calificaciones[i];
	}
	    promedio= promedio/estudiantes;
        printf("la calificaion minima es: %d\n",min);
	    printf("la calificaion maxima es: %d\n",max);
        printf("el promedio de las calificaciones es: %2.f", promedio);


	return 0;
}
