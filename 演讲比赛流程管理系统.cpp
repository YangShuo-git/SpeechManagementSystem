#include <iostream>
#include "speechmanager.h"
using namespace std;
#define START 1
#define CHECK 2
#define CLEAR 3
#define EXIT  0

int main()
{
	CSpeechManager sm;

#if 0
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
			break;
		case CLEAR:
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