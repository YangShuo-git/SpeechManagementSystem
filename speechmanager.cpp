#include "speechmanager.h"
#include <algorithm>
#include <numeric>
#include <deque>
#include <fstream>
using namespace std;

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
	this->vRound1.clear();
	this->vRound2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
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
		// ÿһ��ѡ������
		sp.m_name = name;
		// ÿһ��ѡ�ַ�����Ϊ0
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}

		//12��ѡ�ֵı��10001-10012 
		this->vRound1.push_back(i + 10001);
		//ѡ�ֱ�� �Լ���Ӧ��ѡ�� ��ŵ�map������
		this->m_speaker.insert(make_pair(i + 10001, sp));   // map�е�key����ţ���value��ѡ�֣�
	}
}
	
void CSpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	speechDraw();
	//2������
	speechContest();
	//3����ʾ�������
	showScore();

	//�ڶ��ֱ���
	m_Index++;
	//1����ǩ
	speechDraw();
	//2������
	speechContest();
	//3����ʾ���ս��
	showScore();
	//4���������
	saveRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

void CSpeechManager::speechDraw()
{
	cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(vRound1.begin(), vRound1.end());
		for (vector<int>::iterator it = vRound1.begin(); it != vRound1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(vRound2.begin(), vRound2.end());
		for (vector<int>::iterator it = vRound2.begin(); it != vRound2.end(); it++)
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

	multimap<double, int, greater<int>> groupScore; //��ʱ����������doubleΪkey���� intΪvalueѡ�ֱ�� greater<int>��ʾ���Զ���������

	int num = 0; //��¼��Ա����6��Ϊ1��

	vector <int> v_Src;   //��������Ա����
	if (this->m_Index == 1)   //����ǵ�һ�֣������������ΪvRound1 
	{
		v_Src = vRound1;
	}
	else                      //����ǵڶ��֣������в���������ΪvRound2 
	{
		v_Src = vRound2;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//10����ί��֣��ɼ���deque�����洢
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());				//sort��d���������������
		d.pop_front();												//ȥ����߷�
		d.pop_back();												//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);			//��ȡ�ܷ�
		double avg = sum / (double)d.size();						//��ȡƽ����

		//ÿ����ƽ����
		//cout << "��ţ� " << *it  << " ѡ�֣� " << this->m_Speaker[*it].m_Name << " ��ȡƽ����Ϊ�� " << avg << endl;  //��ӡ����
		this->m_speaker[*it].m_score[this->m_Index - 1] = avg;  //����map����ͨ��key��ȷ����Ԫ�أ�Ȼ���Ԫ�ؿ��Ե����Լ������Ի򷽷�

		//6����һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{

			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator 
				it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second 
					<< " ������ " << this->m_speaker[it->second].m_name 
					<< " �ɼ��� " << this->m_speaker[it->second].m_score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//ȡǰ����
			for (multimap<double, int, greater<int>>::iterator 
				it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					vRound2.push_back((*it).second);
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

//��ʾ���������ʵ��
void CSpeechManager::showScore() {
	cout << "-------------- ��<<" << this->m_Index << ">>�ֽ���ѡ����Ϣ����:-----------------" << endl;
	vector<int> v;   //��ʱ���� 
	if (this->m_Index == 1) {   //����ǵ�һ�ֲ�������vRound2��Ϊ��ʾ���� 
		v = vRound2;
	}
	else {                     //����ǵڶ��ֱ�����������������Ϊ��ʾ���� 
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << " ѡ�ֱ�ţ�" << *it
			 << " ������" << this->m_speaker[*it].m_name
			 << " �÷֣�" << this->m_speaker[*it].m_score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}
void CSpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //--��׷�ӵķ�ʽ���ļ����������� �����ڴ�����˵������out��

	//��ÿ���˵�����д���ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << ","
			<< m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	// �ر��ļ� 
	ofs.close();

	cout << "��¼�Ѿ����棡" << endl;
}

void CSpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in); //���������󣬶�ȡ�ļ�

	//�ļ������� 
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	//�ļ�Ϊ�� 
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);  //֮ǰ��֤�ļ��Ƿ�Ϊ�յĵ����ַ��Ż�ȥ 
	string data;  //�����ַ����ı�ʶ 
	int index = 1;
	while (ifs >> data) {   //�����ַ��� 
		//cout<<data<<endl;
		vector<string> v;   //�ַ��������ڸ������� 

		int pos = -1;//�鵽��λ�õı��� 
		int start = 0;

		while (true) {
			pos = data.find(",", start); //��0��ʼ����
			if (pos == -1) {
				break;    //�Ҳ���break���� 
			}
			//�ҵ��ˣ����зָ����1 ��ʼλ�ã�����2 ��ȡ�ĳ��� 
			string tmp = data.substr(start, pos - start);

			//cout<<tmp<<endl;
			v.push_back(tmp);

			start = pos + 1;
		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	for (map<int, vector<string> >::iterator it = m_record.begin(); it != m_record.end(); it++) 
	{
		cout << " ��������: " << it->first << " �ھ���ţ�" << it->second[0] << " ����: " << it->second[1] << endl;
	}
}

//��ռ�¼�ĺ�����ʵ��
void CSpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//��ģʽ ios::trunc �������ɾ���ļ����ظ��´��� 
		ofstream ofs("speech.csv", ios::trunc);
		ofs.clear();

		//��ʼ������
		this->initSpeech();

		//����ѡ��
		this->createSpeaker();

		//��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

CSpeechManager::~CSpeechManager()
{

}