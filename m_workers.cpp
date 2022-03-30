#include"m_workers.h"

WorkerManager::WorkerManager()
{
    //文件不存在
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    if(! ifs.is_open())
    {
        //cout << "文件不存在" << endl;
        //初始化属性
        //初始化记录人数
        this->m_EmpNum = 0;
        //初始化数组指针
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return; 
    }
    //文件存在 数据为空
    char ch;
    ifs >> ch;
    if(ifs.eof())
    {
        //cout << "文件为空" << endl;
        //初始化记录人数
        this->m_EmpNum = 0;
        //初始化数组指针
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return; 
    }
    //文件存在,并且记录数据
    int num = this->get_EmpNum();
    //cout << "职工人数为:  " << num <<endl;
    this->m_EmpNum = num;
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    //将文件中的数据存到数组中
    this->init_Emp();
    this->m_FileIsEmpty = false;
}
//保存文件
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME,ios::out);
    //写文件
    for(int i = 0;i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << "  "
            << this->m_EmpArray[i]->m_Name << "  "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
    ofs.close();
}
//统计文件中人数
int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    int id;
    string name;
    int did;
    int num = 0;
    while(ifs >> id && ifs >> name && ifs >> did)
    {
        //统计人数
        num++;
    }
    return num;
}
//展示菜单
void WorkerManager::Show_Menu()
{
    cout << "*********************************" << endl;
    cout << "*******欢迎使用职工管理系统!*******" << endl;
    cout << "********* 0.退出管理程序 *********" << endl;
    cout << "********* 1.增加职工信息 *********" << endl;  
    cout << "********* 2.显示职工信息 *********" << endl;
    cout << "********* 3.删除离职员工 *********" << endl;
    cout << "********* 4.修改职工信息 *********" << endl;
    cout << "********* 5.查找职工信息 *********" << endl;
    cout << "********* 6.按照编号排序 *********" << endl;
    cout << "********* 7.清空所有文档 *********" << endl;
    cout << "*********************************" << endl;
    cout << endl;
}
//退出系统
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
//添加职工
void WorkerManager::Add_Emp()
{
    cout << "请输入添加职工数量:  " << endl;
    int addNum = 0; //要增加的人数
    cin >> addNum;
    if(addNum > 0)
    {
        //计算添加新空间大小
        int newSize = this->m_EmpNum + addNum;
        //开辟新空间
        Worker **newspace = new Worker*[newSize];
        //将原来空间下的数据拷贝到新空间下
        if(this->m_EmpArray != NULL)
        {
            for(int i = 0; i < this->m_EmpNum;i++)
            {
                newspace[i] = this->m_EmpArray[i];
            }
        }
        //批量添加新数据
        for (int i = 0;i < addNum;i++)
        {
            int id;      //职工编号
            string name; //职工姓名
            int dSelect; //部门选择
            cout << "请输入第" << i+1 << " 个新职工编号:  " << endl;
            cin >> id;
            cout << "请输入第" << i+1 << " 个新职工姓名:  " << endl;
            cin >> name;
            cout << "请选择该职工岗位:  " << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;
            Worker * worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id,name,1);
                break;
            case 2:
                worker = new Manager(id,name,2);
                break;
            case 3:
                worker = new Boss(id,name,3);
                break;
            default:
                break;
            }
            //将创建的职工职责,保存到数组中
            newspace[this->m_EmpNum + i]= worker;
        }
        //释放原有空间
        delete[] this->m_EmpArray;
        //更改新空间的指向
        this->m_EmpArray = newspace;
        //更新新的职工人数
        this->m_EmpNum = newSize;
        //数据保存到文件中
        this->save();
        //更新职工不为空
        this->m_FileIsEmpty = false;
        cout << "成功添加" << addNum << " 名职工" << endl;
    }
    else
    {
        cout << "输入数据有误" << endl;
    }
}
//初始化员工
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME,ios::in);
    int id;
    string name;
    int did;
    int index = 0;//初始化数组的下标
    while(ifs >> id && ifs >> name && ifs >> did)
    {
        Worker* worker = NULL;
        if (did == 1)//普通职工
        {
            worker = new Employee(id,name,did);
        }
        else if(did == 2)//经理
        {
            worker = new Manager(id,name,did);
        }
        else//老板
        {
            worker = new Boss(id,name,did);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
    system("puase");
}
//显示职工
void WorkerManager::Show_Emp()
{
    //判断文件是否为空
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        for(int i = 0; i < m_EmpNum;i++)
        {
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
}
//删除职工
void WorkerManager::Del_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入想要删除职工编号" << endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);
        if(index != -1)
        {
            for(int i = index;i < this->m_EmpNum - 1;i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;//更新数组中记录人员个数
            //数据同步更新到文件中
            this->save();
            cout << "删除成功" << endl;
        }
        else
        {
            cout << "删除失败，未找到该职工" << endl;
        }
    }
    system("pause");
}
//判断职工是否存在 如果存在返回职工所在数组中的位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for(int i = 0;i < this->m_EmpNum;i++)
    {
        if(this->m_EmpArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}
//修改职工
void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入要修改职工的编号:  " << endl;
        int id;
        cin >> id;
        int ret = this->IsExist(id);
        if(ret != -1)
        {
            delete this->m_EmpArray[ret];
            int newId = 0;
            string newName = "";
            int dSelect = 0;
            cout << "请输入新职工号" << endl;
            cin >> newId;
            cout << "请输入新姓名" << endl;
            cin >> newName;
            cout << "请输入新岗位" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;
            Worker* worker = NULL;
            switch(dSelect)
            {
                case 1:
                    worker = new Employee(newId,newName,dSelect);
                    break;
                case 2:
                    worker = new Manager(newId,newName,dSelect);
                    break;
                case 3:
                    worker = new Boss(newId,newName,dSelect);
                    break;
                default:
                    cout << "输入数据有误，请重新输入" << endl;
                    break;
            }
            this->m_EmpArray[ret] = worker;
            cout << "修改成功" << endl;
            //保存文件
            this->save();
        }
        else
        {
            cout << "修改失败，查无此人" << endl;
        }
    }
    system("pause");
}
//查找职工
void WorkerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入查找的方式:  " << endl;
        cout << "1、按照职工编号查找" << endl;
        cout << "2、按照职工姓名查找" << endl;
        int select = 0;
        cin >> select;
        if(select == 1)
        {
            int id = 0;
            cout << "请输入查找职工的编号:  " << endl;
            cin >> id;
            int ret = IsExist(id);
            if(ret != -1)
            {
                cout << "查找成功,该职工信息如下:  " << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "查无此人" << endl;
            }
        }
        else if(select == 2)
        {
            string name;
            cout << "请输入查找的姓名:  " << endl;
            cin >> name;
            //加入判断是否查到的标志
            bool flag = false; //默认未找到职工
            for (int i = 0;i < m_EmpNum; i++)
            {
                if(this->m_EmpArray[i]->m_Name == name)
                {
                    cout << "职工编号为:  " << this->m_EmpArray[i]->m_Id << "号职工信息如下: "
                         << endl;
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if(flag == false)
            {
                cout << "查无此人" << endl;
            }
        }
        else
        {
            cout << "输入信息有误" << endl;
        }
    }
    system("puase");
}
//排序职工
void WorkerManager::Sort_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
        system("pause");
    }
    else
    {
        cout << "请选择排序的方式" << endl;
        cout << "1、按职工号进行升序排列" << endl;
        cout << "2、按职工号进行降序排列" << endl;
        int select = 0;
        cin >> select;
        for(int i = 0; i < m_EmpNum;i++)
        {
            int minOrmax = i;//声明最小值最大值下标
            for(int j = i + 1;j < this->m_EmpNum;j++)
            {
                if(select == 1)//升序
                {
                    if(this->m_EmpArray[minOrmax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        minOrmax = j;
                    }
                }
                else if(select == 2)//降序
                {
                    if(this->m_EmpArray[minOrmax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        minOrmax = j;
                    }
                }
                else
                {
                    cout << "输入数据有误,请重新输入" << endl;
                    break;
                }
            }
            if(i != minOrmax)
            {
                Worker* temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrmax];
                this->m_EmpArray[minOrmax] = temp;
            }
            
        }
        cout << "排序成功,排序后的结果为:  " <<endl;
        this->Show_Emp();//展示排序后的结果
    } 
}
//清空文件
void WorkerManager::Clean_File()
{
    cout << "是否确认清空" << endl;
    cout << "1、确定" << endl;
    cout << "2、返回" << endl;
    int select = 0;
    cin >> select;
    if(select == 1)
    {
        ofstream ofs(FILENAME,ios::trunc); //删除文件后创建
        ofs.close();
        if(this->m_EmpArray != NULL)
        {
            for(int i = 0; i < this->m_EmpNum;i++)
            {
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "清空成功" << endl;
    }
    else
    {
        return;
    }
    system("pause"); 
}
//析构函数
WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        for(int i = 0;i < this->m_EmpNum;i++)
        {
            delete this->m_EmpArray[i];
            this->m_EmpArray[i] = NULL;
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}