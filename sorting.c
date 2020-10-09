/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/

int InsertSort(int* tabla, int ip, int iu)
{
  int aux,i,j,cont=0;
  if(!tabla||iu<0||ip<0) return -1;

  for(i=ip+1;i<=iu;i++){

    aux=tabla[i];
    j=i-1;
    
    for(;j>=ip && tabla[j]>aux;cont++){

      tabla[j+1]=tabla[j];
      j--;
      
    }
    tabla[j+1]=aux;
    cont++;
  }
  
  return cont;
}


int InsertSortInv(int* table, int ip, int iu)
{
  int aux,i,j,cont=0;
  if(!table||iu<0||ip<0) return -1;

  for(i=iu-1;i>=ip;i--){

    aux=table[i];
    j=i-1;
    
    for(;j>=ip && table[j]>aux;cont++){

      table[j+1]=table[j];
      j--;
      
    }
    table[j+1]=aux;
    cont++;
  }
  
  return cont;
}


