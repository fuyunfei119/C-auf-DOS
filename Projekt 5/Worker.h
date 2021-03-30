#pragma once
#include <iostream>
using namespace std;


class Worker
{
public:

	//显示个人信息
	virtual void showalldetails() = 0;

	//显示部门名称
	virtual void showdepertmentname() = 0;
	
	//员工编号
	int id;

	//员工姓名
	string name;

	//部门编号
	int Depertment_id;

};

