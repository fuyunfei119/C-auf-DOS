#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "workmanager.h"
#include "Worker.h"
#include "Emperyee.h"
#include "Manager.h"
#include "Boss.h"


//在头文件里定义类，在源文件类外定义具体函数
Workmanger::Workmanger() {
	//在构造函数里初始化成员属性
	number_of_workers;
	arrays_of_workers;
	//1.如果文件不存在
	ifstream ifs;
	ifs.open(FILE, ios::in);

	if (!ifs.is_open())
	{
		//如果文件不存在，初始化属性
		cout << "文件不存在" << endl;
		this->number_of_workers = 0;
		this->arrays_of_workers = NULL;
		this->Fileisempty = true;
		ifs.close();
		return;
	}

	//2.文件存在，但没有数据
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件存在，没有数据" << endl;
		this->number_of_workers = 0;
		this->arrays_of_workers = NULL;
		this->Fileisempty = true;
		ifs.close();
		return;
	}

	//3.文件存在，有数据存在
	int num = this->get_number_of_workers_in_books();
	cout << "一共有"<<num<<"个人存在" << endl;
	this->number_of_workers = num;

	//给数组开辟空间
	this->arrays_of_workers = new Worker*[this->number_of_workers];

	//调用initialize函数给成员初始化，把存在的数据传入数组中
	this->initialize();

	/*for (int i = 0; i < number_of_workers; i++)
	{
		cout << "职工的编号是： " << this->arrays_of_workers[i]->id << "\t名字是： " << this->arrays_of_workers[i]->name << "\t职位是： " << this->arrays_of_workers[i]->Depertment_id << endl;
	}*/
	
}

//显示主菜单
void Workmanger::showmenu() {

	cout << "****************************************" << endl;
	cout << "********** Herzlichen Willkommen *********" << endl;
	cout << "************ 0.Exit   System       ************" << endl;
	cout << "************ 1.Add    Emperyee   ************" << endl;
	cout << "************ 2.Show   Emperyee   ************" << endl;
	cout << "************ 3.Delete Emperyee   ************" << endl;
	cout << "************ 4.Modify Emperyee   ************" << endl;
	cout << "************ 5.Find   Emperyee   ************" << endl;
	cout << "************ 6.Sort   Emperyee   ************" << endl;
	cout << "************ 7.Clean  Emperyee   ************" << endl;
	cout << "****************************************" << endl;
	cout << endl;

}

//退出系统
void Workmanger::Exitsystem() {
	
	cout << "欢迎再次使用，再见" << endl;
	system("pause");
	//退出函数
	exit(1);
};

//添加员工功能
void Workmanger::Add_works_to_system() {

	cout << "请输入要添加的人数" << endl;

	int Number_of_workers_to_add = 0;
	cin >> Number_of_workers_to_add;

	if (Number_of_workers_to_add > 0)
	{
		//实现添加

		//由于不断的添加，所以需要不断的开辟新的内存空间
		int newSize = this->number_of_workers + Number_of_workers_to_add; //新空间大小 = 原来的成员数量 + 新添加的成员数量

		//根据新空间大小开辟新空间
		Worker** newSpace = new Worker* [newSize];//开辟一片员工父类指针类型的数组，来赋给父类指针类型的指针newspace来存储父类指针类型的数组

		//如果原来在数组中有数据，就要把原来的数据拷贝到新空间下
		if (arrays_of_workers != NULL)
		{
			for (unsigned int i = 0; i < this->number_of_workers; i++)
			{
				newSpace[i] = arrays_of_workers[i];
			}
		}

		//原来数据拷贝完之后，在创建要添加的新成员
		for (int i = 0; i < Number_of_workers_to_add; i++)
		{
			int enter_id;
			string enter_name;
			int position_of_workers;

			cout << "请输入第"<< i + 1 <<"个成员的id" << endl;
			cin >> enter_id;

			cout << "请输入第" << i + 1 << "个成员的姓名" << endl;
			cin >> enter_name;

			cout << "请选择员工岗位" << endl;
			cout << "\t1.普通员工" << endl;
			cout << "\t2.经理" << endl;
			cout << "\t3.老板" << endl;
			cin >> position_of_workers;

			Worker* worker = NULL;//创建需要的父类指针类型的指针
			switch (position_of_workers)
			{
			case 1:
				worker = new Emperyee(enter_id,enter_name,1);//在堆区开辟子类对象空间指向父类指针
				break;
			case 2:
				worker = new Manager(enter_id, enter_name, 2);
				break;
			case 3:
				worker = new Boss(enter_id, enter_name, 3);
				break;
			default:
				break;
			}

			//将创建好的成员传入到数组中
			newSpace[this->number_of_workers + i] = worker; //把指向子类对象的父类指针添加到原有成员之后
		}

		//释放原有空间的内存
		delete[] this->arrays_of_workers; //这里原本是释放父类指针--worker，但是这是一个数组,所以释放数组名 | 由于原来已经存在的成员已经拷贝到newSpace去了，所以在数组里就不需要了，可以删除。

		//更改新空间指向
		this->arrays_of_workers = newSpace; //由于原来已经存在的成员已经拷贝到newSpace去了，所以直接把新空间里的数据赋给员工数组就可以了

		//更新员工人数
		number_of_workers = newSize;

		//更新文件不为空
		Fileisempty = false;

		//提示添加成功
		cout << "成功添加了" << Number_of_workers_to_add <<"员工"<< endl;

		//调用保存数据函数
		this->save();

	}
	else {
		cout << "输入的人数有误" << endl;
	}

	system("pause");
}

