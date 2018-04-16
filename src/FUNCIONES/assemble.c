#include <math.h>
#include <stdio.h>
#include <gsl/gsl_matrix.h>

/********************************************************************/

void assemble(float compress,float deltat,float * v_area_elem,
		int ** near_elem,float ** movility,
		float ** dist_center_elem,int numels,int ** BCC_flag,
	      gsl_matrix * K,gsl_vector * S_ast){

  // Ensamblamos la matriz de permeabilidad K del sistema
  // K*P=B
  
  int aux;
  float cumulative;
  float aux_cross;

  // Recorro la matriz usando la diagonal principal y relleno los terminos cruzados
  // directamente desde cada diagonal sabiendo que la matriz es simetrica. 
  for(int i = 0;i<numels;i++){

    // Calculo los términos de los elementos sin
    // CCD
    if(BCC_flag[i][0] != -1){

      // Ensamblado de la matriz K

      cumulative = compress*v_area_elem[i]/deltat;

      gsl_vector_set(S_ast, i, cumulative);
	
      // Recorriendo la diagonal principal, estoy recorriendo los volumenes del dominio
      // por lo tanto necesitio recorrer tambien las aristas de cada volumen.
      for(int k = 0;k<4;k++){
	// Luego sumamos los terminos de los flujos en cada
	// arista del volumen, en caso de ser una arista
	// con condicion de contorno de Neumann (-2), se cancela.
	cumulative += (BCC_flag[i][k]!=-2)*movility[i][k]/
	  dist_center_elem[i][k];

	// Calculo de los terminos cruzados asociados a cada elementos.
	aux = near_elem[i][k] - 1;
     
	if((aux>=0)){
	  // Diagonal superior
	  aux_cross = - movility[aux][k]/
	    dist_center_elem[aux][k];
	  // Diagonal inferior
	  aux_cross = - movility[aux][k]/
	    dist_center_elem[aux][k];

	  gsl_matrix_set(K,i,aux,aux_cross);
	  gsl_matrix_set(K,aux,i,aux_cross);
	} // End if
      } // End for k
      
    gsl_matrix_set(K,i,i,cumulative);
    
    } // End if
    // Para el caso de condiciones de Dirichlet
  else{
    gsl_matrix_set(K,i,i,1);
  } // End else

  } // End for i

} // End assemble



