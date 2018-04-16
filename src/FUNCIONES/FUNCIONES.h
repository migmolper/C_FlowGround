// Librerias para GSL
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

// Declaracion implicita de funciones 

/* Funciones auxiliares del programa */
extern void mesh_info(int*,int*);
extern void ** mat_din(int,int,int);
extern void ** mat_din_0(int,int,int);
extern void * vect_din(int,int);
extern void * vect_din_0(int, int);
extern void vect_ini_I(int *,int,int);
extern void vect_ini_F(float *,int,float);
extern void mat_ini_I(int **,int,int,int);
extern void mat_ini_F(float **,int,int,float);
extern void print_C_FG(char *);

/* Funciones para la lectura de la malla */
extern void mesh_data(float **,float **,int,int);
extern void output_mesh_info(int,int);

/* Funciones para el calculo de la topologia de la malla */
extern void topology(float **,float **,float **,float **,
	      float *,float **,int **,int *, float **, float **, int);
extern void output_topology(int *,float **,float *,float **,int **,
			    float **,int,float **,float **);

/* Funciones para la lectura de los parametros fisicos del problema */
extern void read_physical_parameters(float *,float *,float *,float *,
				     float *,int);
extern void calc_physical_parameters(float **,float *,float *,int *,
				     float,float,float,float **,float **,
				     int,float **,int **,float *,float **);
extern void output_physical_parameters(float ** sign_movility,
				       float deltat, float compress,
				       float visc,int numels);

/* Funciones para las condiciones de contorno  */
extern void CondiCon(int **,float **,int *,int,int **,float *,float *,
		     gsl_vector *, float **,float **);
extern void output_CondiCon(int **,float **,float *,float *,int);

/* Funciones para las condiciones iniciales */
extern void CondIni(gsl_vector *,int);
extern void output_CondIni(gsl_vector *,int);

/* Funciones para el ensamblado de la matriz */
extern void assemble(float,float,float *,int **,float **,
		     float **,int,int **,gsl_matrix *,
		     gsl_vector *);
extern void output_assemble(gsl_matrix *,int);

/* Funciones para generar el vector del término independiente*/

extern void assemble_S_tot(gsl_vector *, gsl_vector *,gsl_vector *,
			   gsl_vector *, int);



