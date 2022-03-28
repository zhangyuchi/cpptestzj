    #include <type_traits>
    #include <iostream>
    #include <string>

    // template <typename CharT>
    // std::enable_if_t<sizeof(CharT) == 1> create(const CharT * data, size_t size)
    // {
    //     std::cout<<"create for "<<sizeof(CharT)<<std::endl;
    // }

    template <typename CharT>
    std::enable_if_t<sizeof(CharT) == 2> create(const CharT * data, size_t size)
    {
        std::cout<<"create for "<<sizeof(CharT)<<std::endl;
    }

    template <typename CharT, std::enable_if_t<sizeof(CharT) == 1, bool> = true>
    void create(const CharT * data, size_t size)
    {
        std::cout<<"create2 for "<<sizeof(CharT)<<std::endl;
    }

    auto f(auto arg) {
        std::cout<<arg<<std::endl;
        return arg; 
    } 

    int main() {
        char buf[16];
        create(buf, 16);

        int16_t buf1[16];
        create(buf1, 16);

        auto x = f(1); // x 是 int 
        auto s = f(std::string("Hello"));

        return 0;
    }
    