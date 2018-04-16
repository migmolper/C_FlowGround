#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/********************************************************************/

void read_physical_parameters(float * perm,float * visc,float * compress,
			      float * deltat,float * t_end, int numels){

  // Lectura a partir de un fichero externo de los parámetros fisicos
  // y uno numerico del problema.

  // Permeabilidad

  //Semilla que genera los numero aleatorios
  srand(time(NULL)); 

  for (int i = 0;i<=numels;i++){
    perm[i] = pow(1,-(8+rand()%6));
  }  
  *visc = pow(10,-6); // Viscosidad dinamica
  *compress = pow(4,-10); // Compresibilidad del medio
  *deltat = 0.01; // Paso de integracion temporal
  *t_end = 100; // Tiempo final de calculo


} // End read_physical_parameters

/********************************************************************/

void calc_physical_parameters(float ** dist_center_elem,
			      float * v_area_elem,float * perm,int * type_elem,
			      float visc,float compress,float deltat,
			      float ** n_x_elem,float ** n_y_elem,int numels,
			      float ** l_lado_elem,int ** near_elem,
			      float * lambda,float ** movility){

  // Calculamos algunos de los parámetros físicos
  // del problema, como las movilidades.
    
  // Variables auxiliares
  int aux,i,j;
  float N[4][2] = {{1,0},{0,1},{1,0},{0,1}};

  for(i = 0;i<=numels;i++){
    // Cálculo del parámetro lambda, que se calcula de la misma forma
    // independientemente de que sea de contorno o de dominio
    lambda[i] = perm[i]/visc;
    // Es necesario calcularlo en un bucle independiente, ya que para
    // calcular las movilidades es necesario tener calculados previamente
    // los valores, de otra forma, al inicializar con NAN, da problemas.    
  }

  // Recorro todos los elementos del dominio
  for(i = 0;i<=numels-1;i++){
    
    for(j = 0;j<=3;j++){

      // Cálculo de la movilidad en las aristas
      if(near_elem[i][j] > 0){

	// Movilidad en las aristas de dominio
	aux = near_elem[i][j] - 1;  
	movility[i][j] = 2*(lambda[i]*lambda[aux])/(lambda[i] + lambda[aux]);

      }
      else{
	
	// Movilidad en las aristas de contorno
	movility[i][j] = 2*lambda[i]/l_lado_elem[i][j];
	
      }
      // Fin calculo de las movilidades


    } // End j
  } // End i


} // End calc_physical_parameters
