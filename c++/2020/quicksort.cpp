#include <iostream>

namespace quicksort
{

template <typename T, T Value>
struct scalar
{
    using type = scalar<T, Value>;
    using value_type = T;

    static constexpr T value = Value;
};

template <typename Head, typename Tail>
struct list
{
    using type = list<Head, Tail>;
    using head = Head;
    using tail = Tail;
};

template <typename List, typename Pred>
struct filter;

template <typename List1, typename List2>
struct concat_list;

namespace detail
{

template <typename List, typename Pred, bool PredResult>
struct filter_impl;

template <typename List, typename Pred>
struct filter_impl<List, Pred, true>
{
    using result = list<
        typename List::head,
        typename filter<typename List::tail, Pred>::result>;
};

template <typename List, typename Pred>
struct filter_impl<List, Pred, false>
{
    using result = typename filter<typename List::tail, Pred>::result;
};

template <typename List1Cur, typename List1Tail, typename List2>
struct concat_list_impl
{
    using result = list<
        List1Cur,
        typename concat_list<List1Tail, List2>::result>;
};

} // namespace detail

template <typename List, typename Pred>
struct filter
{
    using result = typename detail::filter_impl<
        List, Pred, Pred::template invoke<typename List::head>::value>::result;
};

template <typename Pred>
struct filter<void, Pred>
{
    using result = void;
};

template <bool Greater, typename T, T CompareValue>
struct scalar_compare;

template <typename T, T CompareValue>
struct scalar_compare<true, T, CompareValue>
{
    template <typename Value>
    struct invoke
    {
        static constexpr bool value = Value::value > CompareValue;
    };
};

template <typename T, T CompareValue>
struct scalar_compare<false, T, CompareValue>
{
    template <typename Value>
    struct invoke
    {
        static constexpr bool value = Value::value <= CompareValue;
    };
};

template <typename List1, typename List2>
struct concat_list
{
    using result = typename detail::concat_list_impl<
        typename List1::head, typename List1::tail, List2>::result;
};

template <typename List2>
struct concat_list<void, List2>
{
    using result = List2;
};

template <typename T, typename List>
struct quick_sort
{
private:
    static constexpr auto pivot = List::head::value;
    using left_partition = typename filter<
        typename List::tail, scalar_compare<false, T, pivot>>::result;
    using right_partition = typename filter<
        typename List::tail, scalar_compare<true, T, pivot>>::result;

public:
    using result = typename concat_list<
        typename quick_sort<T, left_partition>::result,
        typename concat_list<
            list<scalar<int, pivot>, void>,
            typename quick_sort<T, right_partition>::result>::result>::result;
};

template <typename T>
struct quick_sort<T, void>
{
    using result = void;
};

template <typename List>
inline void print()
{
    std::cout << List::head::value << " ";
    print<typename List::tail>();
}

template <>
inline void print<void>()
{
    std::cout << std::endl;
}

void main()
{
#define LST(x, n) list<scalar<int, x>, n>
    using input = LST(7, LST(4, LST(2, LST(1, LST(8, LST(9, LST(3, LST(6, LST(5, void)))))))));
#undef LST

    print<quick_sort<int, input>::result>();
}
} // namespace quicksort

int main()
{
    quicksort::main();
    return 0;
}
