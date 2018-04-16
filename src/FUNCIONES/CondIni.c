#include <math.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>

/********************************************************************/

void CondIni(gsl_vector * Pn0,int numels){

  // Imponemos en cada volumen del dominio la condición inicial asignada

  for(int i = 0;i<=numels -1;i++){

    // Lectura del fichero de condiciones iniciales,
    // de momento, inicializamos a cero el vector.    
    gsl_vector_set(Pn0, i, 0.0);

  } // End for i
}
