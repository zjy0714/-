#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void test01()
{
    ofstream ofs;
    ofs.open("demand.txt",ios::out);
    ofs << "公司中分为三类:普通员工、经理、老板,显示信息时需要显示职工编号、职工姓名职工岗位以及职责" <<endl;
    ofs << "普通员工职责:完成经理交给的任务" << endl;
    ofs << "经理职责:完成老板下发的任务,并下发任务给员工" << endl;
    ofs << "老板职责:完成公司所有事务" << endl;
    ofs << "--------------------------------------------------------" << endl;
    ofs << "管理系统要实现的功能如下:" << endl;
    ofs << "退出管理程序:退出当前管理系统" << endl;
    ofs << "显示职工信息:实现批量添加职工功能,将信息收录到文件中,职工信息为:职工编号、姓名、部门编号" << endl;
    ofs << "显示职工信息:显示公司内部所有职工的信息" << endl;
    ofs << "删除离职职工:按照编号删除指定的职工" << endl;
    ofs << "修改职工信息:按照编号修改职工信息" << endl;
    ofs << "查找职工信息:按照职工的编号或者姓名进行查找" << endl;
    ofs << "按照编号排序:按照职工编号进行排序,排序规则由用户指定" << endl;
    ofs << "清空所有文档:清空文件中记录的所有职工信息(清空前需要确认)" << endl;
    ofs.close();
}
int main()
{
    test01();
}