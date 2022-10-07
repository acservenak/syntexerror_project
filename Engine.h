#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "room.h"
#include "RoomManager.h"
#include "InputManager.h"

class Engine
{
private:
	sf::RenderWindow window;
	RoomManager Rmanager;
	InputManager Imanager;
	sf::Text text;
	std::vector<Room> roomList;
public:
	Engine(int height, int width); 
	void start(); 
};













