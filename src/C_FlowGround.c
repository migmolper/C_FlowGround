
// Code : C_FlowGround
// Realease : 1.0
// Author : Miguel Molinos Pérez
// Date : 13/04/2018
// Compilation command : gcc C_FlowGround.c ./FUNCIONES/*.c -o C_FlowGround -lgsl -lgslcblas -lm -std=c99

// Librerías para el programa

// Librerias generales
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// GSL 
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>
// Librerias propias
#include "./FUNCIONES/FUNCIONES.h"
#include "./FUNCIONES/VARIABLES.h"
// Librerias sistema
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Función principal del programa C_FlowGround

int main(void){

  ////////////////////////////////////////////////////////////

  // Genero la carpeta de resultados
  struct stat st = {0};

  // Compruebo si ya existe la carpeta
  if (stat("./RESULTADOS", &st) == -1){
    // Genero la carpeta
    mkdir("./RESULTADOS",0700);
  }

  print_C_FG("Inicio de escritura de resultados: \n");
  
  ////////////////////////////////////////////////////////////

  print_C_FG("Inicio de lectura de la malla \n");

  // Inicio de la lectura de la malla de cálculo

  // Llamada a mesh_info : Queremos saber el número de elementos 
  // (numels) y de vértices de la malla (numverts).
  mesh_info(&numels,&numverts);
  output_mesh_info(numels,numverts);

  ////////////////////////////////////////////////////////////


  print_C_FG("Inicio del alocatado de variables \n");
  
  // Alocatado e inicializacion de variables para mesh_data
  iverts = (float **)mat_din(numverts,3,sizeof(float));
  ielem = (float **)mat_din(numels,4,sizeof(float));

  // Alocatado e inicialización de variables para topology  
  v_area_elem = (float *)vect_din(numels,sizeof(float));
  vect_ini_F(v_area_elem,numels,NAN);
  
  l_lado_elem = (float **)mat_din(numels,4,sizeof(float));
  mat_ini_F(l_lado_elem,numels,4,NAN); 
  
  near_elem = (int **)mat_din(numels,4,sizeof(int));
  mat_ini_I(near_elem,numels,4,-1);

  type_elem = (int *)vect_din(numels,sizeof(int));
  vect_ini_I(type_elem,numels,0);  

  n_x_elem = (float **)mat_din(numels,4,sizeof(float));
  mat_ini_F(n_x_elem,numels,4,NAN);

  n_y_elem = (float **)mat_din(numels,4,sizeof(float));
  mat_ini_F(n_y_elem,numels,4,NAN);
  
  center_elem = (float **)mat_din(numels,2,sizeof(float));
  mat_ini_F(center_elem,numels,4,NAN);

  dist_center_elem = (float **)mat_din(numels,4,sizeof(float));
  mat_ini_F(dist_center_elem,numels,4,NAN);

  // Alocatado e inicialización de variables de physical_parameters
  perm = (float *)vect_din(numels,sizeof(float));
  vect_ini_F(perm,numels,NAN);
  
  lambda = (float *)vect_din(numels,sizeof(float));
  vect_ini_F(lambda,numels,NAN);

  movility = (float **)mat_din(numels,4,sizeof(float));
  mat_ini_F(movility,numels,4,NAN);

  // Alocatado e inicialización de variables de CondiCon

  BCC_data = (float **)mat_din(numels,4,sizeof(float));
  mat_ini_F(BCC_data,numels,4,NAN);

  BCC_flag = (int **)mat_din(numels,4,sizeof(int));
  mat_ini_I(BCC_flag,numels,4,0);

  Source_N = (float *)vect_din(numels,sizeof(float));
  vect_ini_F(Source_N,numels,0);  

  Source_D = (float *)vect_din(numels,sizeof(float));
  vect_ini_F(Source_D,numels,0);

  // Esta parte se alocata con la librería GSL ya que es lo
  // que se va a usar para los calculos
  
  // Alocatado e inicializacion del termino independiente
  // El vector S incorpora los valores de las CC
  // El vector S_ast incorpora el termino C_t*omega/detalta_t
  // El vector S_tot totaliza los vectores anteriores
  S = gsl_vector_alloc(numels);
  S_ast = gsl_vector_alloc(numels);
  S_tot = gsl_vector_alloc(numels);
  gsl_vector_set_zero(S);
  gsl_vector_set_zero(S_ast);
  gsl_vector_set_zero(S_tot);
  
  // Alocatado e inicialización de variables de assemble
  // La matriz K_gsl la inicializo a 0.
  K = gsl_matrix_alloc(numels, numels);
  gsl_matrix_set_zero(K);
   
  // Alocato e inicializo los vectores de resultados
  // Pn0 es el vector de los valores del paso anterios
  // y Pn1 es el vector de resultados.
  Pn0 = gsl_vector_alloc(numels);
  Pn1 = gsl_vector_alloc(numels);
  gsl_vector_set_zero(Pn0);
  gsl_vector_set_zero(Pn1);

  // Alocatado de las variables usadas para la descomposicion
  // LU. La lista p de permutacion de indices para LU
  permutacion =  gsl_permutation_alloc(numels);  


  print_C_FG("Fin del alocatado de variables \n");
  
  ////////////////////////////////////////////////////////////

  print_C_FG("Inicio del calculo de la topologia \n");
  
  // Llamada a mesh_data :

  print_C_FG("Inicio de lectura de la malla en mesh_data \n");

  // Ejecución de la subrutina
  
  mesh_data(iverts,ielem, numels, numverts);

  print_C_FG("Fin de la lectura de la malla en mesh_data \n");

  
  ////////////////////////////////////////////////////////////
  
  // Llamada a topology :

  // Ejecución de la subrutina

  print_C_FG("Inicio del cálculo de la topología en topology \n");
  
  topology(iverts,center_elem,dist_center_elem,ielem,v_area_elem,
	   l_lado_elem,near_elem,type_elem,n_x_elem,n_y_elem,numels);

  print_C_FG("Fin del cálculo de la topología en topology \n");
  
  output_topology(type_elem,center_elem,v_area_elem,l_lado_elem,
		  near_elem,dist_center_elem,numels,n_x_elem,n_y_elem);

  ////////////////////////////////////////////////////////////

  
  // Llamada a physical_parameters :

  // Ejecución de la subrutina
   
  read_physical_parameters(perm,&visc,&compress,&deltat,&t_end,numels);


  print_C_FG("Inicio del cálculo de los parámetros físicos \n");
  
  calc_physical_parameters(dist_center_elem,v_area_elem,perm,type_elem,visc,
			   compress,deltat,n_x_elem,n_y_elem,numels,l_lado_elem,
			   near_elem,lambda,movility);
  
  print_C_FG("Fin del cálculo de los parámetros físicos \n");

  output_physical_parameters(movility,deltat,compress,visc,
			     numels);

  ////////////////////////////////////////////////////////////

  
  // Llamada a CondIni :

  print_C_FG("Inicio del cálculo de las condiciones iniciales \n");
 
  // Ejecución de la subrutina :

  // Cargo en Pn el valor de la condición inicial
  CondIni(Pn0,numels);

  print_C_FG("Fin del cálculo de las condiciones iniciales \n");

  output_CondIni(Pn0,numels);
  
  ////////////////////////////////////////////////////////////

  // Llamada a CondiCon :

  //Ejecución de la subrutina:

  print_C_FG("Inicio del cálculo de las condiciones de contorno \n");
  
  CondiCon(BCC_flag,BCC_data,type_elem,numels,near_elem,Source_N,
	   Source_D,S,movility,dist_center_elem);

  print_C_FG("Fin del cálculo de las condiciones de contorno \n");

  
  output_CondiCon(BCC_flag,BCC_data,Source_N,Source_D,numels);

  ////////////////////////////////////////////////////////////

  // Llamada a assemble :

  //Ejecución de la subrutina:

  print_C_FG("Inicio del ensamblado de la matriz de cálculo \n");

 
  assemble(compress,deltat,v_area_elem,near_elem,
	   movility,dist_center_elem,numels,
	   BCC_flag,K,S_ast);

  print_C_FG("Fin del ensamblado de K \n");
  
  output_assemble(K,numels);
  
  // Libero memoria
  // Antes de inicializar el cálculo, libero la memoria
  // para reducir la carga de la ram del ordenador en
  // el caso de modelos de gran tamaño
  
  // Libero la memoria de topology
  free(iverts);
  free(center_elem);
  free(dist_center_elem);
  free(v_area_elem);
  free(near_elem);
  free(l_lado_elem);
  free(type_elem);
  free(n_x_elem);
  free(n_y_elem);

  // Libero la memoria de calc_physical_parameters
  free(sign_movility);
  free(lambda);
  free(sign);
  free(movility);

  // Libero la memoria de CondiCon
  free(BCC_flag);
  free(BCC_data);
  free(Source_N);
  free(Source_D);

  ////////////////////////////////////////////////////////////

  // Operaciones previas con la libreria GSL. Primero le paso
  // los valores de K a una matriz de tipo GSL, segundo le
  // paso los valores del vector inicial a GSL y finalmente
  // genero 

  // Descomposicion LU
  gsl_linalg_LU_decomp(K, permutacion, &s);
    
  
  ////////////////////////////////////////////////////////////

  // Inicio de los cálculos

  t_i = 0;

  while(t_i<t_end){
    
    // Genero el vector con los términos independientes
    assemble_S_tot(S_tot,S_ast,S,Pn0,numels);
    
    // Resuelvo el sistema de ecuaciones en cada paso de tiempo
    gsl_linalg_LU_solve(K, permutacion, S_tot, Pn1);
    
    // Paso los resultados a unos ficheros
    sprintf(file_name, "./RESULTADOS/results_%i.res",step);
    file_ans = fopen(file_name, "w");
    gsl_vector_fprintf (file_ans,Pn1,"%f");
    fclose(file_ans);
    
    // Actualizo resultados
    gsl_vector_memcpy (Pn0,Pn1);   

    // Incremento el paso de tiempo
    // printf("Instante : %f \n",t_i);
    t_i += deltat;
    ++step;
    
  }

  // Libero la memoria
  gsl_matrix_free(K);
  gsl_vector_free(S);
  gsl_vector_free(S_ast);
  gsl_vector_free(S_tot);
  gsl_vector_free(Pn0);
  gsl_vector_free(Pn1);
  
  ////////////////////////////////////////////////////////////
  
  return 0;

} // End main
