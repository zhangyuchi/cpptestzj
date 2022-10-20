#include <iostream>
#include <stdexcept>
#include <string>

void throw_re(const std::string &content, bool flag=true) {
  if (flag)
    throw std::runtime_error(content);
  else
    return;
}

class MyTest_Base {
public:
  virtual ~MyTest_Base() noexcept(true) {
    // std::cout << "开始准备销毁一个MyTest_Base类型的对象"<< std::endl;
    //  注意：在析构函数中抛出了异常
    try {
      throw_re("析构函数中故意抛出一个异常, 测试!",true);
    }
    catch(...){
      std::cout << "MyTest_Base catch ex" << std::endl;
      throw;
    }
  }

  void Func() noexcept(true) { throw_re("Func故意抛出一个异常, 测试!", false); }

  void Other() {}
};

void work() {
  MyTest_Base obj;

  try {
    // 构造一个对象，当obj对象离开这个作用域时析构将会被执行
    obj.Func();
  } catch (std::exception &e) {
    std::cout << "work catch ex:" << e.what() << std::endl;
  } catch (...) {
    std::cout << "work unknow exception" << std::endl;
  }
}

int main() {
  try {
    work();
  } catch (std::exception &e) {
    std::cout << "main catch ex:" << e.what() << std::endl;
  } catch (...) {
    std::cout << "main unknow exception" << std::endl;
  }

  return 0;
}
