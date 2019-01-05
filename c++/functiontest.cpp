// ConsoleApplication11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>

#include <functional>
#include <vector>
#include <string>

struct A {
    A(std::string const &s) : s(s) {}

    A() {}

    A operator*(A const &other) const { return A("shit" + s + other.s); }

    A operator+(A const &other) const { return A("fuck" + s + other.s); }

    A operator*(A const &&other) const { return A("haha" + s + other.s); }

    A operator+(A const &&other) const { return A("ehhh" + s + other.s); }

    A(const A &obj) {
        s = obj.s;
    }

    A(A&& obj) noexcept:
            s(std::move(obj.s))       // 类类型成员的显式移动
    {}

    A& operator=(const A &obj )
    {
        if (this != &obj) {
            s = obj.s;
        }
        return *this;
    }

    A& operator=(A&& obj) noexcept {
        if (this != &obj) {
            s = std::move(obj.s);
        }
        return *this;
    }

    std::string s;
};

typedef std::function<A(size_t)> GetA1;
typedef std::function<A const &(size_t)> GetA2;

struct B {
    int xxx;
    A a;
};

A InnerProduct(A const *a, A const *b, size_t n) {
    A ret;
    for (size_t i = 0; i < n; ++i) {
        ret = ret + a[i] * b[i];
    }
    return ret;
}

// NOTE: get_a copy A
A InnerProduct(GetA1 const &get_a, GetA1 const &get_b, size_t n) {
    A ret;
    for (size_t i = 0; i < n; ++i) {
        ret = ret + get_a(i) * get_b(i);
    }
    return ret;
}

A InnerProduct2(GetA2 const &get_a, GetA2 const &get_b, size_t n) {
    A ret;
    for (size_t i = 0; i < n; ++i) {
        ret = ret + get_a(i) * get_b(i);
    }
    return ret;
}

template <class Func>
A InnerProduct3(Func const &get_a, Func const &get_b, size_t n) {
    A ret;
    for (size_t i = 0; i < n; ++i) {
        ret = ret + get_a(i) * get_b(i);
    }
    return ret;
}

A test1() {
    std::vector<A> a(100);
    for (auto &i : a) {
        i = A(std::to_string(rand()));
    }

    std::vector<A> b(100);
    for (auto &i : b) {
        i = A(std::to_string(rand()));
    }

    return InnerProduct(a.data(), b.data(), a.size());
}

A test2() {
    std::vector<B> a(100);
    std::vector<B> b(100);
    auto get_a = [&a](size_t i) -> A const & { return a[i].a; };
    auto get_b = [&b](size_t i) -> A const & { return b[i].a; };
    return InnerProduct3<GetA2>(get_a, get_b, a.size());
}

A test3() {
    std::vector<B> a(100);
    std::vector<B> b(100);

    auto get_a = [&a](size_t i)  { return a[i].a + A("abc"); };
    auto get_b = [&b](size_t i)  { return b[i].a + A("123"); };
    return InnerProduct3<GetA1>(get_a, get_b, a.size());
}

int main() {
    test1();
    test2();
    test3();

    return 0;
}