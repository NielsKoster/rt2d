/**
 * This class describes DefaultScene behavior.
 *
 * Copyright 2020 Niels Koster
 */

#include <fstream>
#include <sstream>
#include <math.h>

#include "defaultscene.h"

DefaultScene::DefaultScene() : Scene()
{
	hexagons = std::vector<Hexagon*>();
	SetupHexGrid();
	player = new Player();
	menu = new Basicentity();
	mainmenubutton = new Button();
	quitbutton = new Button();
	menuselected = false;
	mainmenuselected = true;
	endscreenselected = false;
	findpath = false;
	destination = new Hexagon(0,0);
	menutext = new Text();
	menushade = new Basicentity();
	pauseicon = new Basicentity();
	scoreLine = new Text();
	timeLine = new Text();
	highscoreLine = new Text();
	mainmenubg = new Basicentity();
	playbutton = new Button();
	retrybutton = new Button();
	logo = new Basicentity();

	//Get mouse coordinates
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();
	//Combine them into a Point2
	Point2 mousepos = Point2(mousex, mousey);

	
	this->addChild(player);
	player->position = hexagons[500]->position;
	player->scale = hexagons[500]->scale;

	colorCounter = 0;
	addColors();

	randomTileCounter = 0;
	randomtileMax = 0;
	srand(time(NULL));

	points = 0;
	highscore = 0;
	maxtargets = 10;

	UISetup();

	timer = new Timer();
	timer->start();
}

DefaultScene::~DefaultScene()
{
	for (int i = 0; i < hexagons.size(); i++) 
	{
		delete hexagons[i];
	}

	delete player;
	delete menu;
	delete mainmenubutton;
	delete quitbutton;
	delete menutext;
	delete menushade;
	delete pauseicon;
	delete scoreLine;
	delete timeLine;
	delete highscoreLine;
	delete mainmenubg;
	delete playbutton;
	delete retrybutton;
	delete logo;
}

void DefaultScene::UISetup()
{
	this->addChild(menushade);
	this->addChild(menu);
	this->addChild(mainmenubutton);
	mainmenubutton->addChild(menutext);
	this->addChild(pauseicon);
	this->addChild(timeLine);
	this->addChild(mainmenubg);
	this->addChild(quitbutton);
	this->addChild(playbutton);
	this->addChild(highscoreLine);
	this->addChild(retrybutton);
	this->addChild(logo);

	menu->addSprite("assets/color.tga");
	menushade->addSprite("assets/color.tga");
	pauseicon->addSprite("assets/pause_icon.tga");
	mainmenubg->addSprite("assets/color.tga");
	logo->addSprite("assets/colorclicker_logo_c.tga");

	menushade->sprite()->color = BLACK;
	menushade->sprite()->color.a = 150;
	mainmenubg->sprite()->color = GRAY;

	menu->position.y = SHEIGHT / 2;
	mainmenubutton->position.y = SHEIGHT / 2;
	quitbutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 + 275);
	menushade->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	pauseicon->position.y = SHEIGHT / 2;
	mainmenubg->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	playbutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 + 150);
	highscoreLine->position = Point2(9999, SHEIGHT / 2);
	retrybutton->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	logo->position = Point2(SWIDTH / 2, SHEIGHT / 2 - 150);

	timeLine->position = Point2(50 , SHEIGHT - 50);

	menu->scale = Point2(1, 1.5);
	mainmenubutton->scale = Point2(0.75, 0.75);
	quitbutton->scale = Point2(0.75, 0.75);
	menushade->scale = Point2(5, 3);
	pauseicon->scale = Point2(1.5 ,1.5);
	mainmenubg->scale = Point2(5, 3);
	playbutton->scale = Point2(0.75, 0.75);
	retrybutton->scale = Point2(0.75, 0.75);
	logo->scale = Point2(0.3, 0.3);

	mainmenubutton->textbox->message("MAIN MENU", BLACK);
	quitbutton->textbox->message("QUIT", BLACK);
	menutext->message("MENU", BLACK);
	playbutton->textbox->message("PLAY", BLACK);
	retrybutton->textbox->message("RETRY", BLACK);

	mainmenubutton->textbox->position.x = mainmenubutton->position.x - 100;
	quitbutton->textbox->position.x = quitbutton->position.x - 675;
	menutext->position = Point2(mainmenubutton->position.x - 65, mainmenubutton->position.y - 525); 
	playbutton->textbox->position.x = playbutton->position.x -675;
	retrybutton->textbox->position = Point2(retrybutton->position.x - 690, retrybutton->position.y - 360);

	menutext->scale = Point2(1.5, 1.5);

	menu->position.x = 9999;
	mainmenubutton->position.x = 9999;
	menushade->position.x = 9999;
	pauseicon->position.x = 9999;
	scoreLine->position.x = 9999;
	retrybutton->position.x = 9999;

	text.push_back(scoreLine);
	std::stringstream scoretxt;
	scoretxt << points << std::endl;
	this->addChild(text[0]);
	text[0]->scale = Point2(1.2, 1.2);

	text.push_back(timeLine);
	std::stringstream timetxt;
	timetxt << time << std::endl;
	this->addChild(text[1]);

	text.push_back(highscoreLine);
	std::stringstream highscoretext;
	highscoretext << highscore << std::endl;
	this->addChild(text[2]);
	text[2]->scale = Point2(0.50, 0.50);
}

