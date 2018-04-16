
#include <math.h>


/********************************************************************/

void topology(float ** iverts, float ** center_elem,float ** dist_center_elem,
	      float ** ielem, float * v_area_elem, float ** l_lado_elem,
	      int ** near_elem,int * type_elem , float ** n_x_elem, float ** n_y_elem ,
	      int numels){

  // Resuelve la topología de la malla y calcula los siguientes valores:
  //    - Área de cada elemento (v_area_elem)
  //    - Longitud de cada lado para cada elemento (l_lado_elem)
  //    - Elementos ''vecinos'' de cada elemento (near_elem)
  //    - Indica si cada elemento pertenece al dominio o al contorno (type_elem)

  // Declaracion de variables

  int i,ii,j;

  int aux,aux2,aux3;

  int count[numels][4];

  float area1,area2;

  float coordinateX[4],coordinateY[4];

  // Recorre todos los elementos
  for(i = 0;i<=numels-1;i++){

    aux2 = 0; // Contador para saber si es elemento de contorno o no

    // Conectividades entre elementos //
  
    // Recorre el resto de los elementos //
    for(ii = 0;ii<=numels-1;ii++){

      if(i == ii) goto salida; // En el caso de i=ii

      if((ielem[i][0]==ielem[ii][3])&&(ielem[i][1]==ielem[ii][2])){ near_elem[i][0] = ii+1; aux2++;}
      
      if((ielem[i][1]==ielem[ii][0])&&(ielem[i][2]==ielem[ii][3])){ near_elem[i][1] = ii+1; aux2++;}
	
      if((ielem[i][2]==ielem[ii][1])&&(ielem[i][3]==ielem[ii][0])){ near_elem[i][2] = ii+1; aux2++;}
       
      if((ielem[i][3]==ielem[ii][2])&&(ielem[i][0]==ielem[ii][1])){ near_elem[i][3] = ii+1; aux2++;}
	
    salida:; // En el caso de i=ii

    }

    if(aux2<4){ type_elem[i] = -1; aux2 = 0; } // Es elemento de contorno
    // Asigno de manera predeterminada la etiqueta -1 a todos los elementos
    // que se encuentran en el contorno, la cual significa condición de
    // contorno de tipo Newmann homogéneo.
    

    // Coodenadas de los vértices de cada elemento
    for(j = 0;j<=3;j++){

      aux = ielem[i][j] - 1 ;

      coordinateX[j] = iverts[aux][0];
      coordinateY[j] = iverts[aux][1];
      
    } // End for j

    
    // Calculo las coordenas "x" e "y" del centro de cada elemento
    center_elem[i][0] = (coordinateX[2] + coordinateX[0])/2;
    center_elem[i][1] = (coordinateY[2] + coordinateY[0])/2;

    
    // Calculo el area de cada elemento
    
    v_area_elem[i] =fabs(0.5*(coordinateY[0]*(coordinateX[3] - coordinateX[1]) +
			      coordinateY[1]*(coordinateX[0] - coordinateX[2]) +
			      coordinateY[2]*(coordinateX[1] - coordinateX[3]) +
			      coordinateY[3]*(coordinateX[2] - coordinateX[0])));

    // Calculo la longitud de cada lado

    for(j = 0;j<=2;j++){

      l_lado_elem[i][j] = sqrt( pow((coordinateX[j] - coordinateX[j+1]),2) +
				pow((coordinateY[j] - coordinateY[j+1]),2) );

    } // End for j

    l_lado_elem[i][3] = sqrt( pow((coordinateX[3] - coordinateX[0]),2) +
			      pow((coordinateY[3] - coordinateY[0]),2) );


    // Calculo del vector normal a cada cara

    n_x_elem[i][0] = (coordinateY[1] - coordinateY[0])/l_lado_elem[i][0];
    n_y_elem[i][0] = (coordinateX[1] - coordinateX[0])/l_lado_elem[i][0];

    n_x_elem[i][1] = (coordinateY[1] - coordinateY[2])/l_lado_elem[i][1];
    n_y_elem[i][1] = (coordinateX[1] - coordinateX[2])/l_lado_elem[i][1];

    n_x_elem[i][2] = (coordinateY[3] - coordinateY[2])/l_lado_elem[i][2];
    n_y_elem[i][2] = (coordinateX[3] - coordinateX[2])/l_lado_elem[i][2];

    n_x_elem[i][3] = (coordinateY[3] - coordinateY[0])/l_lado_elem[i][3];
    n_y_elem[i][3] = (coordinateX[3] - coordinateX[0])/l_lado_elem[i][3];

    
  } // End for i


  // Distancia entre centros para cada elemento
  // Recorre todos los elementos
  for(i = 0;i<=numels-1;i++){
    for(j = 0; j<=3; j++){
      
      aux3 = near_elem[i][j];

      // Calcula las distancia entre centros de los elementos
      // adyacentes, si es de contono, asigna la sitancia a la
      // longitud de la arista del contorno.
      
      if(aux3 > 0){
      dist_center_elem[i][j] = sqrt(pow((center_elem[aux3-1][0] - center_elem[i][0]),2) +
      			    pow((center_elem[aux3-1][1] - center_elem[i][1]),2)) ;
      }
      else{
      dist_center_elem[i][j] = l_lado_elem[i][j];
      }

    } // End for j

    
  } // End for i
 

} // End topology
