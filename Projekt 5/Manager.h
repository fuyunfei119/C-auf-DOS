#pragma once
#include <iostream>
using namespace std;
#include "Worker.h"
#include<string>

class Manager :public Worker
{
public:

	//构造函数
	Manager(int enter_your_id, string enter_your_name, int enter_your_Depertment_id);

	//显示个人信息
	virtual void showalldetails();

	//显示部门名称
	virtual void showdepertmentname();

};