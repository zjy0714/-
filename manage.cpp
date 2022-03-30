#include<iostream>
#include<string>
#include"m_workers.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

int main()
{
    //实例化管理者对象
    WorkerManager wm;
    int choice = 0; //用户的选择
    while (true)
    {
        //展示成员菜单
        wm.Show_Menu();
        cout << "输入您的选择:  " << endl;
        cin >> choice;
        switch(choice)
        {
            case 0:      //退出系统
                wm.ExitSystem();
                break;
            case 1:      //增加职工
                wm.Add_Emp();
                break;   
            case 2:      //显示职工
                wm.Show_Emp();
                break;   
            case 3:      //删除职工
                wm.Del_Emp();
                break;
            case 4:      //修改职工
                wm.Mod_Emp();
                break;
            case 5:      //查找职工
                wm.Find_Emp();
                break;
            case 6:      //排序职工
                wm.Sort_Emp();
                break;
            case 7:      //清空职工
                wm.Clean_File();
                break;
            default:
                cout << "输入有误,请重新输入" << endl;
                system("pause");
                break;
        }
    }    

    return 0;
}