//保存文件功能
void Workmanger::save()
{
	ofstream ofs;
	ofs.open(FILE,ios::out);

	for (unsigned int i = 0; i < this->number_of_workers; i++)
	{
		ofs << this->arrays_of_workers[i]->id<<" "
			<<  this->arrays_of_workers[i]->name <<" "
			<< this->arrays_of_workers[i]->Depertment_id 
			<< endl;
	}

	ofs.close();
}

//统计文件的人数
int Workmanger::get_number_of_workers_in_books() {

	ifstream ifs;
	ifs.open(FILE, ios::in);

	int id;
	string name;
	string Depertment_id;

	int num = 0;
	char buf[1024] = {};
	while (ifs.getline(buf,sizeof(buf)))
	{
		num++;
	}

	return num;
};

//初始化员工
void Workmanger:: initialize() {
	ifstream ifs;
	ifs.open(FILE, ios::in);

	int id;
	string name;
	int Depertment_id;

	int index = 0;

	while (ifs>>id&&ifs>>name&&ifs>>Depertment_id)
	{
		Worker* worker = NULL;
		if (Depertment_id == 1)
		{
			worker = new Emperyee(id, name, Depertment_id);
		}
		else if(Depertment_id == 2)
		{
			worker = new Manager(id, name, Depertment_id);
		}
		else if (Depertment_id == 3)
		{
			worker = new Boss(id, name, Depertment_id);
		}
		this->arrays_of_workers[index] = worker;
		index++;
	}

	ifs.close();
};


//显示所以员工功能
void Workmanger::show_all_Details() {
	if (this->Fileisempty)
	{
		cout << "文件为空，没有成员信息" << endl;
	}
	else {

		for (int i = 0; i < this->number_of_workers; i++)
		{
			this->arrays_of_workers[i]->showalldetails(); 
		}
	}
	system("pause");
};

//判断员工是否存在
int Workmanger:: the_worker_is_exsit(int enter_id) {
	
	int index = -1;

	for (int i = 0; i < this->number_of_workers; i++)
	{
		if (this->arrays_of_workers[i]->id==enter_id) {
			index = i;
			break;
		}
	}

	return index;
};

//删除员工功能
void Workmanger::delete_singel_worker() {
	
	//首先判断文件存不存在
	if (Fileisempty)
	{
		cout << "没有数据可以删除" << endl;
	}
	else {

		//删除员工
		cout << "请输入想要删除的员工标号" << endl;
		int enter_id = 0;
		cin >> enter_id;

		//用寻找员工函数找出该员工的数组下标
		int index_of_worker = this->the_worker_is_exsit(enter_id);

		if (index_of_worker != -1)
		{
			for (int i = index_of_worker; i < this->number_of_workers - 1; i++) {

				this->arrays_of_workers[i] = this->arrays_of_workers[i + 1];
			}

			//人数总数剪去；
			this->number_of_workers--;

			//更新输出
			this->save();

			cout << "删除员工成功" << endl;
		}
		else
		{
			cout << "删除失败，没有找到该员工" << endl;
		}


	}
	system("pause");
};

