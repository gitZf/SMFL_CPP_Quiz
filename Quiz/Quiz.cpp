// Zoltan Fuzesi C00197361 Date : 17/01/2017

#include "stdafx.h"
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include<vector>
#include<random>
#include <time.h>
#include"Leaderboard.h"
#include"Question.h"

using namespace std;



void shuffleFourQuestions(vector<vector<string>>*a, int i)
{
	for (int k = i + 1; k < i + 4; k++) {
		int r = k + rand() % ((i + 4) - k);
		swap(a[k][0], a[r][0]);
		swap(a[k][1], a[r][1]);
	}
}


int main()
{
	Leaderboard lead = Leaderboard();
	Question qest = Question();
	double score = 0 , userScore = 0 , multyScore = 5;
	int countGoodAns = 0, questionCounter = 0, s = (int)score, x = 0, y = 0, ansPos, selected = 0, timeFromStart = 0, qust = 0, i = 0;
	string quest = "Question 1", highScore = "High Score ", line, userAns;
	bool updateQuestions = true, finalPage = true, isAnswered = true, menu = true, exit = false, play = true, up = true;
	bool showAns = false, highScoreMenu = false, exitScoreMenu = true, down = true, nextTurn = true, menuReturn = true;
	bool returnPress = true, timeStart = false, nextEnter = false, disableSelection = false;
	time_t start;
	//double userScore = 0;

	vector<string>scoreDate;
	scoreDate.resize(10);
	vector<int> scoreInt;
	scoreDate.resize(10);
	vector<int> a = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
	std::srand(std::time(0));
	std::random_shuffle(a.begin(), a.end());
	vector<vector<string>>txt;
	txt.resize(100);
	vector<vector<string, string>>tempTxt;
	tempTxt.resize(4);
	for (int i = 0; i < 4; i++)
	{
		tempTxt[i].resize(2);
		tempTxt[i][0] = "";
		tempTxt[i][1] = "";
	}
	for (int i = 0; i < 100; ++i)
	{
		txt[i].resize(2);
	}
	
	txt = qest.loadQuestions();

	std::string str;
	i = 1;
	int sec = 0;
	lead.buildScoreVectorList();
	scoreDate = lead.getDates();
	scoreInt = lead.getScores();

	//create Window
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Quiz");

	//font
	sf::Font font;
	if (!font.loadFromFile("font/walk.ttf"))
	{
		std::cout << "Can't load font";
	}


	//Final text
	sf::Text final;
	final.setFont(font);
	final.setFillColor(sf::Color::Blue);
	final.setCharacterSize(30);
	final.setStyle(sf::Text::Bold);
	final.setString("You have Good answers");
	final.setPosition(sf::Vector2f(120, 50));

	//Final text
	sf::Text finalScore;
	finalScore.setFont(font);
	finalScore.setFillColor(sf::Color::Blue);
	finalScore.setCharacterSize(30);
	finalScore.setStyle(sf::Text::Bold);
	finalScore.setString("Your final score is : ");
	finalScore.setPosition(sf::Vector2f(120, 200));
	//Menu
	sf::Text textMenu[5];
	x = 300;
	y = 150;
	//changed
	for (int i = 0; i < 5; i++)
	{
		textMenu[i].setFont(font);
		textMenu[i].setFillColor(sf::Color::Red);
		textMenu[i].setCharacterSize(44);
		textMenu[i].setStyle(sf::Text::Bold);
		textMenu[i].setString("");
		textMenu[i].setPosition(sf::Vector2f(x, y));
		y += 100;
	}
	//Special conditions
	textMenu[0].setFillColor(sf::Color::Blue);
	textMenu[0].setCharacterSize(64);
	textMenu[0].setString("Welcome to computing Quiz");
	textMenu[0].setPosition(sf::Vector2f(80, 50));

	textMenu[1].setFont(font);
	textMenu[1].setFillColor(sf::Color::Green);
	textMenu[1].setString("Play Quiz");

	textMenu[2].setString("High score");

	textMenu[3].setString("Exit game");

	textMenu[4].setString(highScore);
	textMenu[4].setPosition(sf::Vector2f(200, 450));

	//Question and answers

	sf::Text ans;
	ans.setFont(font);
	ans.setFillColor(sf::Color::Blue);
	ans.setCharacterSize(18);
	ans.setStyle(sf::Text::Bold);
	ans.setString("");
	ans.setPosition(sf::Vector2f(120, 500));

	sf::Text textQuiz[5][2];
	x = 120;
	y = 50;
	//changed
	for (int i = 0; i < 5; i++)
	{
		textQuiz[i][0].setFont(font);
		textQuiz[i][0].setFillColor(sf::Color::Green);
		textQuiz[i][0].setCharacterSize(44);
		textQuiz[i][0].setStyle(sf::Text::Bold);
		textQuiz[i][0].setString("");
		textQuiz[i][0].setPosition(sf::Vector2f(x, y));
		y += 100;
	}
	textQuiz[0][0].setFillColor(sf::Color::Green);
	textQuiz[0][0].setCharacterSize(18);
	textQuiz[0][0].setPosition(sf::Vector2f(50, 50));

	//high score
	sf::Text leaderboaard;
	leaderboaard.setFont(font);
	leaderboaard.setFillColor(sf::Color::Green);
	leaderboaard.setCharacterSize(35);
	leaderboaard.setStyle(sf::Text::Bold);
	leaderboaard.setString("Leaderboard");
	leaderboaard.setPosition(sf::Vector2f(50, 50));

	sf::Text HighScoreTxt[6];
	x = 50;
	y = 100;
	//changed
	for (int i = 0; i < 6; i++)
	{
		HighScoreTxt[i].setFont(font);
		HighScoreTxt[i].setFillColor(sf::Color::Blue);
		HighScoreTxt[i].setCharacterSize(18);
		HighScoreTxt[i].setStyle(sf::Text::Bold);
		HighScoreTxt[i].setString(" ");
		HighScoreTxt[i].setPosition(sf::Vector2f(x, y));
		y += 50;
	}




	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;


	clock.restart();

	while (window.isOpen())
	{
		// chek if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greate than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{
			// clear the screen and draw all the shapes

			window.clear();

			if (menu && questionCounter == 0)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && up)
				{
					up = false;
					if (textMenu[1].getFillColor() == (sf::Color::Red) && textMenu[2].getFillColor() == (sf::Color::Green))
					{
						textMenu[1].setFillColor(sf::Color::Green);
						textMenu[2].setFillColor(sf::Color::Red);
						textMenu[3].setFillColor(sf::Color::Red);
						play = true;
						highScoreMenu = false;
					}
					else if (textMenu[2].getFillColor() == (sf::Color::Red) && textMenu[3].getFillColor() == (sf::Color::Green))
					{
						textMenu[1].setFillColor(sf::Color::Red);
						textMenu[2].setFillColor(sf::Color::Green);
						textMenu[3].setFillColor(sf::Color::Red);
						play = false;
						highScoreMenu = true;
					}
					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && down)
				{
					down = false;
					if (textMenu[2].getFillColor() == (sf::Color::Red) && textMenu[1].getFillColor() == (sf::Color::Green))
					{
						textMenu[1].setFillColor(sf::Color::Red);
						textMenu[2].setFillColor(sf::Color::Green);
						textMenu[3].setFillColor(sf::Color::Red);
						play = false;
						highScoreMenu = true;
					}
					else if (textMenu[3].getFillColor() == (sf::Color::Red) && textMenu[2].getFillColor() == (sf::Color::Green))
					{
						textMenu[1].setFillColor(sf::Color::Red);
						textMenu[2].setFillColor(sf::Color::Red);
						textMenu[3].setFillColor(sf::Color::Green);
						play = false;
						highScoreMenu = false;
						exit = false;
					}

				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					up = true;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					down = true;
				}
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && menuReturn == false)
				{
					menuReturn = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && menuReturn)
				{
					if (play&&highScoreMenu == false)
					{
						menu = false;
						questionCounter = 0;
						qust = 0;
						std::srand(std::time(0));
						std::random_shuffle(a.begin(), a.end());
						showAns = false;
						timeStart = true;
					}
					else if (highScoreMenu&& play == false)
					{
						menu = false;
					}
					else if(exit)
					{
						window.close();
					}
					else
					{
						if (textMenu[1].getFillColor() == (sf::Color::Green))
						{
							play = true;
							timeStart = true;
							userScore = 0;
						}
						else if (textMenu[2].getFillColor() == (sf::Color::Green))
						{
							highScoreMenu = true;
							menu = false;
						}
							
						else if (textMenu[3].getFillColor() == (sf::Color::Green))
							window.close();
					}
					menuReturn = false;
				}
				//changed
				for (int i = 0; i < 4; i++)
				{
					window.draw(textMenu[i]);
				}
			}

			if((highScoreMenu || play)&&menu==false)
			{
				if (highScoreMenu)
				{
					lead.buildScoreVectorList();
					scoreDate = lead.getDates();
					scoreInt = lead.getScores();
					//show the high score and back option
					string scoreStr;
					//changed
					for (int i = 0; i < 5; i++)
					{
						scoreStr = to_string(i+1) + ". " + to_string(scoreInt[i]) + " points  : " + scoreDate[i];
						HighScoreTxt[i].setString(scoreStr);				
					}
					HighScoreTxt[5].setString("Hit Enter back to Main menu");
					window.draw(leaderboaard);
					//changed
					for (int i = 0; i < 6; i++)
					{
						window.draw(HighScoreTxt[i]);
					}
				

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&&exitScoreMenu == false)
					{
						highScoreMenu = false;
						exitScoreMenu = true;
						menu = true;
					}
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						exitScoreMenu = false;
					}
				}
				else if(play)
				{
					if (timeStart)
					{
						start = time(0);
						timeStart = false;
						finalPage = true;
					}
	
					// get keyboard input.
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && up && disableSelection == false)
					{
						if (textQuiz[1][0].getFillColor() == (sf::Color::Red) && textQuiz[2][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Green);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Red);
							userAns = textQuiz[1][1].getString();
							cout << userAns;
						}
						else if (textQuiz[2][0].getFillColor() == (sf::Color::Red) && textQuiz[3][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Red);
							textQuiz[2][0].setFillColor(sf::Color::Green);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Red);
							userAns = textQuiz[2][1].getString();
							cout << userAns;
						}
						else if (textQuiz[3][0].getFillColor() == (sf::Color::Red) && textQuiz[4][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Red);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Green);
							textQuiz[4][0].setFillColor(sf::Color::Red);
							userAns = textQuiz[3][1].getString();
							cout << userAns;
						}
						else if (textQuiz[4][0].getFillColor() == (sf::Color::Red) && textQuiz[1][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Red);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Green);
							userAns = textQuiz[4][1].getString();
							cout << userAns;
						}
						else
						{
							textQuiz[1][0].setFillColor(sf::Color::Red);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Green);
							userAns = textQuiz[4][1].getString();
							cout << userAns;
						}
						up = false;

					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && down && disableSelection == false)
					{
						if (textQuiz[1][0].getFillColor() == (sf::Color::Red) && textQuiz[4][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Green);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Red);
							userAns = textQuiz[1][1].getString();
							cout << userAns;
						}
						else if (textQuiz[2][0].getFillColor() == (sf::Color::Red) && textQuiz[1][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Red);
							textQuiz[2][0].setFillColor(sf::Color::Green);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Red);
							userAns = textQuiz[2][1].getString();
							cout << userAns;
						}
						else if (textQuiz[3][0].getFillColor() == (sf::Color::Red) && textQuiz[2][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Red);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Green);
							textQuiz[4][0].setFillColor(sf::Color::Red);
							userAns = textQuiz[3][1].getString();
							cout << userAns;
						}
						else if (textQuiz[4][0].getFillColor() == (sf::Color::Red) && textQuiz[3][0].getFillColor() == (sf::Color::Green))
						{
							textQuiz[1][0].setFillColor(sf::Color::Red);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Green);
							userAns = textQuiz[4][1].getString();
							cout << userAns;
						}
						else
						{
							textQuiz[1][0].setFillColor(sf::Color::Green);
							textQuiz[2][0].setFillColor(sf::Color::Red);
							textQuiz[3][0].setFillColor(sf::Color::Red);
							textQuiz[4][0].setFillColor(sf::Color::Red);
							userAns = textQuiz[1][1].getString();
							cout << userAns;
						}
						down = false;

					}

					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						up = true;
					}
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						down = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && nextTurn && questionCounter <= 11 && isAnswered == false && nextEnter == false)
					{
						nextTurn = true;
						isAnswered = false;
						nextEnter = true;
						updateQuestions = true;
						if (!userAns.compare("T"))
						{
							countGoodAns++;

							userScore += multyScore * 100;
							ans.setString("The answer was correct!\nHit Enter to next question");
							ans.setFillColor(sf::Color::Green);
							showAns = true;
						}
						else
						{
							string correctAns;
							string tr = "T";
							for (int i = ansPos; i < ansPos + 5; i++)
							{
								string tempStr = txt[i][1];

								if(tempStr.compare(tr) == 0)
									correctAns = txt[i][0];
							}
							
							ans.setString("The answer was NOT correct!\nCorrect : "+ correctAns +"\nHit Enter to next question");
							ans.setFillColor(sf::Color::Red);
							showAns = true;
						}
						userAns = "";
						
							questionCounter++;
					}
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && nextTurn && questionCounter <= 10 && isAnswered == false&&nextEnter)
					{
						disableSelection = true;
						nextEnter = false;
						isAnswered = true;
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && nextTurn && questionCounter <10 && isAnswered&&nextEnter==false)
					{
						disableSelection = false;
						isAnswered = false;
						if (qust < 50 && updateQuestions)
						{
							int max = 0;
							int pos = a[questionCounter] * 5;
							ansPos = pos;
							//changed
							for (int i = 1; i < 5; i++)
							{
								textQuiz[i][0].setFillColor(sf::Color::Red);
							}
						
							if (txt[pos][0].length() > 70)
							{
								textQuiz[0][0].setCharacterSize(13);
							}
							else
							{
								textQuiz[0][0].setCharacterSize(25);
							}

							for (int i = 1; i < 5; i++)
							{
								textQuiz[i][0].setCharacterSize(25);
							}
						
							
							int tempPos = pos+1;
							//changed
							for (int i = 0; i < 4; i++)
							{
								tempTxt[i][0] = txt[tempPos][0];
								tempTxt[i][1] = txt[tempPos][1];
								tempPos++;
							}


							std::srand(std::time(0));
							std::random_shuffle(tempTxt.begin(), tempTxt.end());
							textQuiz[0][0].setString(to_string(questionCounter+1) +" : "+ txt[pos][0]);
							textQuiz[0][1].setString(txt[pos][1]);
							qust++;
							pos++;
							//changed
							for (int i = 1; i < 5; i++)
							{
								textQuiz[i][0].setString(tempTxt[i-1][0]);
								textQuiz[i][1].setString(tempTxt[i-1][1]);
								qust++;
								pos++;
							}

						}
						updateQuestions = false;
						nextTurn = false;
						multyScore = 5;
					}
				
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						nextTurn = true;
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && questionCounter >= 10&&returnPress)
					{
						questionCounter++;
						returnPress = false;
						if(questionCounter==11)
							isAnswered = true;
					}
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
					{
						returnPress = true;
					}
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && questionCounter == 10 && finalPage == false)
					{
						finalPage = true;
						//questionCounter++;
					}
					
					if (questionCounter == 13)
					{

						menu = true;
						questionCounter = 0;
						countGoodAns = 0;
						userAns = "";
						isAnswered = true;
						nextEnter = false;
						if (userScore > score)
						{
							score = userScore;
							userScore = 0;
							int s = (int)score;
							highScore = "High Score " + to_string(s);
							textMenu[4].setString(highScore);
						}
						else
						{
							int s = (int)score;
							highScore = "High Score " + to_string(s);
							textMenu[4].setString(highScore);
						}
						int tempScore = 0;
						bool write = true;
						//check the position
						for (int j = 0; j <= 5; j++)
						{
							if ((int)score > scoreInt[j]&& write)
							{
								write = false;
								for (int k = 5; k > j; k--)
								{
									scoreInt[k] = scoreInt[k - 1];
									scoreDate[k] = scoreDate[k - 1];

								}
								scoreInt[j] = score;
								scoreDate[j] = lead.currentDateTime();
							}
						}
						
						if (score > 0)
						{
							//write score txt In Leaderboard class
							lead.writeLeaderboard(scoreDate, scoreInt);
						}
						score = 0;


					}

					if (questionCounter == 12)
					{
						updateQuestions = true;
						isAnswered = false;
						ans.setString("Enter to Main menu");
						if (finalPage)
						{
							int seconds_since_start = difftime(time(0), start);
							string strtime = lead.currentDateTime();
							int s = (int)userScore;
							finalScore.setString("Score : " + to_string(s) + "\nDate : " + strtime + "\nSeconds : " + to_string(seconds_since_start));
						}

						isAnswered = true;
						finalPage = false;
						final.setString("You have " + to_string(countGoodAns) + " good answers");
						isAnswered = false;
						window.draw(final);
						window.draw(finalScore);
						window.draw(ans);
					}

					// update any variables...
					if (questionCounter <= 11)
					{
						//changed
						for (int i = 0; i < 5; i++)
						{
							window.draw(textQuiz[i][0]);
						}
					}
		
					
					if (showAns&&isAnswered)
					{
						window.draw(ans);
					}
						
				}
			}

			window.display();
			timeFromStart++;
			if (timeFromStart % 50 == 0 && multyScore > 0.5)
				multyScore -= 0.2;

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}
