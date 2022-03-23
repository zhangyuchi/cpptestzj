#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

using namespace std;

struct Value
{
    Value(int v):v_(v)
    {
        cout<<"Value:"<<v<<endl;
    }

    ~Value()
    {
        cout<<"~Value:"<<v_<<endl;
    }
    
    int v_;
};


int main()
{   
    {        
        cout<<"in"<<endl;    
        boost::ptr_vector<Value> v;
        v.push_back(new Value{1});
        v.push_back(new Value{2});
    }
    cout<<"out"<<endl;
    
    return 0;    
}