void DefaultScene::addColors()
{
		player->colors.push_back(RED);
		player->colors.push_back(ORANGE);
		player->colors.push_back(YELLOW);
		player->colors.push_back(GREEN);
		player->colors.push_back(BLUE);
}

void DefaultScene::SetupHexGrid() {

	float hexoffsetx = 0;
	float hexoffsety = 0;

	float counter = 0;

	//float hexwidth = SWIDTH;
	//float hexheight = SWIDTH;


	float spriteheight = 0.12;
	float spritewidth = spriteheight * 1.5;

	bool offsetline = false;

	for (int column = 0; column < 56; column++) {
		for (int rows = 0; rows < 21; rows++) {
			Hexagon* hexagon = new Hexagon(column, rows);
			hexagons.push_back(hexagon);
			this->addChild(hexagon);
			counter++;
			hexagon->scale = Point2(spritewidth, spriteheight);
			hexagon->position.x = hexagon->position.x + hexoffsetx;
			hexagon->position.y = hexagon->position.y + hexoffsety;

			hexoffsetx += 64;
		}

		//Check if the line needs an offset
		if (offsetline == false) {
			offsetline = true;
		}
		else {
			offsetline = false;
		}

		//Horizontal row is full, make a new column
		hexoffsety += 12.95;

		//If the line is a line that needs an offset, give it an offset
		if (offsetline) {
			hexoffsetx = 32;
		}
		else {
			hexoffsetx = 0;
		}
	}
}

void DefaultScene::AssignColors() 
{
	// ###############################################################
	// Color randomisation
	// ###############################################################


	if (randomtileMax < maxtargets)
	{
		int randomcolor = 0;


		randomTileCounter = rand() % (hexagons.size() - 1);
		randomcolor = rand() % (player->colors.size());

		if (hexagons[randomTileCounter]->sprite()->color == GRAY) 
		{
			hexagons[randomTileCounter]->addSprite("assets/hexagon_selected.tga");
			hexagons[randomTileCounter]->sprite()->color = player->colors[randomcolor];
			hexagons[randomTileCounter]->selected = true;
			randomtileMax++;
		}
	}
}

void DefaultScene::updatescore(int score) 
{
	text[0]->message("Time's up! Your score is " + std::to_string(score));
}

void DefaultScene::updateTime(double time)
{	
	std::stringstream timestream;
	timestream << std::fixed << std::setprecision(2) << time * 2;
	text[1]->message(timestream.str());

	if (abs(timer->seconds() + -15) < 0.1)
	{
		endScreen();
	}
}

void DefaultScene::checkHighscore()
{
	if (points > highscore)
	{
		highscore = points;
	} 

	text[2]->clearMessage();
	text[2]->message("This session's highscore is " + std::to_string(highscore));
}

void DefaultScene::enableMenu()
{
	if (!menuselected) {
		menu->position.x = SWIDTH / 2 + 300;
		menutext->position = Point2(-65, -165);
		mainmenubutton->position.x = SWIDTH / 2 + 300; 
		quitbutton->position.x = SWIDTH / 2 + 300;
		pauseicon->position.x = SWIDTH / 2 - 300;
		mainmenubutton->position.y = (SHEIGHT / 2);
		quitbutton->position.y = (SHEIGHT / 2) + 125;
		menushade->position = Point2(SWIDTH / 2, SHEIGHT / 2);
		scoreLine->clearMessage();
		timeLine->clearMessage();
		menuselected = true;
	}
	else 
	{
		menu->position.x = 9999;
		mainmenubutton->position.x = 9999;
		quitbutton->position.x = 9999;
		menushade->position.x = 9999;
		pauseicon->position.x = 9999;
		menuselected = false;
	}
}

