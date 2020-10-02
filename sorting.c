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
  
  int i, j, max, aux, cont=0;

  if(!table)return ERR;

  i=ip;
  while(i<iu){

    max=i;

    for(j=i+1;j<=iu;j++){

        cont++;

        if(table[j]<table[max]){
          max=j;
        }
        
    }
    aux=table[i];
    table[i]=table[max];
    table[max]=aux;
    i++;
  }

  return cont;
}


int InsertSortInv(int* table, int ip, int iu)
{
    int i, j, max, aux, cont=0;

  if(!table)return ERR;

  i=ip;
  while(i<iu){

    max=i;

    for(j=i+1;j<=iu;j++){

        cont++;

        if(table[j]>table[max]){
          max=j;
        }
        
    }
    aux=table[i];
    table[i]=table[max];
    table[max]=aux;
    i++;
  }

  return cont;
}


