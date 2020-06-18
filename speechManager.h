#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "speaker.h"

//演讲管理类
class SpeechManager
{
public:
	vector<int>v1;                //比赛选手 容器  12人
	vector<int>v2;                //第一轮晋级容器  6人
	vector<int>vVictory;          //胜利前三名容器  3人
	map<int, Speaker> m_Speaker;  //存放编号 以及对应的 具体选手 容器
    int m_Index;                  //比赛轮数
    bool fileIsEmpty;             //文件标志
    map<int,vector<string>> m_Record;  //往届记录
    
    SpeechManager();
    ~SpeechManager();
    
    void show_Menu();       //展示菜单
    void exitSystem();      //退出系统
    void initSpeech();      //初始化属性 
    void createSpeaker();   //初始化创建12个选手
    void startSpeech();     //开始比赛
    void speechDraw();      //抽签
    void speechContest();   //比赛
    void showScore();       //显示比赛分数
    void saveRecord();     //保存记录
    void loadRecord();     //读取记录
    void showRecord();     //显示往届得分
    void clearRecord();    //清空记录
};


