#pragma once


#include <iostream>
#include <fstream>
#include<vector>
#include <time.h>
#include<string>
using namespace std;

class Leaderboard
{
private:
	vector<int>scoreInt;
	string str;
	vector<string>scoreDate;


public:
	Leaderboard();

	string currentDateTime();

	void buildScoreVectorList();

	vector<int> getScores();

	vector<string> getDates();

	void writeLeaderboard(vector<string>s, vector<int>i);
};
