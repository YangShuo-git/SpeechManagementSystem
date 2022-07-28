/*
1����������
��1��ѧУ����һ���ݽ���������12�˲μӣ����������֣���һ��Ϊ��̭�����ڶ���Ϊ������
��2��ÿ��ѡ�ֶ��ж�Ӧ�ı�ţ���10001����10012
��3��������ʽ�����������ÿ��6����
��4����һ�ַ�Ϊ����С�飬���尴��ѡ�ֱ�Ž��г�ǩ��˳���ݽ�
��5��ʮ����ί�ֱ��ÿ��ѡ�ִ�֣�ȥ����߷ֺ���ͷ֣���ƽ����Ϊѡ�ֵĳɼ�
��6����С���ݽ���Ϻ���̭����������������ѡ�֣�ǰ����������������һ�ֱ�����
��7���ڶ���Ϊ������ǰ����ʤ����
��8��ÿ�ֱ���������Ҫ��ʾ����ѡ�ֵ���Ϣ

2��������
��1����ʼ�ݽ����������������������̣�ÿ�������׶���Ҫ���û�һ����ʾ���û���������������һ���׶�
��2���鿴�����¼���鿴֮ǰ����ǰ���������ÿ�α��������¼���ļ��У��ļ���.CSV��׺������
��3����ձ�����¼�����ļ����������
��4���˳��������򣺿����˳���ǰ����
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
	//����ѡ���Ƿ񴴽��ɹ�
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