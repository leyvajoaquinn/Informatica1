#include <stdio.h>
#include <stdlib.h>

#define N_MAX 10
#define M_MAX 10

struct matrix {
  int filas;
  int columnas;
  float mat[N_MAX][M_MAX];
};

typedef struct matrix matrix_t;

void cargar_matriz(matrix_t *, char *);
void sumar_matrices(matrix_t, matrix_t, matrix_t *);
matrix_t sumar_matrices_r(matrix_t, matrix_t);
void imprimir_matriz(matrix_t);
void guardar_matriz(matrix_t, char *);

int main(void){
  matrix_t A = {0}, B = {0};
  matrix_t C = {0};

  cargar_matriz(&A, "mat_A.txt");
  cargar_matriz(&B, "mat_B.txt");

  imprimir_matriz(A);
  imprimir_matriz(B);

  sumar_matrices(A, B, &C);
  
  imprimir_matriz(C);
  guardar_matriz(C, "mat_C.txt");

  return 0;
}

void cargar_matriz(matrix_t *p, char *file) {
 FILE *fp = fopen( file , "r" );
 if(fp!=NULL){
  fscanf(fp,"%d %d", &p->filas, &p->columnas);

  for(int i =0;i<p->filas; i++){
    for(int j =0; j<p->columnas; j++) {
        fscanf(fp, "%f", &p->mat[i][j]);
    }
  }
  fclose(fp);
 }
 if(fp==NULL){
  printf("no se pudo abrir");
  exit (1);
 }
}

void imprimir_matriz(matrix_t m) {
  for (int i = 0; i < m.filas; i++) {
    for (int j = 0; j < m.columnas; j++)
      printf("%9.2f", m.mat[i][j]);
    printf("\n");
  }
  printf("\n");
}

void sumar_matrices(matrix_t A, matrix_t B, matrix_t *pC) {
   pC->filas = A.filas;
    pC->columnas = A.columnas;

  for(int i =0;i<A.filas; i++){
    for(int j =0; j<A.columnas; j++){
        pC ->mat[i][j] = A.mat[i][j]+ B.mat[i][j];
    }
  }
}

void guardar_matriz(matrix_t m, char *file) {
  FILE *p=fopen ( file , "w");
  if (p==NULL){
    printf("el archivo no se puedo crear");
    exit(1);
  }
  fprintf(p ,"%d %d\n", m.filas , m.columnas);
  
    for (int i = 0; i < m.filas; i++) {
    for (int j = 0; j < m.columnas; j++){
      fprintf(p, "%9.2f",m.mat[i][j]);
    }
    fprintf(p, "\n");
  }
 fprintf(p, "\n");

}
