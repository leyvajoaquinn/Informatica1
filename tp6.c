#include <stdio.h>
#define PI 3.1415927
float calcularAreaRectangulo(float a, float b){
    
    int arearectangulo = a * b;
    return arearectangulo;
    }

float calcularPerimetroRectangulo(float a, float b) {
        float perimetro = (a+b)*2;
        return perimetro;
    }

float calcularPerimetroCirculo(float a){
    float perimetro = 2*a*PI;
    return perimetro;
    }

float calcularAreaCirculo(float a){
    float area = PI*(a*a);
    return area;
    }
void imprimir_resultados (float area, float perimetro){
    printf("el area es igual a:%f\n", area);
    printf("el perimetro es igual a: %f\n",perimetro);
   
}
int main()
{
    int figura;
    printf("ingrese figura que desea calcular (1:rectangulo 2:circulo) : \n");
    scanf("%d",&figura);
    
switch (figura){
    case 1:{
        float altura, longitud, area, perimetro, diagonal;
        
        printf("ingrese la altura del rectangulo: \n");
        scanf("%f",&altura);
        printf("ingrese la longitud del rectangulo: \n");
        scanf("%f",&longitud);
        
        area = calcularAreaRectangulo(altura, longitud);
        perimetro = calcularPerimetroRectangulo(altura, longitud);
        imprimir_resultados(area,perimetro);
        break;
        }
        
    case 2:{
        float radio, Acirculo, pcirculo;
        printf("ingrese el radio del circulo: \n");
        scanf("%f",&radio);
        
        Acirculo= calcularAreaCirculo(radio);
        pcirculo= calcularPerimetroCirculo(radio);
        imprimir_resultados(Acirculo ,pcirculo);
        break;
        }
        
    default:
    printf("ingrese otro numero");
    }
    
  return 0;
}
