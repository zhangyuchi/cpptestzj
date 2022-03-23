#include <boost/signals2.hpp>
#include <memory>
#include <functional>
#include <iostream>

using namespace boost::signals2;

struct world
{   
    void hello() const
    {
         std::cout << "Hello, world!\n";
     }
};

void crash()
{    
    signal<void()> s;   
    {
        std::unique_ptr<world> w(new world());
        s.connect(std::bind(&world::hello, w.get()));
    }
    
    std::cout << s.num_slots() << '\n';
    s();
}

int main()
{
    signal<void()> s;
    {
        boost::shared_ptr<world> w(new world());
        s.connect(signal<void()>::slot_type(&world::hello, w.get()).track(w));
    }
    
    std::cout << s.num_slots() << '\n';
    s();
}

