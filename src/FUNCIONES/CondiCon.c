#include <math.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>

/********************************************************************/

void CondiCon(int ** BCC_flag,float ** BCC_data,int * type_elem,
	      int numels,int ** near_elem,float * Source_N,
	      float * Source_D, gsl_vector * S, float ** movility,
	      float ** dist_center_elem){
  
  /* Asignamos a cada arista de los volumenes del dominio, condiciones
  de contorno. Pueden ser condicion de Dirichlet (-1), Neumann (-2), 
  o sin condicion asignada (0). De manera predeterminada, las aristas
  internas, no tienen asignadas condiciones de contorno, y las aristas
  de contorno tienen asignada condicion de Neumann homogenea.
  Calculo de los terminos fuente para las condiciones de Dirichlet y de 
  Neumann.
  */

  // Inicializo las condiciones de contorno
  
  // Pongo condicion de neumann homogeneo en los contornos
  for(int i = 0;i<numels;i++){
    // Busca los volumenes de contorno y les asigna la condicion
    // de contorno en las aristas de contorno.
    if(type_elem[i] == -1){
	// En las aristas de contorno asigno la condicion de
	// Neumann
      for(int j = 0;j<4;j++){
	if(near_elem[i][j]<=0){
	    // Asigno Neumann homogéneo en los contornos
	    BCC_flag[i][j] = -2;
	    BCC_data[i][j] = 0;
	  } // End if near_elem
      } // End for j
    } // End if
  } // End for i

  
  // Leo condiciones de contorno
  
  FILE* CC;
  
  char mensajes[100];
  int aux_D,aux_N,CC_T,CC_Elem,CC_Aris;
  float CC_Value;
     
  // Abro el fichero de la malla */
  CC = fopen("CondiCon.dat","r");

  if(CC==NULL){
    printf("No se encuentra el fichero CondiCon.dat o esta dañado \n");
    exit(0);
  }
      
  while(feof(CC) == 0){

    fgets(mensajes,100,CC);

    aux_D = sscanf(mensajes,"%i \t %i \t %f",
		    &CC_T,
		    &CC_Elem,
		    &CC_Value);
    aux_N = sscanf(mensajes,"%i \t %i \t %i \t %f",
		   &CC_T,
		   &CC_Elem,
		   &CC_Aris,
		   &CC_Value);

    if(aux_D==3){
      // CC Dirichlet
      if(CC_T==-1){
	// Tipo de CC :
	BCC_flag[CC_Elem-1][0] = -1;
	// Valor :
	BCC_data[CC_Elem-1][0]= CC_Value;
	// Por convenio en el resto de las
	// celdas se dejan NAN
      } // End if      
    } // End if

    if(aux_N==4){
      // CC Neumann      
      if(CC_T==-2){
	// Tipo de CC :
	BCC_flag[CC_Elem-1][CC_Aris]= -2;
	// Valor :
	BCC_data[CC_Elem-1][CC_Aris]= CC_Value;
	// Por convenio en el resto de las
	// celdas se dejan NAN
      } // End if
    } // End if
    
  } // End while loop //
  
  // Cierro el fichero de las condiciones de contorno
  fclose(CC);


  // Asigno condiciones de contorno

  for(int i = 0;i<numels;i++){

    // Calculo de las condiciones de contorno de Dirichlet:
    // Directamente se impone el valor en esa celda. Los volumenes
    // con CCD directamente llevan asociada la etiqueta -1 en todas
    // las aristas (se mira por convenio en la arista 0.)
    if (BCC_flag[i][0] == -1){
      Source_D[i] = BCC_data[i][0];
    } // End if
    
    // Cálculo de las condiciones de contorno de Neumann:
    // Recorre las aristas del volumen
    for(int j = 0;j<4;j++){
      if (BCC_flag[i][j] == -2){
	Source_N[i] += BCC_data[i][j]*movility[i][j]*dist_center_elem[i][j];
      } // End if   
    } // End for j

    // Ensamblado del vector S (source) : 
    // El vector S contiene por un lado la componente asociada al valor
    // de la condicion de contorno de Neumman (-2) y por otro lado el valor de
    // la condicion de contorno de Dirichlet (-1). En un mismo elemento
    // podemos tener dos condiciones de contorno diferente

    gsl_vector_set(S, i,Source_D[i] - Source_N[i]);
    
  } // End for i


} // End CondiCon


