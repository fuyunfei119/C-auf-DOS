#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include <fstream>
#define FILE "books_of_workers.text"

class Workmanger
{
public:
	//构造函数
	Workmanger();

	//显示主菜单
	void showmenu();

	//退出系统
	void Exitsystem();

	//结束程序
	int button_to_stopping_programm = 1;

	//员工总数
	unsigned int number_of_workers;

	//员工数组指针
	Worker** arrays_of_workers;

	//添加员工功能
	void Add_works_to_system();

	//保存文件功能
	void save();

	//判断文件是否为空
	bool Fileisempty;

	//统计文件的人数
	int get_number_of_workers_in_books();

	//初始化员工
	void initialize();

	//显示所以员工功能
	void show_all_Details();

	//删除员工功能
	void delete_singel_worker();

	//判断员工是否存在
	int the_worker_is_exsit(int id);

	//修改成员数据功能
	void modify_the_information_of_worker();

	//查找员工
	void to_find_worker();

	//排序功能
	void sort_worker();

	//清空功能
	void cleanallthings();

	//析构函数
	~Workmanger();

};

