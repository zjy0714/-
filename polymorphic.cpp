#include<iostream>
#include<string>
using namespace std;

//电脑组装:CPU、GPU、ROM

//抽象的CPU类
class CPU
{
public:
    //抽象的计算函数
    virtual void calculate() = 0;
};
//抽象的GPU类
class GPU
{
public:
    //抽象的显示函数
    virtual void display() = 0;
};
//抽象的内存条类
class ROM
{
public:
    //抽象的存储函数
    virtual void storage() = 0;
};
//电脑类
class computer
{
public:
    computer(CPU *cpu,GPU *gpu,ROM *rom)
    {
        m_cpu = cpu;
        m_gpu = gpu;
        m_rom = rom;
    }
    //提供工作的函数
    void work()
    {
        m_cpu->calculate();
        m_gpu->display();
        m_rom->storage();
    }
    ~computer()
    {
        if(m_cpu != NULL)
        {
            delete m_cpu;
            m_cpu = NULL;
        }
                if(m_gpu != NULL)
        {
            delete m_gpu;
            m_gpu = NULL;
        }
                if(m_rom != NULL)
        {
            delete m_rom;
            m_rom = NULL;
        }
    }
private:
    CPU *m_cpu;//CPU的零件指针
    GPU *m_gpu;//GPU的零件指针
    ROM *m_rom;//ROM的零件指针
};
//具体厂商
class IntelCPU : public CPU
{
public:
    void calculate()
    {
        cout << "Intel的CPU工作" << endl;
    }
};
class IntelGPU : public GPU
{
public:
    void display()
    {
        cout << "Intel的GPU工作" << endl;
    }
};
class IntelROM : public ROM
{
public:
    void storage()
    {
        cout << "Intel的ROM工作" << endl;
    }
};
class LenovoCPU : public CPU
{
public:
    void calculate()
    {
        cout << "Lenovo的CPU工作" << endl;
    }
};
class LenovoGPU : public GPU
{
public:
    void display()
    {
        cout << "Lenovo的GPU工作" << endl;
    }
};
class LenovoROM : public ROM
{
public:
    void storage()
    {
        cout << "Lenovo的ROM工作" << endl;
    }
};
void test01()
{
    //第一台电脑零件
    CPU * intelCPU = new IntelCPU;
    GPU * intelGPU = new IntelGPU;
    ROM * intelROM = new IntelROM;
    //创建第一台电脑
    computer * c1 = new computer(intelCPU,intelGPU,intelROM);
    c1->work();
    delete c1;
    c1 = NULL;
}
int main()
{
    test01();
}