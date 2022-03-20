#include <iostream>
#include <string>
using namespace std;

class myint
{
    friend ostream& operator<<(ostream& cout , myint my);
public:
    myint()
    {
        m_A = 0;
    }
    //前置++
    myint& operator++()
    {
        m_A++;
        return *this;
    }
    //后置++
    myint operator++(int)
    {
        myint temp = *this;
        m_A++;
        return temp;
    }
private:
    int m_A;
};
ostream& operator<<(ostream& cout , myint my)
{
    cout << my.m_A;
    return cout;
}
void test01()
{
    myint A;
    cout << ++A << endl;
    cout << ++(++A) << endl;
}
void test02()
{
    myint A;
    cout << A++ <<endl;
    cout << A << endl;
}
int main()
{
    //test01();
    test02();
}