#include<concepts>

struct S{
   int x;
};

template<class T>
requires std::equality_comparable<T>
bool do_magic(T a, T b){
    return a == b;
}

int main(){
    //do_magic(S{}, S{}); //Compile time error
    do_magic(56, 46); // Okay int has == and !=
    return 0;
}
