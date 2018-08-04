//
// Created by zhangjun on 18-8-3.
//

#ifndef CPPTEST_INSERTSORT_H
#define CPPTEST_INSERTSORT_H

class InsertSort{
public:
    InsertSort()=default;
    void Run(std::vector<int> &data){
        sort(&data[0], data.size());
    }

private:
    void sort(int* input, int len){
        
    }
};

#endif //CPPTEST_INSERTSORT_H
