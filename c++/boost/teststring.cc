#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>

using namespace std;
using namespace boost;

void testreplace()
{
    char text[]="hello dolly!";
    iterator_range<char*> result=find_last(text,"ll");

    transform( result.begin(), result.end(), result.begin(), bind2nd(plus<char>(), 1) );

    cout<<text<<endl;
    // text = "hello dommy!"            

    to_upper(result); // text == "hello doMMy!"

    cout<<text<<endl;
    // iterator_range is convertible to bool
    if(find_first(text, "dolly"))
    {
        cout << "Dolly is there" << endl;
    }
}

struct FilterItem
{
    string key;
    string cond;
    string value;
};

bool parse_filter_item(const std::string&filter, FilterItem& item)
{
    bool ret = true;

    std::vector<std::string> split_vec;
    boost::algorithm::split_regex( split_vec, filter, boost::regex( "[><=]+=" ) );

    std::cout<<filter<<": "<<split_vec.size()<<std::endl;

    if ( split_vec.size() < 2)
        return false;

    if(find_first(filter, "=="))
    {
        item.key = split_vec[0];
        item.cond = "==";
        item.value = split_vec[1];
    }
    else if(find_first(filter, ">="))
    {
        item.key = split_vec[0];
        item.cond = ">=";
        item.value = split_vec[1];
    }
    else if(find_first(filter, "<="))
    {
        item.key = split_vec[0];
        item.cond = "<=";
        item.value = split_vec[1];
    }

    else if(find_first(filter, "<>"))
    {
        item.key = split_vec[0];
        item.cond = "<>";
        item.value = split_vec[1];
    }
    else
    {
        ret = false;
    }

    return ret;
}

void testfilter( string filter, vector<FilterItem>& filter_items, string& linkoper )
{
    std::vector<std::string> split_vec;
    split( split_vec, filter, boost::is_any_of("&|") );

    size_t split_size = split_vec.size();
    for( size_t i=0; i<split_size; ++i)
    {
        cout<<split_vec[i]<<endl;
        FilterItem item;
        if ( parse_filter_item( split_vec[i], item ) )
            filter_items.push_back(item);
    }

    if(find_first(filter, "|"))
    {
        linkoper = "or";
    }
    else if(find_first(filter, "&"))
    {
        linkoper = "and";
    }
    else
    {
        linkoper = "null";
    }

    /*
    iterator_range<string::iterator> ret = find_first(filter, "&");
    if ( ret.begin() != ret.end() )
        linkoper.assign(ret.begin(), ret.end());
    */
}

int main()
{
    string filter1 = "time<=123456789";
    string filter2 = "time>=987654321&tag==sex";
    string filter3 = "tag==sport|tag==sex";

    vector<FilterItem> fiv;
    string linkoper;

    testfilter(filter1, fiv, linkoper);    
    cout<<"result: "<<linkoper<<" "<<fiv.size()<<endl;

    fiv.clear();    
    testfilter(filter2, fiv, linkoper);
    cout<<"result: "<<linkoper<<" "<<fiv.size()<<endl;

    fiv.clear();
    testfilter(filter3, fiv, linkoper);
    cout<<"result: "<<linkoper<<" "<<fiv.size()<<endl;

    return 0;
}

