/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

#define SIZE 16

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order){

  DICT* dict=NULL;

  if(size<=0||(order!=SORTED && order!=NOT_SORTED))return NULL;

  dict=(DICT*)calloc(1, sizeof(DICT));
  if(!dict)return NULL;

  dict->size=size;
  dict->order=order;

  dict->table=(int*)calloc(size, sizeof(int));
  if(!dict->table){

    free_dictionary(dict);
    return NULL;

  }

  dict->n_data=0;

  return dict;

}
	


void free_dictionary(PDICT pdict)
{
	/* your code */
}

int insert_dictionary(PDICT pdict, int key){

  int j=0, aux=0, L=0, F=0, cont=0;

  if(!pdict)return ERR;

  if(pdict->size==pdict->n_data){

    pdict->size=pdict->size*2;
    pdict=realloc(pdict, pdict->size*(sizeof(PDICT)));
    if(!pdict)return NULL;

  }
  if(pdict->order==NOT_SORTED||pdict->n_data==0){

      pdict->table[pdict->n_data]=key;
      pdict->n_data++;
      return 1;

  }

  else{

    pdict->table[pdict->n_data]=key;
    F=pdict->table[0];
    L=pdict->table[pdict->n_data];
    aux=pdict->table[L];
    j=L-1;
    while(j>=F && pdict->table[j]>aux){
      cont++;
      pdict->table[j+1]=pdict->table[j];
      j--;

    }
    if(j>=F)cont++;

    pdict->table[j+1]=aux;
    pdict->n_data++;
    return cont;

  }
}


int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
	/* your code */
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){

  int cont=0, F=0, L=0;

  if(!pdict||!method||!ppos)return NULL;

  F=pdict->table[0];
  F=pdict->table[pdict->n_data];

  cont=method(pdict->table, F, L, key ,ppos);

  if(*ppos==NOT_FOUND||cont==ERR)return ERR;

  return cont;

}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
	/* your code */
}

int lin_search(int *table,int F,int L,int key, int *ppos){

  int i=0, size=0, cont=0; 

  if(!table||L<F||!ppos)return ERR;

  size=F-L+1;

  for (i = 0; i < size; i++){ 
    cont++;
    if (table[i] == key){

      *ppos=i;
      return cont;

    }
      
  }
    *ppos=NOT_FOUND;
    return cont; 

}


int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	/* your code */
}


