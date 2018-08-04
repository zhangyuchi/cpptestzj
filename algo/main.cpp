//
// Created by zhangjun on 18-8-3.
//

#include <stdio.h>
#include "quicksort.h"
#include "insertsort.h"
#include "invertlist.h"

//raft, fast raft. leveldb, rocksdb
int print_vec(const std::vector<int> &data){
  printf("<");
  for(int v : data){
    printf("%d,", v);
  }
  printf(">\n");
}


int main(){

  printf("welcome to algo show\n");
  printf("quicksort algo show\n");
  QuickSort qs;
  std::vector<int> data{3,4,1,2,5};
  print_vec(data);
  qs.Run(data);
  print_vec(data);

  return 0;
}