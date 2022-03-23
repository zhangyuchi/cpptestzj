#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
         
using boost::tie;
using boost::tuple;

typedef boost::iostreams::stream<boost::iostreams::file_sink> ofstream;

tuple<int,int,int> get_tuple()
{
    return boost::make_tuple(1,2,3);
}

int main()
{
    ofstream out("HeavyArtillery.txt"); // Wilfred Owen
    out << "Reach at that Arrogance which needs thy harm,\n"
           "And beat it down before its sins grow worse.\n";

	out <<get_tuple()<<"\n";	

    out.close();
	return 0;
}
