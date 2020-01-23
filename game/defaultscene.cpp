/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
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
	findpath = false;
	destination = new Hexagon(0,0);
	menutext = new Text();
	menushade = new Basicentity();

	
	this->addChild(player);
	player->position = hexagons[0]->position;
	player->scale = hexagons[0]->scale;

	colorCounter = 0;
	addColors();

	randomTileCounter = 0;
	randomtileMax = 0;
	srand(time(NULL));

	points = 0;
	maxtargets = 10;

	UISetup();
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
}

void DefaultScene::UISetup()
{
	this->addChild(menushade);
	this->addChild(menu);
	this->addChild(mainmenubutton);
	this->addChild(quitbutton);
	mainmenubutton->addChild(menutext);


	menu->addSprite("assets/color.tga");
	menushade->addSprite("assets/color.tga");
	menushade->sprite()->color = BLACK;
	menushade->sprite()->color.a = 150;

	menu->position.y = SHEIGHT / 2;
	mainmenubutton->position.y = SHEIGHT / 2;
	quitbutton->position.y = SHEIGHT / 2;
	menushade->position = Point2(SWIDTH / 2, SHEIGHT / 2);

	menu->scale = Point2(1, 1.5);
	mainmenubutton->scale = Point2(0.75, 0.75);
	quitbutton->scale = Point2(0.75, 0.75);
	menushade->scale = Point2(5, 3);

	mainmenubutton->textbox->message("MAIN MENU", BLACK);
	quitbutton->textbox->message("QUIT", BLACK);
	menutext->message("MENU", BLACK);

	mainmenubutton->textbox->position.x = mainmenubutton->position.x - 100;
	quitbutton->textbox->position.x = quitbutton->position.x - 40;
	menutext->position = Point2(mainmenubutton->position.x - 65, mainmenubutton->position.y - 525);

	menutext->scale = Point2(1.5, 1.5);

	menu->position.x = 9999;
	mainmenubutton->position.x = 9999;
	quitbutton->position.x = 9999;
	menushade->position.x = 9999;
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

		hexagons[randomTileCounter]->addSprite("assets/hexagon_selected.tga");
		hexagons[randomTileCounter]->sprite()->color = player->colors[randomcolor];
		hexagons[randomTileCounter]->selected = true;

		randomtileMax++;
	}
}

void DefaultScene::updatescore(int score) {
	Text* line = new Text();
	line->scale = Point2(1.0f, 1.0f);
	line->position = Point2(SWIDTH / 2 - 125, 50);
	text.push_back(line);
	std::stringstream fpstxt;
	fpstxt << "Score: " << score << std::endl;
	text[0]->message(fpstxt.str());
	this->addChild(text[0]);
}

void DefaultScene::enableMenu()
{
	if (menu->position.x != SWIDTH / 2) {
		menu->position.x = SWIDTH / 2;
		mainmenubutton->position.x = SWIDTH / 2;
		quitbutton->position.x = SWIDTH / 2;

		mainmenubutton->position.y = (SHEIGHT / 2);
		quitbutton->position.y = (SHEIGHT / 2) + 125;
		menushade->position = Point2(SWIDTH / 2, SHEIGHT / 2);
		menuselected = true;
	}
	else {
		menu->position.x = 9999;
		mainmenubutton->position.x = 9999;
		quitbutton->position.x = 9999;
		menushade->position.x = 9999;
		menuselected = false;
	}
}

void DefaultScene::update(float deltaTime)
{
	// ###############################################################
	// Controls
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		//this->stop();
		enableMenu();
	}

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
					std::cout << points << std::endl;
				}
			}
		}
	}

	//Get mouse coordinates
	int mousex = input()->getMouseX();
	int mousey = input()->getMouseY();
	//Combine them into a Point2
	Point2 mousepos = Point2(mousex, mousey);

	if (!menuselected) {
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
	}
	// ###############################################################
	// Controls
	// ###############################################################

	// ###############################################################
	// Pathfinding
	// ###############################################################

	if (findpath) 
	{
		//This needs work
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

	// ###############################################################
	// Pathfinding
	// ###############################################################	
	if (randomtileMax < maxtargets)
	{
		AssignColors();
	}

	updatescore(points);
}
