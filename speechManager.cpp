#include "speechManager.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();    //初始化属性
	this->createSpeaker(); //创建选手
	this->loadRecord();    //获取往届记录
}

SpeechManager::~SpeechManager()
{

}

void SpeechManager::show_Menu()
{
    cout << "********************************************" << endl;
	cout << "*************   Welcome To This Match!     ************" << endl;
	cout << "*************     1.Start Match            *************" << endl;
	cout << "*************     2.View previous records  *************" << endl;
	cout << "*************     3.Clear recordes         *************" << endl;
	cout << "*************     0.Quit                   *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout<<"See you next time"<<endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	this->v1.clear();       //容器保证为空
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;      //初始化比赛轮数
	//初始化记录容器
	this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "xuanshou";
		name += nameSeed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[i] = 0;
		}

		this->v1.push_back(i+10001);   //12名选手编号

		this->m_Speaker.insert(make_pair(i+10001,sp));  //选手编号,对应的选手都存在map中去
	}
}

void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	speechDraw();
	//2、比赛
	speechContest();
	//3、显示晋级结果
	showScore();
	//第二轮比赛
	this->m_Index++;
	//1、抽签
	speechDraw();
	//2、比赛
	speechContest();
	//3、显示最终结果
	showScore();
	//4、保存分数
	saveRecord();
	//5.重置比赛
	this->initSpeech();    //初始化属性
	this->createSpeaker(); //创建选手
	this->loadRecord();    //获取往届记录

	cout<<"match end!"<<endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "number of rounds is" << this->m_Index <<endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "the sequence after drawing:" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it!= v1.end(); it++)
		{
			cout<<*it<<" ";
		}
		cout<<endl;
	}
	else
	{
		random_shuffle(v2.begin(),v2.end());
		for (vector<int>::iterator it = v1.begin(); it!= v1.end(); it++)
		{
			cout<<*it<<" ";
		}
		cout<<endl;
	}
	cout<<"---------------------------------------------------------"<<endl;
	system("pause");
	cout<<endl;
}

void SpeechManager::speechContest()
{
	cout << "-------------number of<"<< this->m_Index << ">rounds------------- " << endl;
	multimap<double,int,greater<int>> groupScore;   //临时容器，保存key分数 value 选手编号
	//multimap允许插入相同的score的人，greater<int>可以降序排列
	int num = 0;  //记录人员数，6个一组

	vector<int> v_Src; //比赛的人员容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分 10个评委
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;  // 600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());				//排序
		d.pop_front();												//去掉最高分
		d.pop_back();												//去掉最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f);				//获取总分
		double avg = sum / (double)d.size();									//获取平均分
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//6个人一组，用临时容器保存
		groupScore.insert(make_pair(avg,*it));
		if (num % 6 == 0)
		{
			cout << "number of" << num/6 << "goup" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "number:" << it->second << "name:" << this->m_Speaker[it->second].m_Name << "grade:" << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//取前三
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
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
	cout << "-------------number of" << this->m_Index << "round is over------------- " << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "---------the winner info of number" << this->m_Index << "round:-----------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "number:" << *it << "name:" << m_Speaker[*it].m_Name << "score:" << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu(); 
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv",ios::out | ios::app);   //用输出的方式打开文件,写文件

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end() ; it++)
	{
		ofs<<*it<<","<<m_Speaker[*it].m_Score[1]<<",";
	}
	ofs<<endl;
	ofs.close();

	cout<<"record had been recorded!"<<endl;
	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv",ios::in);   //输入流对象 读取文件

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout<<"file is not exist"<<endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;   //读取单个字符并取出
	if (ifs.eof())
	{
		cout<<"file is empty!"<<endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//if文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch);    //读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",",start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start,pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index,v));
		index++;
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout<<"file is not exist or record is empty"<<endl;
	}
	else{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "number of" << i + 1 << "th competition" << endl <<
				"champion number:" << this->m_Record[i][0] << "   score" << this->m_Record[i][1] << endl <<
				"runner-up number" << this->m_Record[i][2] << "   score" << this->m_Record[i][3] << endl <<
				"bronze number" << this->m_Record[i][4] << "    score" << this->m_Record[i][5] << endl;
		}
		system("pause");
		system("cls");
	}
}

void SpeechManager::clearRecord()
{
	cout << "Sure?" << endl;
	cout << "1.Yes" << endl;
	cout << "2.No" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();
		
		cout << "success,say goodbye to past" << endl;
	}

	system("pause");
	system("cls");
}