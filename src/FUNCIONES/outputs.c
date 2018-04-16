
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

/////////////////////////////////////////////////////////////////

void print_C_FG(char text []){
  FILE * rep_C_FlowGround;
  rep_C_FlowGround = fopen("./RESULTADOS/process.rep","a+");
  fprintf(rep_C_FlowGround,text);
  fclose(rep_C_FlowGround);
}


/////////////////////////////////////////////////////////////////

void output_mesh_info(int numels,int numverts){

  FILE * rep_C_FlowGround;
  
  rep_C_FlowGround = fopen("./RESULTADOS/mesh_info.rep","w");

  fprintf(rep_C_FlowGround,
	  "Inicio de la lectura de la malla de calculo \n");

  fprintf(rep_C_FlowGround,
	  "\t Numero de elementos en la malla : %d \n",numels);
  fprintf(rep_C_FlowGround,
	  "\t Numero de nodos de la malla : %d \n",numverts);

  fprintf(rep_C_FlowGround,
	  "Fin de la lectura de la malla de calculo \n");

  fclose(rep_C_FlowGround);

}


/////////////////////////////////////////////////////////////////

void output_topology(int * type_elem,float ** center_elem,
		     float * v_area_elem,float ** l_lado_elem,
		     int ** near_elem,float ** dist_center_elem,
		     int numels,float ** n_x_elem,float ** n_y_elem){

  FILE * rep_C_FlowGround;
  
  rep_C_FlowGround = fopen("./RESULTADOS/topology.rep","w");

  fprintf(rep_C_FlowGround,
	  "Inicio de la topolog√≠a \n");	  

    // Resultados parados al fichero C_FlowGround.rep
  for(int i = 0;i<=numels-1;i++){

    fprintf(rep_C_FlowGround,
	    "Datos del elemento : %i \n",i+1);

    /////////////////////////////////////////////////////////////////
    
    fprintf(rep_C_FlowGround,
	    "\t Tipo de elemento : %i \n",
	    type_elem[i]);

    if(type_elem[i] != type_elem[i]){
      printf("NAN value en type_elem[%i]\n",i+1);
      exit(0);
    }

    /////////////////////////////////////////////////////////////////
    
    fprintf(rep_C_FlowGround,
	    "\t Coordenadas del centro del elemento : [%f ; %f] \n",
	    center_elem[i][0],center_elem[i][1]);

    if((center_elem[i][0] == NAN)||(center_elem[i][1] == NAN)){
      printf("NAN value en center_elem[%i][]\n",i+1);
      exit(0);
    }

    /////////////////////////////////////////////////////////////////
    
    fprintf(rep_C_FlowGround,
	 "\t Area del elemento : %f \n",
	   v_area_elem[i]);

    if(v_area_elem[i] != v_area_elem[i]){
      printf("NAN value en v_area_elem[%i]\n",i+1);
      exit(0);
    }
    if(v_area_elem[i] <= 0){
      printf("0 or negative value en v_area_elem[%i]\n",i+1);
      exit(0);
    }    

    /////////////////////////////////////////////////////////////////


    fprintf(rep_C_FlowGround,
	    "\t Longitud de sus aristas : %f , %f , %f , %f \n",
	    l_lado_elem[i][0],
	    l_lado_elem[i][1],
	    l_lado_elem[i][2],
	    l_lado_elem[i][3]);

    for(int j = 0;j<=3;j++){
      if(l_lado_elem[i][j] != l_lado_elem[i][j]){
	printf("NAN value en l_lado_elem[%i][%i]\n",i+1,j);
	exit(0);
      }
      if(l_lado_elem[i][j] <= 0){
	printf("0 or negative value en l_lado_elem[%i][%i]\n",i+1,j);
	exit(0);
      }
    }

    /////////////////////////////////////////////////////////////////
    
    fprintf(rep_C_FlowGround,
	    "\t Elementos adyacentes : %i ,%i, %i, %i \n",
	   near_elem[i][0],near_elem[i][1],near_elem[i][2],near_elem[i][3]);
    
    for(int j = 0;j<=3;j++){
      if(near_elem[i][j] != near_elem[i][j]){
	  printf("NAN value en near_elem[%i][%i]\n",i+1,j);
	  exit(0);
      }
    }

    /////////////////////////////////////////////////////////////////

    fprintf(rep_C_FlowGround,
	    "\t Distancias entre centros : %f, %f, %f, %f \n",
    	   dist_center_elem[i][0],dist_center_elem[i][1],
	   dist_center_elem[i][2],dist_center_elem[i][3]);

    for(int j = 0;j<=3;j++){
      if(dist_center_elem[i][j] != dist_center_elem[i][j]){
	printf("NAN value en dist_center_elem[%i][%i]\n",i+1,j);
	exit(0);
      }
      if(dist_center_elem[i][j] <= 0){
	printf("0 or negative value en dist_center_elem[%i][%i]\n",i+1,j);
	exit(0);
      }
      
    }

    /////////////////////////////////////////////////////////////////
    

    for(int j = 0;j<=3;j++){
      fprintf(rep_C_FlowGround,
	      "\t Vector normal a la cara %i  : [%f;%f]\n",
	      j,n_x_elem[i][i],n_y_elem[i][j]);

      if((n_x_elem[i][j] != n_x_elem[i][j])||
	 (n_y_elem[i][j] != n_y_elem[i][j])){
	printf("NAN value en n_()_elem[%i][%i]\n",i,j);
	exit(0);
      }
    }

    /////////////////////////////////////////////////////////////////
    
  }   

  fprintf(rep_C_FlowGround,
	  "Topologia finalizada \n");

  fclose(rep_C_FlowGround);

  /////////////////////////////////////////////////////////////////

  rep_C_FlowGround = fopen("./RESULTADOS/centers.rep","w");

  for(int i = 0;i<numels;i++){
    fprintf(rep_C_FlowGround,"%f \t %f \n",
	   center_elem[i][0],
	   center_elem[i][1]);
  }
  
  fclose(rep_C_FlowGround);  

} // End output_topolgy



