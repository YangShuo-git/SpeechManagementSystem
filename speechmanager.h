#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Speaker.h"
using namespace std;

// 设计演讲管理类
class CSpeechManager
{
public:
	//比赛选手 容器  12人
	vector<int>vPlayer;
	//第一轮晋级容器  6人
	vector<int>vRound1;
	//胜利前三名容器  3人
	vector<int>vVictory;
	//存放编号 以及对应的 具体选手 容器
	map<int, CSpeaker> m_Speaker;

	int m_Index;


public:
	CSpeechManager();
	~CSpeechManager();

	// 展示菜单
	void showMenu();
	// 退出系统
	void exitSystem();

	// 初始化属性
	void initSpeech();

	// 初始化创建12名选手
	void createSpeaker();

	// 开始比赛 - 比赛流程控制
	void startSpeech();

	// 抽签
	void speechDraw();

	// 比赛
	void speechContest();








};