void DefaultScene::checkInputs(float deltaTime)
{
	if (input()->getKeyDown(KeyCode::E))
	{
		if (colorCounter < player->colors.size() - 1)
		{
			colorCounter += 1;
			player->sprite()->color = player->colors[colorCounter];

		}
		else
		{
			colorCounter = 0;
			player->sprite()->color = player->colors[colorCounter];
		}
	}

	if (input()->getKeyDown(KeyCode::Q))
	{
		if (colorCounter > 0)
		{
			colorCounter -= 1;
			player->sprite()->color = player->colors[colorCounter];

		}
		else
		{
			colorCounter = player->colors.size() - 1;
			player->sprite()->color = player->colors[colorCounter];
		}
	}

	if (input()->getKeyDown(KeyCode::Space))
	{
		for (int h = 0; h < hexagons.size(); h++)
		{
			if (player->position == hexagons[h]->position)
			{
				if (player->sprite()->color == hexagons[h]->sprite()->color)
				{

					hexagons[h]->addSprite("assets/hexagon.tga");
					hexagons[h]->sprite()->color = GRAY;
					randomtileMax--;
					points++;
				}
				else
				{
					points--;
				}
			}
		}
	}

	//Get mouse coordinates
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();
	//Combine them into a Point2
	Point2 mousepos = Point2(mousex, mousey);

	//Find the nearest hexagon to the mouse
	size_t activeid = findnearest(mousepos);

	//Search through all hexagons 
	for (int j = 0; j < hexagons.size(); j++) {
		//If a the mouse hovers over a hexagon and the player clicks the left mouse button...
		if (hexagons[j] == hexagons[activeid] && input()->getMouseDown(0)) {
			//Let player calculate a path to the destination

			destination = hexagons[j];

			findpath = true;
		}

		//If the player just hovers, highlight it 
		if (hexagons[j] == hexagons[activeid] && hexagons[j]->selected == false) {
			hexagons[j]->Highlighted();
		}

		//If neither are true, then just keep it as a gray hexagon
		else
		{
			if (!hexagons[j]->selected)
			{
				hexagons[j]->Unselected();
			}
		}
	}
	// ###############################################################
	// Controls
	// ###############################################################
}

void DefaultScene::checkMenuButtons()
{
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();
	mousepos = Point2(mousex, mousey);

	if (mousepos.x > mainmenubutton->position.x - 100 && mousepos.x < mainmenubutton->position.x + 100 && mousepos.y > mainmenubutton->position.y - 50 && mousepos.y < mainmenubutton->position.y + 50)
	{
		if (input()->getMouseDown(0))
		{
			enableMenu();
			toggleMainMenu();
			endscreenselected = false;
		}
	}

	if (mousepos.x > retrybutton->position.x - 100 && mousepos.x < retrybutton->position.x + 100 && mousepos.y > retrybutton->position.y - 50 && mousepos.y < retrybutton->position.y + 50)
	{
		if (input()->getMouseDown(0))
		{
			retry();
			for (int p = 0; p < hexagons.size() - 1; p++)
			{
				hexagons[p]->addSprite("assets/hexagon.tga");
				hexagons[p]->sprite()->color = GRAY;
			}
			randomtileMax = 0;
			scoreLine->position.x = 9999;
			AssignColors();
		}
	}

	if (mousepos.x > playbutton->position.x - 100 && mousepos.x < playbutton->position.x + 100 && mousepos.y > playbutton->position.y - 50 && mousepos.y < playbutton->position.y + 50)
	{
		if (input()->getMouseDown(0))
		{
			toggleMainMenu();
			if (menuselected)
			{
				enableMenu();
			}
			for (int p = 0; p < hexagons.size() - 1; p++)
			{
				hexagons[p]->addSprite("assets/hexagon.tga");
				hexagons[p]->sprite()->color = GRAY;
			}
			randomtileMax = 0;
			scoreLine->position.x = 9999;
			AssignColors();
		}
	}

	else
	{
		if (mousepos.x > quitbutton->position.x - 100 && mousepos.x < quitbutton->position.x + 100 && mousepos.y > quitbutton->position.y - 50 && mousepos.y < quitbutton->position.y + 50)
		{
			if (input()->getMouseDown(0))
			{
				this->stop();
			}
		}
	}
}

