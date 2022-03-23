#include <boost/intrusive/list.hpp>
#include <string>
#include <utility>
#include <iostream>
#include <memory>

using namespace boost::intrusive;

typedef link_mode<auto_unlink> mode;

struct animal : public list_base_hook<mode>
{
  std::string name;
  int legs;
  animal(std::string n, int l) : name{std::move(n)}, legs{l} {}
  ~animal(){ std::cout<<"~animal name:"<<name<<"address:"<<this<<std::endl;}
};

int main()
{
  animal a1{"cat", 4};
  animal a2{"shark", 0};
  animal *a3 = new animal{"spider", 8};
  std::shared_ptr<animal> a4 = std::shared_ptr<animal>(new animal{"maque", 7});
  animal a5{"dog", 2};

  typedef constant_time_size<false> constant_time_size;
  typedef list<animal, constant_time_size> animal_list;
  animal_list animals;
  animal_list birds;


  a1.unlink();
  animals.push_back(a1);
  animals.push_back(a2);
  animals.push_back(*a3);
  animals.push_back(*a4);
  animals.push_back(a5);

  auto printAnimal = [&](){
    for (const animal &a : animals)
      std::cout << a.name << '\n';
    std::cout<<std::endl;
  };

  printAnimal();
  animal_list::iterator it = animals.begin();
  //a4->unlink();
  while ( it!=animals.end() )
  {
    if( it->name == "maque" )
    {
      animal_list::iterator tempit=it;
      std::shared_ptr<animal> a41(&*tempit);
      std::cout<<"a41 == a4?"<<(a41==a4)<<std::endl;
      //animals.erase(tempit); tempit have been invalid
      ++it;
      continue;
    }   


    if( it->name == "cat" )
    {
      animal_list::iterator tempit=it;
      ++it;
      animals.erase(tempit);
      continue;
    }

    ++it;
  }

  //std::cout<<"iter end"<<std::endl;
  printAnimal();

  birds.push_back(*a4);

  for (const animal &b : birds)
    std::cout << b.name << '\n';

  delete a3;
}

