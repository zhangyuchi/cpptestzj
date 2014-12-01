#include "widget.hpp"
#include <functional>
#include <string>
#include <vector>
#include <iostream>

struct Widget::Impl {  
  std::string name="zj";
  std::vector<double> data;

  ~Impl(){std::cout<<"~Impl:"<<this<<std::endl;}
};

Widget::Widget()                    // per Item 21, create
  :pImpl(std::make_unique<Impl>())   // std::unique_ptr
{}   

Widget::~Widget() = default; //define of destructor need meet define of impl

Widget::Widget(Widget&& rhs) = default;              // right idea,
Widget& Widget::operator=(Widget&& rhs) = default;   // wrong code!

Widget::Widget(const Widget& rhs)              //need selfdefine, default only shallow copy unique pointer
  : pImpl(std::make_unique<Impl>(*rhs.pImpl)) //will invoke Impl copy ctor
{}

Widget& Widget::operator=(const Widget& rhs)   // copy operator=
{
  *pImpl = *rhs.pImpl;
  return *this;
}

size_t Widget::hash()
{
  return std::hash<std::string>()(pImpl->name);
}
