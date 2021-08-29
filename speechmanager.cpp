#include "speechmanager.h"
#include <algorithm>
#include <deque>


CSpeechManager::CSpeechManager()
{
	//��ʼ������
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
}

void CSpeechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void CSpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void CSpeechManager::initSpeech()
{
	//������֤Ϊ��
	this->vPlayer.clear();
	this->vRound1.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	//��ʼ����������
	this->m_Index = 1;
}

void CSpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];    // �ַ�����ƴ��

		// ʵ����ѡ��
		CSpeaker sp;
		// ÿһ��ѡ�ֱ��
		this->vPlayer.push_back(i + 10001);
		// ÿһ��ѡ������
		sp.m_name = name;
		// ÿһ��ѡ�ַ�����Ϊ0
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}
		//ѡ�ֱ�� �Լ���Ӧ��ѡ�� ��ŵ�map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));   // map�е�key����ţ���value��ѡ�֣�
	}
}
	
void CSpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	speechDraw();
	//2������

	//3����ʾ�������

	//�ڶ��ֱ���

	//1����ǩ

	//2������

	//3����ʾ���ս��

	//4���������
}

void CSpeechManager::speechDraw()
{
	cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(vPlayer.begin(), vPlayer.end());
		for (vector<int>::iterator it = vPlayer.begin(); it != vPlayer.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(vRound1.begin(), vRound1.end());
		for (vector<int>::iterator it = vRound1.begin(); it != vRound1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}

void CSpeechManager::speechContest()
{
	cout << "------------- ��" << this->m_Index << "����ʽ������ʼ��------------- " << endl;

	multimap<double, int, greater<int>> groupScore; //��ʱ����������key���� value ѡ�ֱ��

	int num = 0; //��¼��Ա����6��Ϊ1��

	vector <int>v_Src;   //��������Ա����
	if (this->m_Index == 1)
	{
		v_Src = vPlayer;
	}
	else
	{
		v_Src = vRound1;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());				//����
		d.pop_front();												//ȥ����߷�
		d.pop_back();												//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);				//��ȡ�ܷ�
		double avg = sum / (double)d.size();									//��ȡƽ����

		//ÿ����ƽ����
		//cout << "��ţ� " << *it  << " ѡ�֣� " << this->m_Speaker[*it].m_Name << " ��ȡƽ����Ϊ�� " << avg << endl;  //��ӡ����
		this->m_Speaker[*it].m_score[this->m_Index - 1] = avg;

		//6����һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{

			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator 
				it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second 
					<< " ������ " << this->m_Speaker[it->second].m_name 
					<< " �ɼ��� " << this->m_Speaker[it->second].m_score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//ȡǰ����
			for (multimap<double, int, greater<int>>::iterator 
				it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					vRound1.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();

			cout << endl;

		}
	}
	cout << "------------- ��" << this->m_Index << "�ֱ������  ------------- " << endl;
	system("pause");
}










CSpeechManager::~CSpeechManager()
{

}