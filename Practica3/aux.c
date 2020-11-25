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
  if(pdict){
    if(pdict->table) free(pdict->table);
    free(pdict);
  }
}

int insert_dictionary(PDICT pdict, int key){

  int j=0, aux=0, L=0, F=0, cont=0;

  if(!pdict)return ERR;

  printf("%d", key);

  if(pdict->size==pdict->n_data){

    pdict->size=pdict->size*2;
    pdict=realloc(pdict, pdict->size*(sizeof(PDICT)));
    if(!pdict)return ERR;

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

  F=pdict->table[0];
  F=pdict->table[pdict->n_data];

  cont=method(pdict->table, F, L, key ,ppos);

  if(*ppos==NOT_FOUND)return NOT_FOUND;

  return cont;

}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
  int m = (int)F+L/2;
  int count=1;
  int flag = OK;

	if(!table||!ppos) return ERR;
  if(F>L) return NOT_FOUND;
  if(F==L) {
    if (table[F]== key) {
      *ppos = F;
      return count;
    }
    return NOT_FOUND;
  }


  if(table[m]== key){
    *ppos = m;
    return count;
  }

  else if(table[m]>key){
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
	int i,aux,count = 1;
  if(!table||!ppos) return ERR;

  if(table[F]==key){
    *ppos = F;
    return count;
  }
  for(i=F+1;i<=L;i++){
    count ++;
    if(table[i] == key){
      aux = table[i-1];
      table[i-1]=table[i];
      table[i] = aux;
      *ppos = i-1;
      return count;
    } 
  }
  return count;
}


short average_search_time(pfunc_search metodo, pfunc_key_generator generator,int order,int N, int n_times,PTIME_AA ptime){

  PDICT d=NULL;
  int *perm, count, *table;
  clock_t begin,end;
  double time=0;
  int max=0,min,count=0, a, ppos, j;

  d=init_dictionary(N, order);

  if(!d)return ERR;

  perm=generate_perm(N);

  if(!perm){
    free_dictionary(d);
  }

  count=massive_insertion_dictionary(d, perm, N);
  if(count==ERR){

    free_dictionary(d);
    free(perm);
  }
  free(perm);

  table=(int*)malloc(N*n_times*(sizeof(int)));
  if(!table){
    free_dictionary(d);
    return ERR;
  }

  generator(table, N*n_times, N);


  begin =clock();

  a=metodo(d->table, 0, N-1, table[0], &ppos);
  max=a;
  min=a;
  count +=a; 
  end = clock();
  /*La unidad de tiempo serán los microsegundos*/
  time += (end-begin)*(1000000/CLOCKS_PER_SEC); 
  for (j=1; j<N*n_times; j++){
    begin = clock();
    a = metodo(d->table, 0, N-1, table[j], &ppos);
    end = clock();
    time += (end-begin)*(1000000/CLOCKS_PER_SEC);

    if(max<a)
     max=a;
    if(min>a)
     min=a;
    count +=a;
  }
  
  free(table);

  ptime->max_ob = max;
  ptime->min_ob = min;
  ptime->N = N;
  ptime->average_ob = (double)count/(N*n_times);
  ptime->n_elems = (N*n_times);
  ptime->time = time/(N*n_times);
  return OK;
}
