//
// Created by zhangjun on 18-8-3.
//

#ifndef CPPTEST_MERGESORT_H
#define CPPTEST_MERGESORT_H

class MergeSort{
public:
    MergeSort()=default;
    void Run(std::vector<int> &data){
        sort(&data[0], data.size());
    }

private:
    void sort(int* input, int len){
        
    }
};

#endif //CPPTEST_MEGESORT_H
