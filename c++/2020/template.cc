    #include <type_traits>
    #include <iostream>

    template <typename CharT>
    std::enable_if_t<sizeof(CharT) == 1> create(const CharT * data, size_t size)
    {
        std::cout<<"create for "<<sizeof(CharT)<<std::endl;
    }

    template <typename CharT>
    std::enable_if_t<sizeof(CharT) == 2> create(const CharT * data, size_t size)
    {
        std::cout<<"create for "<<sizeof(CharT)<<std::endl;
    }

    int main() {
        char buf[16];
        create(buf, 16);

        int16_t buf1[16];
        create(buf1, 16);

        return 0;
    }
    