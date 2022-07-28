/* 设计演讲管理类
功能描述
（1）提供菜单界面与用户交互
（2）对演讲比赛流程进行控制
（3）与文件进行读写交互
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

	// 显示每一轮的比赛分数
	void showScore();

	// 保存分数
	void saveRecord();

	// 读取记录分数
	void loadRecord();

	// 清空记录
	void clearRecord();

public:
	vector<int> vRound1;    //比赛选手    12人   这3个vector存放的都是编号
	vector<int> vRound2;    //第一轮晋级  6人   
	vector<int> vVictory;   //胜利前三名  3人	
	map<int, CSpeaker> m_speaker; //存放编号 以及 对应的具体选手 

	int m_Index;  //记录比赛轮数

	bool fileIsEmpty;  //判断文件是否为空的标志
	map<int, vector<string>> m_record; //记录往届获胜分数的容器
};