#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
int main(int argc, char* argv[])
{
    //declare need options
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("person,p", boost::program_options::value<string>()->default_value("world"), "who")
        ;

    boost::program_options::variables_map vm;        
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);    

    if (vm.count("help")) {
        cout << desc;
        return 0;
    }
    cout << "Hello " << vm["person"].as<string>() << endl;
    return 0;
}

