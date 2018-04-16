
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*********************************************************************/

void mesh_info(int* numels,int* numverts){

  // Leemos la malla y determinamos el número de elementos (numels)
  //y nodos (numverts) de la malla para iniciar el cálculo.

  FILE* malla;

  int aux[2],elem[5];
  
  char mensajes[100];
  
  float  coordinateX,coordinateY,coordinateZ;
  int vertex;
   
  // Abro el fichero de la malla */
  malla = fopen("malla.msh","r");

  if(malla==NULL){
    printf("No se encuentra el fichero malla.msh o está dañado \n");
    exit(0);
  }  
  
  while (feof(malla) == 0){

    fgets(mensajes,100,malla);

    aux[0] = sscanf(mensajes,"%d %f %f %f",
		    &vertex,
		    &coordinateX,
		    &coordinateY,
		    &coordinateZ);

    aux[1] = sscanf(mensajes,"%d %d %d %d %d",
		    &elem[0],
		    &elem[1],
		    &elem[2],
		    &elem[3],
		    &elem[4]);
    
    // Lectura de valores de la malla
     
    if ((aux[0] == 4)&&(aux[1] == 2)){
      //      printf("Vertice : %d \t Coord x : %f \t Coord y : %f \t Coord z : %f \n",
      //     vertex,
      //     coordinateX,
      //     coordinateY,
      //     coordinateZ);
      if (vertex >= *numverts) *numverts = vertex;
    }

    if ((aux[0] == 4)&&(aux[1] == 5)){
      //      printf("Elemento : %d \t Vertices : %d ,%d ,%d, %d  \n",
      //     elem[0],
      //     elem[1],
      //     elem[2],
      //     elem[3],
      //     elem[4]);

      if (elem[0] >= *numels) *numels = elem[0];
      
    }


  } // End while loop //

  
  // Cierro el fichero de la malla
  fclose(malla);

   
} // End mesh_info




/*********************************************************************/



void ** mat_din(int fil,int col,int trama){

  // Alocatado dinámico de matrices

  int i;
  void **m;

  // Ubicación del puntero a la tabla de punteros a filas 

  m = (void **)malloc((unsigned)fil * sizeof(void *));
  if (m == NULL) {puts("Error en malloc");exit(0);}

  // Ubicación de los punteros de filas 

  for(i = 0; i<fil;i++){

    m[i] = malloc((unsigned)col * trama); // malloc() devuelve un puntero a void
    if(m[i]==NULL){puts("Error en malloc"); exit(0);}

  }

  return m;

}


/*********************************************************************/



void ** mat_din_0(int fil,int col,int trama){

  // Alocatado dinámico de matrices

  int i;
  void **m;

  // Ubicación del puntero a la tabla de punteros a filas

  m = (void **)calloc(fil,sizeof(void*));
  if (m == NULL) {puts("Error en calloc");exit(0);}

  // Ubicación de los punteros de filas 
  
  for(i = 0; i < fil; i++){
    m[i] = (void *)calloc(col,(unsigned)col * trama);
    if(m[i]==NULL){puts("Error en malloc"); exit(0);}

    //m[i] = malloc((unsigned)col * trama); // malloc() devuelve un puntero a void
  }

  return m;

}


/********************************************************************/


void mat_ini_I(int ** mat,int filas,int columnas,int value){

  // Inicializa matrices de enteros (mat) de dimensiones filas*columnas
  // con un valor determinado (value)

  for(int i = 0;i==filas-1;i++){
    for(int j = 0;j==columnas-1;j++){

      mat[i][j] = value;
      
    }
  }

} // End mat_ini_I 


/*********************************************************************/

void * vect_din(int dim, int trama){

  // Alocatado dinámico de vectores

  void *v;

  v = malloc(dim * trama); // malloc() devuelve un puntero a void
  if (v == NULL){puts("Error en malloc"); exit(0);}
  return v;

} // End vect_din


/*********************************************************************/

void * vect_din_0(int dim, int trama){

  // Alocatado dinámico de vectores

  void *v;

  v = calloc(dim,dim * trama);
  if (v == NULL){puts("Error en calloc"); exit(0);}
  return v;

} // End vect_din


/********************************************************************/


void vect_ini_I(int * vect,int size_v,int value){

  // Inicializa vectores de enteros (vect) de dimensiones size_v
  // con un valor determinado (value)
  
  for(int i = 0;i<=size_v-1;i++){
    vect[i] = value;
  }

} // End vect_ini_I


/********************************************************************/


void vect_ini_F(float * vect,int size_v,float value){

  // Inicializa vectores de float (vect) de dimensiones size_v
  // con un valor determinado (value)
  
  for(int i = 0;i<=size_v-1;i++){
    vect[i] = value;
  }

} // End vect_ini_F




/********************************************************************/


void mat_ini_F(float ** mat,int filas,int columnas,float value){

  // Inicializa matrices de enteros (mat) de dimensiones filas*columnas
  // con un valor determinado (value)

  for(int i = 0;i==filas-1;i++){
    for(int j = 0;j==columnas-1;j++){

      mat[i][j] = value;
      
    }
  }

} // End mat_ini_F


/*********************************************************************/
