#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	startbutton = new MyEntity();
	optionsbutton = new MyEntity();
	creditsbutton = new MyEntity();

	this->addChild(startbutton);
	this->addChild(optionsbutton);
	this->addChild(creditsbutton);

	startbutton->position = Point2(SWIDTH / 2, SHEIGHT / 2 - 100);
	optionsbutton->position = Point2(SWIDTH / 2 - 100, SHEIGHT / 2 + 50);
	creditsbutton->position = Point2(SWIDTH / 2 + 100, SHEIGHT / 2 + 50);
}

MyScene::~MyScene()
{
	this->removeChild(startbutton);
	this->removeChild(optionsbutton);
	this->removeChild(creditsbutton);

	delete startbutton;
	delete optionsbutton;
	delete creditsbutton;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Register clicks
	// ###############################################################
	if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		std::cout << "Clickety click" << std::endl;
	}
}
