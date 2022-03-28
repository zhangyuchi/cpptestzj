#include <vector>
#include <ranges>
#include <iostream>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    auto even = [](int i){ return i%2 == 0; };
    for (int i : vec | std::views::filter(even) | std::views::transform( [](int i) { return i*i; } ) | std::views::take(5))
        std::cout << i << '\n'; // 打印前 5 个偶整数的平方

    return 0;
}