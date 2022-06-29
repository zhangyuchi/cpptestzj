#include <iostream>

template <typename Method>
class Strategy
{
public:
	void DoTask()
	{
		static_cast<Method *>(this)->DoTask();
	}
};

class Method1 : public Strategy<Method1>
{
public:
	Method1()
	{
		id_ = 1;
	}
	
	void DoTask()
	{
		std::cout << "This is Method1, id:" << id_ << std::endl;
	}

private:
	int id_ = 0;
};

class Method2 : public Strategy<Method2>
{
public:
	Method2()
	{
		id_ = 2;
	}

	void DoTask()
	{
		std::cout << "This is Method2, id:" << id_ << std::endl;
	}

private:
	int id_ = 0;
};

/*---------------------------------------------------------------------------------*/

template <typename Method>
class Task : public Method
{
public:
	double data{0.0};

public:
public:
	void DoTask()
	{
		Method::DoTask();
	}
};

/*---------------------------------------------------------------------------------*/

struct Kevin
{
	using size_type = unsigned int;
};

template<typename T,int N>
std::size_t Len(T(&)[N])
{
	return N;
}

template<typename T>
decltype(T().size(),typename T::size_type()) Len(const T& t)
{
	return t.size();
}

unsigned int Len(...)
{
	return 0;
}

int main()
{
	Task<Method1> method;
	std::cout << "size of method = " << sizeof(method) << std::endl;
	method.DoTask();

	std::cout << "kerin len:" << Len(Kevin()) << std::endl;
}

