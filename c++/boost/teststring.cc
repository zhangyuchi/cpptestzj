#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>
using namespace std;
using namespace boost;

int main()
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

	return 0;
}
