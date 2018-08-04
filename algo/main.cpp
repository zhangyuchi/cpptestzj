//
// Created by zhangjun on 18-8-3.
//

#include <stdio.h>
#include "quicksort.h"
#include "insertsort.h"
#include "invertlist.h"
#include "mergesort.h"

//raft, fast raft. leveldb, rocksdb
int print_vec(const std::vector<int> &data){
  printf("<");
  for(int v : data){
    printf("%d,", v);
  }
  printf(">\n");
}

int print_node(Node* node){
  printf("<");
  while(node != nullptr){
    printf("%d,", node->v);
    node = node->next;
  }
  printf(">\n");
}

Node* init_node_list(int len){
  Node *prev = nullptr;
  Node *head = nullptr;
  for(int i = 0; i < len; i++)
  {
    Node* node = new Node();
    node->v = i;
    node->next=nullptr;
    if (prev){
      prev->next = node;
    }else{
      head = node;
    }
    prev = node;
  }
  
  return head;
}

void testqs(){
  printf("quicksort algo show\n");
  QuickSort qs;
  std::vector<int> data{3,4,1,2,5,4,4,6};
  print_vec(data);
  qs.Run(data);
  print_vec(data);
}

void testis(){
  printf("insertsort algo show\n");
  InsertSort qs;
  std::vector<int> data{3,4,1,2,5};
  print_vec(data);
  qs.Run(data);
  print_vec(data);
}

void testms(){
  printf("mergesort algo show\n");
  MergeSort qs;
  std::vector<int> data{3,4,1,2,5};
  print_vec(data);
  qs.Run(data);
  print_vec(data);
}

void testinvert(){
  printf("invertlist algo show\n");
  InvertList il;
  Node* head = init_node_list(10);
  print_node(head);
  head = il.Run(head);
  print_node(head);
}

int main(){

  printf("welcome to algo show\n");
  testqs();
  testis();
  testms();
  testinvert();

  return 0;
}