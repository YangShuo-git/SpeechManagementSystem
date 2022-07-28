/* ����ݽ�������
��������
��1���ṩ�˵��������û�����
��2�����ݽ��������̽��п���
��3�����ļ����ж�д����
*/

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Speaker.h"
using namespace std;

class CSpeechManager
{
public:
	CSpeechManager();
	~CSpeechManager();

	// չʾ�˵�
	void showMenu();

	// �˳�ϵͳ
	void exitSystem();

	// ��ʼ������
	void initSpeech();

	// ��ʼ������12��ѡ��
	void createSpeaker();

	// ��ʼ���� - �������̿���
	void startSpeech();

	// ��ǩ
	void speechDraw();

	// ����
	void speechContest();

	// ��ʾÿһ�ֵı�������
	void showScore();

	// �������
	void saveRecord();

	// ��ȡ��¼����
	void loadRecord();

	// ��ռ�¼
	void clearRecord();

public:
	vector<int> vRound1;    //����ѡ��    12��   ��3��vector��ŵĶ��Ǳ��
	vector<int> vRound2;    //��һ�ֽ���  6��   
	vector<int> vVictory;   //ʤ��ǰ����  3��	
	map<int, CSpeaker> m_speaker; //��ű�� �Լ� ��Ӧ�ľ���ѡ�� 

	int m_Index;  //��¼��������

	bool fileIsEmpty;  //�ж��ļ��Ƿ�Ϊ�յı�־
	map<int, vector<string>> m_record; //��¼�����ʤ����������
};