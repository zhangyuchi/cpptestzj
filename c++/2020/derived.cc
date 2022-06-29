#include <iostream>
#include <string>

using namespace std;

class Man
{
public:
    // virtual string getName() const
    // {
    //     return "man";
    // }

    virtual string getName(bool flag=true) const
    {
        if (flag)
        {
            return "true man";
        }
        return "man";
    }
};

class Boy : public Man {
public:
    virtual string getName() const override
    {
        return "boy";
    }
};

class Tom final : public Boy {
public:
    virtual string getName(bool flag) const override
    {
        if (flag)
        {
            return "true tom";
        }
        return "tom";
    }
};

int main() {
    Man * boy = new Boy();
    cout<<boy->getName(true)<<endl;

    //static_cast<Boy *>(boy)->getName(true);

    return 0;
}