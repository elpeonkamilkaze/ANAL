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
  int aux,i,j,cont=0, flag;
  if(!table||iu<0||ip<0) return ERR;

  for(i=ip+1;i<=iu;i++){
    flag=1;
    aux=table[i];
    j=i-1;
    
    for(cont++;j>=ip && flag == 1;j--){

      if (table[j]>aux) {
        table[j+1]=table[j];
      }
      else{
        flag = 0;
        j++;
      } 
      cont++;
    }
    table[j+1]=aux;
  }
  
  return cont;
}


int InsertSortInv(int* table, int ip, int iu)
{
  int aux,i,j,cont=0, flag;
  if(!table||iu<0||ip<0) return ERR;

  for(i=ip+1;i<=iu;i++){
    flag=1;
    aux=table[i];
    j=i-1;
    
    for(;j>=ip && flag==1; j--){
      cont++;

      if(table[j]<aux) table[j+1]=table[j];

      else flag=0;
 
    }
    
    table[j+1]=aux;
    
  }
  
  
  return cont;
}


