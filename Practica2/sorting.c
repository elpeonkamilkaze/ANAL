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

int split(int* table, int ip, int iu,int *pos);

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
  int i,j,k,count=0;
  t = (int *)malloc((iu-ip+1)*sizeof(int));
  if (!t) return ERR;

  i = ip;
  j = imiddle+1;
  k = 0;

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
    count++;
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

  for(i=ip,j=0;i<=iu;i++,j++){
    table[i] = t[j];
  }
  free(t);
  return count;
}

int MergeSort(int* table, int ip, int iu){
  int M,count=0,count2;
  if (!table || ip<0 || iu<0 || ip>iu) return ERR;
  if (ip == iu) return OK;

  M= ((ip+iu) - ((ip+iu) %2))/2;

  count= MergeSort(table,ip,M);
  if (count == ERR) return ERR;
  count2 = MergeSort(table,M+1,iu);
  if (count2 == ERR) return ERR;
  count += count2;
  count2 = merge(table,ip,iu,M);
  if(count2 == ERR) return ERR;
  return (count + count2);
}


int quicksort(int* table, int ip, int iu){

    int pos, cont=0, c;

    if(!table||ip<0||iu<0){
      

      return ERR;
    }

    if(iu<ip){
      

      return ERR;
    }

    if(ip==iu){
      

      return 0;
    }

    cont+=split(table, ip, iu, &pos);

    if(ip<((pos)-1)){

        c=quicksort(table, ip, ((pos)-1));
        if(c==-1)return ERR;

        cont+=c;

    }
    if(iu>pos+1)c=quicksort(table, ((pos)+1), iu);
    if(c==-1)return ERR;

    cont+=c;

   

    return cont;

}

int median(int *table, int ip, int iu,int *pos){

    (*pos)=ip;

    return 0;

}

int split(int* table, int ip, int iu,int *pos){

    int i, k, aux, cont=0;

    cont+=median(table, ip, iu, pos);

    k=table[(*pos)];

    for(i=ip+1;i<=iu;i++){
        cont++;
        if(table[i]<k){

            (*pos)++;
            aux=table[i];
            table[i]=table[(*pos)];
            table[(*pos)]=aux;

        }

    }

    aux=table[ip];
    table[ip]=table[(*pos)];
    table[(*pos)]=aux;

    return cont;

}

int quicksortntr(int* table, int ip, int iu){

    int pos, cont=0, c=0;

    if(iu<ip||!table||ip<0||iu<0){
      
      return ERR;
    }

  while(ip<iu){
   
        cont+=split(table, ip, iu, &pos);

        if(ip<((pos)-1)){
  
            c=quicksortntr(table, ip, pos-1);
            if(c==-1)return ERR;

            cont+=c;

        } 
        
        ip=(pos)+1;

    }
    return cont;
}