#include"Leaderboard.h"

Leaderboard::Leaderboard()
{
	scoreDate.resize(10);
	scoreInt.resize(10);
}

string Leaderboard::currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return buf;
}

void Leaderboard::buildScoreVectorList()
{
	int i = 1;
	int sec = 0;
	ifstream fileS("score.txt");
	while (i <= 10)
	{
		std::getline(fileS, str);
		if (i % 2 == 0)
		{
			if (str.size() == 0)
				str = "0000-00-00.00:00:00";
			scoreDate[sec] = str;
			sec++;
		}
		else
		{
			if (str.size() == 0)
				str = "0";
			scoreInt[sec] = stoi(str);
		}
		i++;
	}

}

vector<int> Leaderboard::getScores()
{
	return scoreInt;
}
vector<string> Leaderboard::getDates()
{
	return scoreDate;
}

void Leaderboard::writeLeaderboard(vector<string>s, vector<int>i)
{
	ofstream myfile;
	myfile.open("score.txt");
	int n = 0;
	while (n < 5)
	{
		myfile << i[n] << endl;
		myfile << s[n] << endl;
		n++;
	}
	myfile.close();
}