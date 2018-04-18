#pragma once

#include <fstream>
#include<vector>
#include<string>
using namespace std;

class Question
{
private:
	vector<vector<string>>txt;
	string line;

public:
	Question();

	vector<vector<string>> loadQuestions();
};