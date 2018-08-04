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
        if (len == 1)
            return;
        if (len == 2){
            if (input[0] > input[1]){
                int tmp = input[0];
                input[0] = input[1];
                input[1] = tmp;
            }
            return;
        }

        int pos;
        partition(input, len, pos);
        if (pos == len){
            return;
        }
            
        sort(input, pos);
        sort(input+pos, len-pos);
        return;
    }

};

#endif //CPPTEST_QUICKSORT_H