/////////////////////////////////////////////////////////////////

void output_physical_parameters(float ** movility,
				float deltat, float compress,
				float visc,int numels){
  FILE * rep_C_FlowGround;
  
  rep_C_FlowGround = fopen("./RESULTADOS/movilidades.rep","w");

  fprintf(rep_C_FlowGround,
	  "Resultados de Physical parameters \n");

  for(int i = 0;i<=numels-1;i++){
    
    fprintf(rep_C_FlowGround,
	    "Movilidades del elemento : %i \n",i+1);
    for(int j = 0;j<=3;j++){
    
      fprintf(rep_C_FlowGround,
	      "\t Movilidad en la arista %i : %f \n",
	      j,movility[i][j]);
      
      if(movility[i][j] != movility[i][j]){
	printf("NAN value en sign_movility[%i][%i]\n",i+1,j);
	exit(0);
      }
      
    }
  }  

  fprintf(rep_C_FlowGround,
	  "Physical parameters finalizado \n");

  fclose(rep_C_FlowGround);

}


/////////////////////////////////////////////////////////////////

void  output_CondiCon(int ** BCC_flag,float ** BCC_data,float * Source_N,
		      float * Source_D,int numels){

  FILE * rep_C_FlowGround;
 
  rep_C_FlowGround = fopen("./RESULTADOS/BCC.rep","w");
  
  fprintf(rep_C_FlowGround,
	  "Resultados de CondiCon \n");

  for(int i = 0;i<=numels-1;i++){

    fprintf(rep_C_FlowGround,
	    "Elemento %i : \n",i+1);

    if(BCC_flag[i][0]==-1){
      fprintf(rep_C_FlowGround,
	      "\t Condicion de %s en el volumen : %i \n",
	      "CC.Dirichlet",i+1);
    }    

    for(int j = 0;j<4;j++){
          if(BCC_flag[i][j]==-2){
	      fprintf(rep_C_FlowGround,
		      "\t Condicion de %s en la arista %i del volumen : %i \n"
		      ,"CC.Neumann",j,i+1);
	  } // End of
    } // End for j

  } // End for i

  fprintf(rep_C_FlowGround,
	  "CondiCon finalizado \n");
  
  fclose(rep_C_FlowGround);  
}


/////////////////////////////////////////////////////////////////

void output_assemble(gsl_matrix * K,int numels){

  FILE * rep_C_FlowGround;
  
  rep_C_FlowGround = fopen("./RESULTADOS/K_assemble.rep","w");

  fprintf(rep_C_FlowGround,
	  "Resultados de K_assemble \n");

  for (int i=0;i<numels;i++){

    fprintf(rep_C_FlowGround,"Fila : %i \n",i+1);
    
    for (int j=0;j<numels;j++){
      
      fprintf(rep_C_FlowGround,"| %f |",
	      gsl_matrix_get(K, i, j));
      
    } // End for j
    
    fprintf(rep_C_FlowGround,"\n");
    
  } // End for i
  
  fprintf(rep_C_FlowGround,
	  "K_assemble finalizado \n");
  
  fclose(rep_C_FlowGround);  

}


/////////////////////////////////////////////////////////////////

void output_CondIni(gsl_vector * Pn0,int numels){


  FILE * rep_C_FlowGround;
  
  rep_C_FlowGround = fopen("./RESULTADOS/output_CondIni.rep","w");

  fprintf(rep_C_FlowGround,
	  "Resultados de output_CondIni \n");

  for(int i = 0;i<=numels-1;i++){
    
    fprintf(rep_C_FlowGround,
	    "PresiÛn inicial en el elemento %i : %f\n",
	    i+1,
	    gsl_vector_get (Pn0,i));
           
  } // End for i


  fprintf(rep_C_FlowGround,
	  "output_CondIni finalizado \n");
  
  fclose(rep_C_FlowGround);    
  
}
