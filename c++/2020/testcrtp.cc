#include <iostream>

template<typename Method>
class Strategy
{
public:
	void DoTask()
	{
		static_cast<Method*>(this)->DoTask();
	}
};

class Method1	: public Strategy<Method1>
{
public:
	Method1() {
		id_ = 1;
	}
	void DoTask()
	{
		std::cout << "This is Method1, id:"<< id_ << std::endl;
	}
private:
	int id_=0;
};

class Method2	:	public Strategy<Method2>
{
public:
	Method2() {
    id_ = 2;
  }

	void DoTask()
	{
		std::cout << "This is Method2, id:"<< id_ << std::endl;
	}

private:
	int id_=0;
};

int main()
{
	Strategy<Method1> method;
	std::cout << "size of method = " << sizeof(method) << std::endl;
	method.DoTask();
}

