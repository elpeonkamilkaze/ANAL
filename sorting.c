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

int InsertSort(int* table, int ip, int iu)
{
  int aux,i,j,cont=0;
  if(!table||iu<0||ip<0) return ERR;

  for(i=ip+1;i<=iu;i++){

    aux=table[i];
    j=i-1;
    
    for(;j>=ip && table[j]>aux;cont++,j--){

      table[j+1]=table[j];
      
      
    }
    table[j+1]=aux;
    cont++;
  }
  
  return cont;
}


int InsertSortInv(int* table, int ip, int iu)
{
  int aux,i,j,cont=0;
  if(!table||iu<0||ip<0) return ERR;

  for(i=ip+1;i<=iu;i++){

    aux=table[i];
    j=i-1;
    
    for(;j>=ip && table[j]<aux;cont++, j--){

      table[j+1]=table[j];
      
      
    }
    table[j+1]=aux;
    cont++;
  }
  
  return cont;
}


