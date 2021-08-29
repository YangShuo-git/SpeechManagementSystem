#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Speaker.h"
using namespace std;

// ����ݽ�������
class CSpeechManager
{
public:
	//����ѡ�� ����  12��
	vector<int>vPlayer;
	//��һ�ֽ�������  6��
	vector<int>vRound1;
	//ʤ��ǰ��������  3��
	vector<int>vVictory;
	//��ű�� �Լ���Ӧ�� ����ѡ�� ����
	map<int, CSpeaker> m_Speaker;

	int m_Index;


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








};