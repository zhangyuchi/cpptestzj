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
    //pos is first big than input[0]
    void partition(int *input, int len, int& pos){
        int start=1;
        int end=len-1; 
        while (true)
        {
            while ( start<=len-1 && input[start] <= input[0])
                ++start;
            while ( end > 0 && input[end] > input[0] )
                --end;
            
            if (end < start){
                for (int i=1; i<end; ++i){
                    if(input[i]<input[0]){
                        int tmp = input[i];
                        input[i] = input[0];
                        input[0] = tmp;
                    }
                }
                pos = start;
                break;
            }

            int tmp = input[start];
            input[start] = input[end];
            input[end] = tmp;
        }        
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
