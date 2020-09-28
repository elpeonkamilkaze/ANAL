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
  int i,a,max=0,min,count;
  int **array;
  clock_t begin,end;
  double time=0;
  
  array = generate_permutations(n_perms,N);
 begin = clock();
    a = InsertSort(array[i],0,N);
    end = clock();
    time += (end-begin)/CLOCKS_PER_SEC; 

  for (i=0; i<n_perms; i++){
    begin = clock();
    a = InsertSort(array[i],0,N);
    end = clock();
    time += (end-begin)/CLOCKS_PER_SEC;
<<<<<<< HEAD
    if(max>a) max=a;
    if(min<a) min=a;
    count +=a;
  }
}
=======

  }
}
/*******************
    if(max>a) max=a;
    count +=a;********************************/
>>>>>>> 9891c41bff00f20e8cae6b3e3ac5a7b0fffdd0be
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms)
{
  /* Your code */
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  /* your code */
}
<<<<<<< HEAD
=======


>>>>>>> 9891c41bff00f20e8cae6b3e3ac5a7b0fffdd0be
