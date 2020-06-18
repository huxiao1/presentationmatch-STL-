#include<iostream>
using namespace std;
#include "speechManager.h"

int main()
{
	srand((unsigned int)time(NULL));
    SpeechManager sm;
    int choice = 0; //用来存储用户的选项

    /*
    test
    for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
    {
	    cout  << "player number:" << it->first 
            << "name:" << it->second.m_Name 
            << "score:" << it->second.m_Score[0] <<endl;
    }
    */

	while (true)
	{
		sm.show_Menu();

		cout << "Please input your choice:";
		cin >> choice; // 接受用户的选项

		switch (choice)
		{
		    case 1:  //开始比赛
                sm.startSpeech();
			    break;
		    case 2:  //查看记录
				sm.showRecord();
			    break;
		    case 3:  //清空记录
				sm.clearRecord();
			    break;
		    case 0:  //退出系统
                sm.exitSystem();
			    break;
		    default:
			    system("cls"); //清屏
			    break;
		}
	}

    system("pause");
    return 0;
}