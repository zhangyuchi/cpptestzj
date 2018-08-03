//
// Created by zhangjun on 18-8-3.
//

#ifndef CPPTEST_QUICKSORT_H
#define CPPTEST_QUICKSORT_H

#include <vector>

class QuickSort{
public:
    QuickSort()= default;
    void Run(std::vector<int> &data){
        sort(&data[0], data.size());
    }

private:
    void partition(int *input, int len, int& pos){

    }

    void sort(int* input, int len){
      int pos;
      partition(input, len, pos);
      if (pos == len - 1){
        return;
      }else{
        
      }
    }

};

#endif //CPPTEST_QUICKSORT_H
