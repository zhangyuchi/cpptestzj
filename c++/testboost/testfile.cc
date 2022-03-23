/*
 * =============================================================================
 *
 *       Filename:  testfile.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012年09月14日 17时36分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangjun (zhangyuchi), zhangyuchi@gmail.com
 *        Company:  Qihoo inc.
 *
 * =============================================================================
 */
#include <time.h>
#include <boost/date_time.hpp>
#define BOOST_DATE_TIME_SOURCE
#include <iostream>
#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <sstream>

#include <stdio.h>

using namespace std;
using namespace boost::filesystem;
using namespace boost::posix_time;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: tut1 path\n";
        return 1;
    }
    //std::cout << argv[1] << " " << file_size(argv[1]) << '\n';

    std::string pathname(argv[1]);

    path p(pathname);
    create_directory(p);    

    std::cout<<"last modification time:"<<last_write_time(p)<<std::endl;

    ptime now = second_clock::local_time();

    std::cout<<now.time_of_day().seconds()<<std::endl;

    /*
    boost::local_time::local_time_facet* output_facet = new boost::local_time::local_time_facet();
    output_facet->format(boost::local_time::local_time_facet::iso_time_format_extended_specifier);

    boost::local_time::local_date_time ldt(boost::local_time::second_clock::local_time());

    stringstream ss;
    ss.str("");
    ss << ldt;
    cout << ss.str() << endl; // "2004-02-29 12:34:56.000789-05:00"
    */
/*
    std::string strTime = boost::posix_time::to_iso_string( second_clock::local_time() );
    std::cout<<strTime<<std::endl;
    int pos = strTime.find('T');
    strTime.replace(pos,1,std::string(" "));
    strTime.replace(pos + 3,0,std::string(":"));
    strTime.replace(pos + 6,0,std::string(":"));
    std::cout << strTime << std::endl;
*/
    time_facet *facet = new time_facet("%Y-%m-%d %H:%M:%S");
    stringstream ss;
    ss.imbue(locale(ss.getloc(), facet));
    ss << second_clock::local_time() << endl;
    string filename;
    ss>>filename;
    ss>>filename;

    
    std::string file = p.string() + "/" + filename + ".txt";
    std::ofstream out;
    out.close();
    out.open(file.c_str());

    out.imbue(locale(out.getloc(), facet));
    out<<second_clock::local_time()<<","<<2<<"\n";
    out.close();
   
    if ( exists(path(file)) )
        rename(path(file), path(file+".bak") );
    return 0;
}
