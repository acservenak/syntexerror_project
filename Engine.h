#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "room.h"
#include "RoomManager.h"

class Engine
{
private:
	sf::RenderWindow window;
	RoomManager Rmanager;
	sf::Text text;
	std::list<Room> roomList;
public:
	Engine(int height, int width); 
	void start(); 
};













