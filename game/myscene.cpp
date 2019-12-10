#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	myentity = new MyEntity();
	this->addChild(myentity);
	myentity->position = Point2(SWIDTH / 2, SHEIGHT / 2);
}


MyScene::~MyScene()
{
	this->removeChild(myentity);
	delete myentity;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	if (input()->getMouseDown(GLFW_MOUSE_BUTTON_1)) {
		std::cout << "Clicked!" << std::endl;
	}
}