//修改成员数据功能
void Workmanger::modify_the_information_of_worker() {

	if (this->Fileisempty)
	{
		cout << "没有成员可供删除" << endl;
	}
	else
	{
		cout << "请输入要修改人的编号" << endl;
		int enter_id = 0;
		cin >> enter_id;

		int the_index_of_worker = the_worker_is_exsit(enter_id);
		if (the_index_of_worker != -1)
		{
			delete this->arrays_of_workers[the_index_of_worker];

			int new_id = 0;
			string new_name = "";
			int new_Depertment_id = 0;

			cout << "查找到" << enter_id << "号的员工" << "请输入新的编号" << endl;
			cin >> new_id;

			cout<<"请输入新的姓名" << endl;
			cin >> new_name;

			cout << "请输入新的岗位" << endl;
			cout << "\t1.普通员工" << endl;
			cout << "\t2.经理" << endl;
			cout << "\t3.老板" << endl;

			int button_of_select = 0;
			cin >> button_of_select;

			Worker* worker = NULL;
			switch (button_of_select)
			{
			case 1:
				worker = new Emperyee(new_id, new_name, new_Depertment_id);
				break;
			case 2:
				worker = new Manager(new_id, new_name, new_Depertment_id);
				break;
			case 3:
				worker = new Boss(new_id, new_name, new_Depertment_id);
				break;
			default:
				break;
			}

			this->arrays_of_workers[the_index_of_worker] = worker;

			cout << "删除成功" << endl;

			this->save();

		}
		else {
			cout << "找不到要修改信息的人" << endl;
		}
	}
	system("pause");
};

//查找员工
void Workmanger:: to_find_worker() {
	if (this->Fileisempty)
	{
		cout << "没有可查找的员工" << endl;
	}
	else {
		cout << "请输入要以何种方式查找" << endl;
		cout << "1.以员工编号的方式" << endl;
		cout << "2.以员工姓名的方式" << endl;

		int button_of_select = 0;
		cin >> button_of_select;

		if (button_of_select = 1)
		{
			cout << "请输入要查找的人的编号" << endl;
			int enter_id = 0;
			cin >> enter_id;

			int the_index_of_worker = the_worker_is_exsit(enter_id);
			if (the_index_of_worker != -1)
			{
				cout << "成功找到此人，信息如下" << endl;
				this->arrays_of_workers[the_index_of_worker]->showalldetails();

			}
			else
			{
				cout << "找不到此人" << endl;
			}
		}
		else if (button_of_select = 2)
		{
			cout << "请输入要查找的人的姓名" << endl;
			string name;
			cin >> name;

			bool flage = true;

			for (int i = 0; i < number_of_workers; i++)
			{
				if (this->arrays_of_workers[i]->name == name) {
					this->arrays_of_workers[i]->showalldetails();

					flage = true;
				}
			}
			if (flage == false)
			{
				cout << "找不到此人" << endl;
			}
		}
		else
		{
			cout << "输入有误，请重新输入" << endl;
		}

	}
	system("pause");
};

//排序功能
void Workmanger::sort_worker() {

	if (Fileisempty)
	{
		cout << "文件不存在，无法排序" << endl;
		system("pause");
	}
	else {
	
		cout << "请选择升序还是降序" << endl;
		cout << "1.升序" << endl;
		cout << "2.降序" << endl;

		int button_of_select = 0;
		cin >> button_of_select;

		for (int i = 0; i < number_of_workers; i++)
		{
			int min_or_max = i;	
			for (int j = i+1; j < number_of_workers; j++)
			{
				if (button_of_select == 1) {//升序
					if (arrays_of_workers[min_or_max]->id > arrays_of_workers[j]->id)
					{
						min_or_max = j;
					}
				
				}
				else //降序
				{
					if (arrays_of_workers[min_or_max]->id < arrays_of_workers[j]->id)
					{
						min_or_max = j;
					}
				}
			}

			if (i != min_or_max)
			{
				Worker* temp = NULL;
				temp = arrays_of_workers[i];
				arrays_of_workers[i] = arrays_of_workers[min_or_max];
				arrays_of_workers[min_or_max] = temp;
			}

		}

		cout << "排序成功" << endl;

		this->save();

		this->show_all_Details();
	}
};

//清空功能
void Workmanger::cleanallthings() {

	cout << "是否要清空数据？" << endl;
	cout << "1.清空" << endl;
	cout << "2.在考虑考虑" << endl;

	int button_of_select = 0;
	cin >> button_of_select;

	if (button_of_select == 1)
	{
		ofstream ofs;
		ofs.open(FILE, ios::trunc);
		ofs.close();

		if (this->arrays_of_workers != NULL)
		{
			//删除堆区每个职工对象
			for (int i = 0; i < number_of_workers;i++) {
				delete this->arrays_of_workers[i];
				this->arrays_of_workers[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->arrays_of_workers;
			this->arrays_of_workers = NULL;
			this->number_of_workers = 0;
			this->Fileisempty = true;
		}

		cout << "清空成功" << endl;
	}
	system("pause");
};

//析构函数
Workmanger::~Workmanger(){
	if (arrays_of_workers != NULL) //在上第一次释放之后，数组又被新空间赋值了，所以要在释放一次
	{
		for (int i = 0; i < number_of_workers; i++)
		{
			if (this->arrays_of_workers[i] != NULL) 
			{
				delete this->arrays_of_workers[i];
			}
		}
		
		delete [] this->arrays_of_workers;
		arrays_of_workers = NULL;
	}
}