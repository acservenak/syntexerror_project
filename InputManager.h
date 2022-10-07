#pragma once
#include <list>
#include <string>
#include "RoomManager.h"
#include "Room.h"


enum  Actions
{
	GOBACK = 1, 
	GOTO = 2,
	USE = 3,
	PICKUP = 4,
};



class InputManager
{
public: InputManager(RoomManager RManager); //TODO:add playermanager; 
		InputManager();
		~InputManager();
		std::vector<Actions> getPossibleActions();
		std::list<std::string> getPossibleTargetRooms();
		std::list<Object> getPossibleTargetObjects();
private:
	std::vector<Actions> possibleActions;
	std::list<std::string> possibleTargetRooms;
	std::list<Object> possibleTargetObjects;

};

