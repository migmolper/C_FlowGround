
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*********************************************************************/

void mesh_data(float ** iverts,float ** ielem,int numels,int numverts){

  // Cargamos los datos de la malla en los ficheros iverts (vértices) e
  // ielem (elementos).

  FILE* malla;

  int aux[2],elem[5];

  int i = 0,j = 0;
  
  char mensajes[80];
  
  float  coordinateX,coordinateY,coordinateZ;
  int vertex;
   
  // Abro el fichero de la malla
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
     
    if ((aux[0] == 4)&&(aux[1] == 2)&&(i<numverts)){

      iverts[i][0] = coordinateX;
      iverts[i][1] = coordinateY;
      iverts[i][2] = coordinateZ;
      i++;
     
    }


    if ((aux[0] == 4)&&(aux[1] == 5)&&(j<numels)){

      ielem[j][0] = elem[1];
      ielem[j][1] = elem[2];
      ielem[j][2] = elem[3];
      ielem[j][3] = elem[4];
      j++;

    }

  } // End while loop //

  
  // Cierro el fichero de la malla 
  fclose(malla);
  
  
} // End mesh_data
