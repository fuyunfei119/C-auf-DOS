#include <iostream>
using namespace std;
#include "workmanager.h"
#include "Emperyee.h"
#include "Boss.h"
#include "Manager.h"


int main() {
	//实例化对象
	Workmanger  workmanager;
	
	////员工功能测试
	////1.创建父类指针，指向子类对象，完成多态
	//Worker* emperyee = new Emperyee(1,"zhangsan","IT部门");
	//Worker* manager = new Manager(2, "lisi", "管理层");
	//Worker* boss = new Boss(3, "wangwu", "总裁");

	////2.用父类指针调用子类中的函数（功能）
	//emperyee->showalldetails();
	//emperyee->showdepertmentname();
	//delete emperyee;

	//manager->showalldetails();
	//manager->showdepertmentname();
	//delete manager;

	//boss->showalldetails();
	//boss->showdepertmentname();
	//delete boss;

	//用户的选择
	int choice = 0;
	

	do
	{
		//显示主菜单
		workmanager.showmenu();

		//接受用户想要的功能
		cout << "please choose your nummber" << endl;
		cin >> choice;
		if (!(choice >= 0 && choice <= 7))
		{
			cout << "Error,plase choose again" << endl;
			system("pause");
			//system("cls");
		}
		else
		{
			switch (choice)
			{

			case 0:
				workmanager.Exitsystem();
				break;
			case 1:
				workmanager.Add_works_to_system();
				break;
			case 2:
				workmanager.show_all_Details();
				break;
			case 3:
				workmanager.delete_singel_worker();
				break;
			case 4:
				workmanager.modify_the_information_of_worker();
				break;
			case 5:
				workmanager.to_find_worker();
				break;
			case 6:
				workmanager.sort_worker();
				break;
			case 7:
				workmanager.cleanallthings();
				break;
			default:
				system("cls");
				cout << "plase choose right nummber" << endl;
				break;
			}
		}
	} while (true);
}