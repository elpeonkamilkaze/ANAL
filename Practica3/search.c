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
#include "times.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

PDICT init_dictionary (int size, int order){

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
  if(pdict){
    if(pdict->table) free(pdict->table);
    free(pdict);
  }
}

int insert_dictionary(PDICT pdict, int key){

  int j=0, aux=0, L=0, F=0, cont=0;

  if(!pdict)return ERR;

  if(pdict->size==pdict->n_data){

    pdict->size=pdict->size*2;
    pdict=realloc(pdict, pdict->size*(sizeof(PDICT)));
    if(!pdict)return ERR;

  }
  if(pdict->order==NOT_SORTED||pdict->n_data==0){

      pdict->table[pdict->n_data]=key;
      pdict->n_data++;
      return 0;

  }

  else{

    L=pdict->n_data;
    aux=key;
    j=L-1;
    while(j>=F && pdict->table[j]>aux){
      cont++;
      pdict->table[j+1]=pdict->table[j];
      j--;

    }
    if(j>=F)cont++;

    pdict->table[j+1]=key;
    pdict->n_data++;

    return cont;

  }
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
	int i,flag=OK,count = 0;
  if(!keys) return ERR;
  for(i=0;i<n_keys && flag != ERR;i++){
    flag = insert_dictionary(pdict, keys[i]);
    count += flag;
  }
  
  if(flag == ERR) return ERR;
  return count;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){

  int cont=0, F=0, L=0;

  if(!pdict||!method||!ppos)return ERR;

  F=0;
  L=pdict->n_data;

  cont=method(pdict->table, F, L, key ,ppos);

  if(*ppos==NOT_FOUND)return NOT_FOUND;

  return cont;

}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
  int m = (int)((F+L)/2);
  int count=1;
  int flag = OK;
  
	if(!table||!ppos)return ERR;

  if(F>L){
    *ppos=NOT_FOUND;
    return 0;
  }
  
  if(F==L) {
    if (table[F]== key) {
      *ppos = F+1;
      return count;
    }
    *ppos=NOT_FOUND;
    return count;
  }


  if(table[m]== key){
    *ppos = m+1;
    return count;
  }

  else if(table[m]<key){
    flag = bin_search(table,m+1,L,key,ppos);
    if(flag == ERR) return ERR;
    return count + flag;
  }
  else{
    flag = bin_search(table,F,m-1,key,ppos);
    if(flag == ERR) return ERR;
    return count + flag;
  }
}

int lin_search(int *table,int F,int L,int key, int *ppos){

  int i=0, size=0, cont=0; 

  if(!table||L<F||!ppos)return ERR;

  size=L-F+1;

  for (i = 0; i < size; i++){ 
    cont++;
    if (table[i] == key){

      *ppos=i+1;
      return cont;

    }
      
  }
    *ppos=NOT_FOUND;
    return cont; 

}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
	int i,aux,count = 1;
  if(!table||!ppos) return ERR;

  if(table[F]==key){
    *ppos = F+1;
    return count;
  }
  for(i=F+1;i<=L;i++){
    count ++;
    if(table[i] == key){
      aux = table[i-1];
      table[i-1]=table[i];
      table[i] = aux;
      *ppos = i;
      return count;
    } 
  }
  return count;
}


