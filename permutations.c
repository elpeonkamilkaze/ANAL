/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Pablo Soto y Sergio Leal
 * Version: 1.0
 * Fecha: 21-09-2019
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include "permutations.h"

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{

  return (int)((double)rand()*(double)(sup-inf+1)/(double)RAND_MAX)+inf;
}
/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i, aux, j;
  int *perm;
  perm=(int*)malloc(N*sizeof(int));
  if(!perm)return NULL;

  for(i=0;i<N;i++){

    perm[i]=i+1;

  }
for(i=0;i<N;i++){
  

  j=random_num(i, N-1);
  aux=perm[i];
  perm[i]= perm[j];
  perm[j]=aux;

}

return perm;

}


/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N){
  int i,flag=0;
  int **salida;
  salida = (int**)malloc(n_perms*sizeof(int*));
  if (!salida) return NULL;
  for(i=0;i<n_perms && flag==0;i++){
    if(!(salida[i] = generate_perm(N))) flag= 1;
  }
  
  if(flag==1){
    for(;i>=0;i--){
      free(salida[i]);
    }
    free(salida);
    return NULL;
  }
  
  return salida;    
  
}

