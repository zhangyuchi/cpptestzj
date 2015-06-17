#include <boost/property_tree/ptree.hpp>
#include <iostream>

using boost::property_tree::ptree;
using namespace std;

void base()
{
    
    ptree pt;    
    pt.put("C:.Windows.System", "20 files");
    
    ptree &c = pt.get_child("C:");  
    ptree &windows = c.get_child("Windows");    
    ptree &system = windows.get_child("System");
    
    std::cout <<"C:"<< c.get_value<std::string>().size() << '\n';
    std::cout <<"Windows:"<< windows.get_value<std::string>() << '\n';
    std::cout <<"system:"<< system.get_value<std::string>() << '\n';
    
}


void iter()
{        
    typedef boost::property_tree::basic_ptree<std::string, int> ptree;      
    ptree pt;
        
    pt.put(ptree::path_type{"C:\\Windows\\System", '\\'}, 20);        
    pt.put(ptree::path_type{"C:\\Windows\\Cursors", '\\'}, 50);
        
    ptree &windows = pt.get_child(ptree::path_type{"C:\\Windows", '\\'});
    int files = 0;
        
    for (const std::pair<std::string, ptree> &p : windows)
    {   
        cout<<p.first<<endl;
        files += p.second.get_value<int>();
    }
    
    
    std::cout << files << '\n';
}

int main()
{
    iter();

    return 0;
}

