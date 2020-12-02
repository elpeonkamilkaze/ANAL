/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
<<<<<<< HEAD
 * Version: 1.0
=======
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
>>>>>>> 9891c41bff00f20e8cae6b3e3ac5a7b0fffdd0be
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "times.h"
#include "search.h"
#include "permutations.h"

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo,  int n_perms, int N, PTIME_AA ptime)
{
  int i,a,max=0,min,count=0;
  int **array;
  clock_t begin,end;
  double time=0;


  if(!metodo || !ptime) return ERR;
  if(!(array = generate_permutations(n_perms,N)))return ERR;

  begin = clock();
  /*Insert Sort solo da ERROR si array[i] es NULL., pero ya hemos comprobado que no lo es antes*/
  a = metodo(array[0],0,N-1);
  
  max=a;
  min=a;
  count +=a; 
  end = clock();
  /*La unidad de tiempo serán los microsegundos*/
  time += (end-begin)*(1000000/CLOCKS_PER_SEC); 
  for (i=1; i<n_perms; i++){
    begin = clock();
    a = (int)metodo(array[i],0,N-1);
    end = clock();
    time += (end-begin)*(1000000/CLOCKS_PER_SEC);

    if(max<a)
     max=a;
    if(min>a)
     min=a;
    count +=a;
  }
  for(i=0;i<n_perms;i++){
    free(array[i]);
  }
  free(array);

  ptime->max_ob = max;
  ptime->min_ob = min;
  ptime->N = N;
  ptime->average_ob = (double)count/n_perms;
  ptime->n_elems = n_perms;
  ptime->time = time/n_perms;
  return OK;
}



/********************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  int i,j, n_times;
  short flag = OK;
  PTIME_AA ptime;

  if (incr == 0) return ERR;
  if(!method || !file ) return ERR;

  n_times = (int) (num_max-num_min)/incr;
  if(!(ptime = (PTIME_AA)malloc(n_times*sizeof(TIME_AA)))) flag = ERR;

  for(i=num_min,j=0;i<=num_max && flag == OK && j<n_times; i*= incr,j++){
    flag = average_sorting_time(method,n_perms,i,&ptime[j]);
  }

  if(flag != ERR) flag = save_time_table(file, ptime,n_times);
  free(ptime);
  if(flag==ERR) return ERR;
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  int i;
  short flag = OK;
  FILE *f;

  if(!ptime || !file) return ERR;
  if(!(f = fopen(file,"w"))) return ERR;


  fprintf(f,"Size,Time,average_ob,max_ob,min_ob\n");
  for(i=0; i< n_times && flag != -1;i++){
    flag = fprintf(f,"%d,%f,%f,%d,%d\n",ptime[i].N,ptime[i].time,ptime[i].average_ob,ptime[i].max_ob,ptime[i].min_ob);
  }

  fclose(f);
  if (flag != -1)return OK;
  return ERR;
}
static int logn(int numero,int base){
  int res=0,comp=1;
  if(base<=0) return 0;
  while(numero >comp){
    comp *= base;
    res++;
  }
  return res;
}


short average_search_time(pfunc_search metodo, pfunc_key_generator generator,int order,int N, int n_times,PTIME_AA ptime){

  PDICT d=NULL;
  int *perm, count=0, *table;
  clock_t begin,end;
  
  double time=0;
  int max=0,min, a, flag, ppos, j;

  d=init_dictionary(N, order);

  if(!d)return ERR;

  perm=generate_perm(N);

  if(!perm){
    free_dictionary(d);
  }

  flag=massive_insertion_dictionary(d, perm, N);
  if(flag==ERR){

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
  end = clock();
  max=a;
  min=a;
  count +=a; 
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
  free_dictionary(d);
  ptime->max_ob = max;
  ptime->min_ob = min;
  ptime->N = N;
  ptime->average_ob = (double)count/(N*n_times);
  ptime->n_elems = (N*n_times);
  ptime->time = time/(N*n_times);
  return OK;
}

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times){
  int i,j,flag = OK;
  int times;
  PTIME_AA ptime;

  if(!file||!method||!generator) return ERR;
  times = logn(num_max/num_min,incr);
  if(!(ptime = (PTIME_AA)malloc(times*sizeof(TIME_AA)))) return ERR;

  for(i=num_min,j=0;i<=num_max && flag == OK && j< times;i*=incr,j++){
    flag = average_search_time(method, generator, order,i,  n_times, &ptime[j]);
  }

  if(flag == OK) flag = save_time_table( file,  ptime, times);
  free(ptime);


  return flag;
}