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
#include "times.h"
#include "sorting.h"
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
  //Insert Sort solo da ERROR si array[i] es NULL., pero ya hemos comprobado que no lo es antes
  a = metodo(array[0],0,N-1);
  max=a;
  min=a;
  count +=a; 
  end = clock();
  //La unidad de tiempo serán los microsegundos
  time += (end-begin)*(1000000/CLOCKS_PER_SEC); 
  for (i=1; i<n_perms; i++){
    begin = clock();
    a = metodo(array[i],0,N-1);
    end = clock();
    time += (end-begin)*(1000000/CLOCKS_PER_SEC);

    if(max>a) max=a;
    if(min<a) min=a;
    count +=a;
  }
  for(i=0;i<n_perms;i++){
    free(array[i]);
  }
  free(array);

  ptime->max_ob = max;
  ptime->min_ob = min;
  ptime->N = N;
  ptime->average_ob = (double) (count/n_perms);
  ptime->n_elems = n_perms;
  ptime->time = time/n_perms;
  return OK;
}



/*******************
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  int i;
  short flag = OK;
  PTIME_AA ptime;
  FILE *f;


  if(!method || !file ) return ERR;
  if(!(f = fopen(file, "w"))) return ERR;
  for(i=num_min;i<num_max && flag == OK; i+= incr){
    if(!(ptime = (PTIME_AA)malloc(sizeof(TIME_AA)))) flag = ERR;
    if(flag != ERR) flag = average_sorting_time(method,n_perms,i,ptime);
    if(flag != ERR) flag = save_time_table(f, ptime,n_perms);
    free(ptime);
  }
  fclose(f);
  if(flag==ERR) return ERR;
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(FILE* file, PTIME_AA ptime, int n_times)
{
  short flag = OK;
  if(!ptime) return ERR;

  flag = fprintf(file,"|   %d   | %lf |  %lf   |   %d   |   %d   |   %d   |\n",ptime->N,ptime->time,ptime->average_ob,ptime->max_ob,ptime->min_ob,n_times);

  if (flag != -1)return OK;
  return ERR;
}
