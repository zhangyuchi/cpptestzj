#include <concepts>

struct S{
   int x;
};

template <typename T>
concept haveEqic = requires std::equality_comparable<T>;


template<haveEqic T>
bool do_magic(T a, T b){
    return a == b;
}

int main(){
    //do_magic(S{}, S{}); //Compile time error
    do_magic(56, 46); // Okay int has == and !=
    return 0;
}
