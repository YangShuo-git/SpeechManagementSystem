/*
1、比赛规则：
（1）学校举行一场演讲比赛，共12人参加，比赛分两轮，第一轮为淘汰赛，第二轮为决赛，
（2）每个选手都有对应的编号：如10001——10012
（3）比赛方式：分组比赛，每组6个人
（4）第一轮分为两个小组，整体按照选手编号进行抽签后顺序演讲
（5）十名评委分别给每名选手打分，去除最高分和最低分，求平均分为选手的成绩
（6）当小组演讲完毕后，淘汰组内排名最后的三个选手，前三名晋级，进入下一轮比赛，
（7）第二轮为决赛，前三名胜出，
（8）每轮比赛过后需要显示晋级选手的信息

2、程序功能
（1）开始演讲比赛：完成整届比赛的流程，每个比赛阶段需要给用户一个提示，用户按任意键后继续下一个阶段
（2）查看往届记录：查看之前比赛前三名结果，每次比赛都会记录到文件中，文件用.CSV后缀名保存
（3）清空比赛记录：将文件中数据清空
（4）退出比赛程序：可以退出当前程序
*/


#include <iostream>
#include "speechmanager.h"
using namespace std;

#define START    1
#define CHECK    2
#define CLEAR    3
#define EXIT     0

int main()
{
	CSpeechManager sm;

#if 0
	//测试选手是否创建成功
	for (map<int, CSpeaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
	{
		cout << "选手编号：" << it->first
			<< " 姓名： " << it->second.m_name
			<< " 成绩： " << it->second.m_score[0] << endl;
	}
#endif

	int choice = 0;
	while (true)
	{
		sm.showMenu();

		cout << "请输入你的选择：" << endl;
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case START:
			sm.startSpeech();
			break;
		case CHECK:
			sm.loadRecord();
			break;
		case CLEAR:
			sm.clearRecord();
			break;
		case EXIT:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;	
		}
	}

	return 0;
}