#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include "Boss.h"
#include <string>


//构造函数
Boss::Boss(int enter_your_id, string enter_your_name, int enter_your_Depertment_id) {
	this->id = enter_your_id;
	this->name = enter_your_name;
	this->Depertment_id = enter_your_Depertment_id;
}

//显示个人信息
void Boss::showalldetails()
{
	cout << "这个员工的员工\n\t\t编号是： " << this->id << "\t名字是： " << this->name << "\t部门名称是: " <<this->Depertment_id;
	showdepertmentname();
};

//显示部门名称
void Boss::showdepertmentname()
{
	cout << "\t是个老板" << endl;
};


