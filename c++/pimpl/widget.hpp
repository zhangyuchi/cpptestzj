#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <memory>

class Widget
{
  public:
    Widget();
    ~Widget();

    Widget(Widget&& rhs);              // right idea,
    Widget& operator=(Widget&& rhs);   // wrong code!
    
    Widget(const Widget& rhs);              // declarations
    Widget& operator=(const Widget& rhs);   // only
    
    size_t hash();

  private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;  
};

#endif

