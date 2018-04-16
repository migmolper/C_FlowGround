#include <gsl/gsl_matrix.h>

/********************************************************************/

void assemble_S_tot(gsl_vector * S_tot, gsl_vector * S_ast,
		    gsl_vector * S, gsl_vector * Pn0, int numels){

  float aux;
  
  for(int i = 0;i<numels;i++){

    aux = gsl_vector_get(S_ast,i)*gsl_vector_get(Pn0,i) +
      gsl_vector_get(S,i);
    
    gsl_vector_set(S_tot, i,aux);

  } // End for i
  
} // End assemble_S_tot
