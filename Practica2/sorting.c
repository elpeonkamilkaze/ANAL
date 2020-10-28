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
    
    for(;j>=ip&&aux<table[j];j--){
      cont++;
     
        table[j+1]=table[j];
     
    }
    if(j>=ip)cont++;

    table[j+1]=aux;
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
    
    for(;j>=ip&&aux>table[j];j--){
      cont++;
     
        table[j+1]=table[j];
     
    }
    if(j>=ip)cont++;

    table[j+1]=aux;
  }
  
  return cont;
}

int merge(int *table, int ip, int iu, int imiddle){
  int *t;
  int i,j,k;

  t = (int *)malloc((iu-ip+1)*sizeof(int));
  if (!t) return ERR;

  i = iu;
  j = imiddle+1;
  k = ip;

  while (i<=imiddle && j<=iu){
    if (table[i]<table[j]){
      t[k] = table[i];
      i++;
    }
    else{
      t[k] = table[j];
      j++;
    }
    k++;
  }

  if (i>imiddle){
    while (j<=iu){
      t[k] = table[j];
      j++;
      k++;
    }
  }
  else if (j>iu){
    while (i<=imiddle){
      t[k] = table[i];
      i++;
      k++;
    }
  }
  for(i=ip,j=0;i<iu;i++,j++){
    table[i] = t[j];
  }
  free(t);
  return OK;
}

int MergeSort(int* table, int ip, int iu){
  int M;
  if (!table || ip<0 || iu<0 || ip>iu) return ERR;

  if (ip == iu) return OK;

  M= ((ip+iu) - ((ip+iu) %2))/2;

  MergeSort(table,ip,M);
  MergeSort(table,M+1,iu);
  return Combine(table,ip,M,iu);
}