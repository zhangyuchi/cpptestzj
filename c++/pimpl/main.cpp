#include "widget.hpp"
#include <iostream>

using namespace std;

int main()
{
  Widget w;
  cout<<w.hash()<<endl;

  Widget h(w);
  cout<<h.hash()<<endl;

  return 0;
}

