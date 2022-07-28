#include "speechmanager.h"
#include <algorithm>
#include <numeric>
#include <deque>
#include <fstream>
using namespace std;

CSpeechManager::CSpeechManager()
{
	//初始化属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
}

void CSpeechManager::showMenu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void CSpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void CSpeechManager::initSpeech()
{
	//容器保证为空
	this->vRound1.clear();
	this->vRound2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	//初始化比赛轮数
	this->m_Index = 1;
}

void CSpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];    // 字符串的拼接

		// 实例化选手
		CSpeaker sp;
		// 每一名选手姓名
		sp.m_name = name;
		// 每一名选手分数置为0
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}

		//12名选手的标号10001-10012 
		this->vRound1.push_back(i + 10001);
		//选手编号 以及对应的选手 存放到map容器中
		this->m_speaker.insert(make_pair(i + 10001, sp));   // map中的key（编号）、value（选手）
	}
}
	
void CSpeechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	speechDraw();
	//2、比赛
	speechContest();
	//3、显示晋级结果
	showScore();

	//第二轮比赛
	m_Index++;
	//1、抽签
	speechDraw();
	//2、比赛
	speechContest();
	//3、显示最终结果
	showScore();
	//4、保存分数
	saveRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

void CSpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
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
	cout << "------------- 第" << this->m_Index << "轮正式比赛开始：------------- " << endl;

	multimap<double, int, greater<int>> groupScore; //临时容器，保存double为key分数 int为value选手编号 greater<int>表示会自动降序排列

	int num = 0; //记录人员数，6个为1组

	vector <int> v_Src;   //比赛的人员容器
	if (this->m_Index == 1)   //如果是第一轮，则操作的容器为vRound1 
	{
		v_Src = vRound1;
	}
	else                      //如果是第二轮，则现行操作的容器为vRound2 
	{
		v_Src = vRound2;
	}

	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;

		//10个评委打分，成绩用deque容器存储
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());				//sort后，d就是已排序的容器
		d.pop_front();												//去掉最高分
		d.pop_back();												//去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);			//获取总分
		double avg = sum / (double)d.size();						//获取平均分

		//每个人平均分
		//cout << "编号： " << *it  << " 选手： " << this->m_Speaker[*it].m_Name << " 获取平均分为： " << avg << endl;  //打印分数
		this->m_speaker[*it].m_score[this->m_Index - 1] = avg;  //这里map可以通过key来确定该元素，然后该元素可以调用自己的属性或方法

		//6个人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{

			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator 
				it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号: " << it->second 
					<< " 姓名： " << this->m_speaker[it->second].m_name 
					<< " 成绩： " << this->m_speaker[it->second].m_score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//取前三名
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
	cout << "------------- 第" << this->m_Index << "轮比赛完毕  ------------- " << endl;
	system("pause");
}

//显示比赛结果的实现
void CSpeechManager::showScore() {
	cout << "-------------- 第<<" << this->m_Index << ">>轮晋级选手信息如下:-----------------" << endl;
	vector<int> v;   //临时容器 
	if (this->m_Index == 1) {   //如果是第一轮操作，将vRound2作为显示容器 
		v = vRound2;
	}
	else {                     //如果是第二轮比赛，将最终容器作为显示容器 
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << " 选手编号：" << *it
			 << " 姓名：" << this->m_speaker[*it].m_name
			 << " 得分：" << this->m_speaker[*it].m_score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->showMenu();
}
void CSpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app); //--以追加的方式向文件里输入数据 （对于代码来说，就是out）

	//将每个人的数据写入文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << ","
			<< m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	// 关闭文件 
	ofs.close();

	cout << "记录已经保存！" << endl;
}

void CSpeechManager::loadRecord() {
	ifstream ifs("speech.csv", ios::in); //输入流对象，读取文件

	//文件不存在 
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	//文件为空 
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);  //之前验证文件是否为空的单个字符放回去 
	string data;  //接收字符串的标识 
	int index = 1;
	while (ifs >> data) {   //接受字符串 
		//cout<<data<<endl;
		vector<string> v;   //字符串保存在该容器中 

		int pos = -1;//查到，位置的变量 
		int start = 0;

		while (true) {
			pos = data.find(",", start); //从0开始查找
			if (pos == -1) {
				break;    //找不到break返回 
			}
			//找到了，进行分割，参数1 起始位置，参数2 截取的长度 
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
		cout << " 比赛届数: " << it->first << " 冠军编号：" << it->second[0] << " 分数: " << it->second[1] << endl;
	}
}

//清空记录的函数的实现
void CSpeechManager::clearRecord() {
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、取消" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//打开模式 ios::trunc 如果存在删除文件并重更新创建 
		ofstream ofs("speech.csv", ios::trunc);
		ofs.clear();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

CSpeechManager::~CSpeechManager()
{

}