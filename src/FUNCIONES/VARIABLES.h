#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

// Varibles generales:
// i : contador
int i;

// Variables topologicas del problema:
int numels = 0, numverts = 0;
float ** iverts, ** ielem, ** l_lado_elem;
float ** n_x_elem, ** n_y_elem, ** center_elem;
float ** dist_center_elem;
float * v_area_elem;
int ** near_elem;
int * type_elem;

// Variables fisicas del problema:
// visc : viscosidad dinamica del fluido
// compress : compresibilidad del medio
float visc,compress;
float * perm, * lambda;

// Parametros numericos:
float deltat,t_i,t_end;
float ** sign_movility;
float ** sign, ** movility;
int ** BCC_flag;
float ** BCC_data;
float * Source_N, * Source_D;
gsl_vector * Pn1, * Pn0;
gsl_vector * S, * S_ast, *S_tot ;
gsl_permutation  * permutacion; 
gsl_matrix * K;
int s;

// Resultados
FILE* file_ans;
char file_name[80];
int step = 0;

