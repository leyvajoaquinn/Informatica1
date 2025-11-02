#include <stdio.h>

int main() {
    float num1;
    float num2;
    float num3;

do{
    printf("ingrese su peso en kg: \n");   
    scanf("%f", &num1);
    printf("ingrese su altura en metros: \n");
    scanf("%f", &num2);
   }while(num1<0 ||num2<0);

    num3 = num1/(num2 * num2);
    printf("su BMI es %2.f \n", num3 );

    if(num3<18.5)
        printf("su peso es bajo");
    if(num3>18.5 && num3<24.9)
        printf("su peso es normal");
    if(num3>25 && num3<29.9)
        printf("usted tiene sobrepeso");
    if(num3 > 29.9)
        printf("usted padece obesidad");
    

    return 0;
}
