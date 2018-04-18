#include"Question.h"


Question::Question()
{
	txt.resize(100);
}

vector<vector<string>> Question::loadQuestions()
{
	for (int i = 0; i < 100; ++i)
	{
		txt[i].resize(2);
	}
	int i = 0;
	ifstream file("QuizQuestions/quiz.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			std::getline(file, line);
			txt[i][0] = line;
			getline(file, line);
			txt[i][1] = line;
			i++;
		}
	}
	file.close();
	return txt;
}