void DefaultScene::pathfinding(float deltaTime)
{
	if (findpath)
	{
		Vector2 distance = player->position - destination->position;
		if (distance.getLength() > 5)
		{
			Vector2 path = player->NavigateToPoint(player->position, destination, deltaTime);
			size_t activeid = findnearest(player->position - player->NavigateToPoint(player->position, destination, deltaTime) * 5);

			for (int h = 0; h < hexagons.size(); h++) {
				if (activeid == h) {
					player->position = hexagons[activeid]->position;
				}

				if (!hexagons[h]->selected)
				{
					hexagons[h]->Unselected();
				}
			}
		}
		else
		{
			player->position = destination->position;
			findpath = false;
		}
	}
}

void DefaultScene::toggleTimer()
{	
	if (timer->paused()) 
	{
		timer->seconds() * -1;
		timer->unpause();
	}
	else
	{
		timer->pause();
	}
}

void DefaultScene::endScreen()
{
	menushade->position = Point2(SWIDTH / 2, SHEIGHT / 2);
	timeLine->clearMessage();
	scoreLine->position = Point2(SWIDTH / 2 - 475, SHEIGHT / 2 - 200);
	quitbutton->position = Point2(SWIDTH / 2 + 300, SHEIGHT / 2 + 150);
	mainmenubutton->position = Point2(SWIDTH / 2 - 300, SHEIGHT / 2 + 150);
	highscoreLine->position = Point2(SWIDTH / 2 - 250, SHEIGHT / 2 - 50);
	retrybutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 + 150);
	menutext->position.x = 9999;
	checkHighscore();
	endscreenselected = true;
}

void DefaultScene::toggleMainMenu()
{
	if (mainmenuselected || endscreenselected)
	{
		mainmenubg->position.x = 9999;
		quitbutton->position.x = 9999;
		playbutton->position.x = 9999;
		retrybutton->position.x = 9999;
		logo->position.x = 9999;
		timer->start();
		mainmenuselected = false;
	} 

	else
	{
		mainmenubg->position = Point2(SWIDTH / 2, SHEIGHT / 2);
		quitbutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 + 275);
		playbutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 + 150);
		logo->position = Point2(SWIDTH / 2, SHEIGHT / 2 - 150);
		timer->stop();
		points = 0;
		text[2]->clearMessage();
		mainmenuselected = true;
	}

	if (endscreenselected)
	{
		pauseicon->position.x = 9999;
		highscoreLine->position.x = 9999;
		menu->position.x = 9999;
		mainmenubutton->position.x = 9999;
		menushade->position.x = 9999;
		mainmenubg->position = Point2(SWIDTH / 2, SHEIGHT / 2);
		quitbutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 + 275);
		playbutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 + 150);
		logo->position = Point2(SWIDTH / 2, SHEIGHT / 2 - 150);
		timer->stop();
		points = 0;
		text[2]->clearMessage();
		mainmenuselected = true;
	}
}

void DefaultScene::retry()
{
	points = 0;
	mainmenubg->position.x = 9999;
	quitbutton->position.x = 9999;
	playbutton->position.x = 9999;
	retrybutton->position.x = 9999;
	highscoreLine->position.x = 9999;
	mainmenubutton->position.x = 9999;
	scoreLine->position.x = 9999;
	menushade->position.x = 9999;
	timer->stop();
	timer->start();
	endscreenselected = false;
}

void DefaultScene::update(float deltaTime)
{


	if (!menuselected && !mainmenuselected && !endscreenselected)
	{
		checkInputs(deltaTime);
		pathfinding(deltaTime);
		updatescore(points);
		updateTime(abs(timer->seconds() + -15));
		toggleTimer();
		checkMenuButtons();

		if (randomtileMax < maxtargets)
		{
			AssignColors();
		}
		if (input()->getKeyUp(KeyCode::Escape))
		{
			enableMenu();
		}
	}

	else if (menuselected && !mainmenuselected && !endscreenselected)
	{
		timer->pause();

		if (input()->getKeyUp(KeyCode::Escape))
		{
			enableMenu();
		}
		checkMenuButtons();
	}

	if (!menuselected && mainmenuselected && !endscreenselected)
	{
		timer->pause();
		checkMenuButtons();
	}

	if (menuselected && mainmenuselected && !endscreenselected)
	{
		timer->pause();
		checkMenuButtons();
	}

	if (!menuselected && !mainmenuselected && endscreenselected)
	{
		timer->stop();
		timer->pause();
		checkMenuButtons();
	}


	//std::cout <<  "menuselected: " <<menuselected << ", mainmenuselected: " << mainmenuselected << ", endscreenselected: " << endscreenselected << std::endl;
}
