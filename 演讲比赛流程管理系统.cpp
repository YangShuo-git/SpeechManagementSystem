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
		cout << "ѡ�ֱ�ţ�" << it->first
			<< " ������ " << it->second.m_name
			<< " �ɼ��� " << it->second.m_score[0] << endl;
	}
#endif

	int choice = 0;
	while (true)
	{
		sm.showMenu();

		cout << "���������ѡ��" << endl;
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