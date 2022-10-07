#include "InputManager.h"

InputManager::InputManager() {
	possibleActions = { };
	possibleTargetRooms = { };
}
InputManager::~InputManager() {}
InputManager::InputManager(RoomManager RManager) {
	Room currentRoom = RManager.getCurrentRoom();
	if (currentRoom.getPreviousName() != "empty")
	{
		possibleActions.push_back(Actions::GOBACK);
	}
	std::vector<Object> objects =*currentRoom.getObjectList();
	std::list<std::string> nextrooms = currentRoom.getNextNames();
	for (std::string room : nextrooms)
	{
		std::string tempS = room;
		std::string delimiter = ";";
		size_t pos = 0;
		std::string temp;
		std::vector<std::string> params = {};
		while ((pos = tempS.find(delimiter)) != std::string::npos) {
			temp = tempS.substr(0, pos);
			params.push_back(temp);
			tempS.erase(0, pos + delimiter.length());
		}

		if (params[1] == "no")
		{
			possibleTargetRooms.push_back(params[0]);
		}
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i].getName() == params[1])
			{
				if (objects[i].getIsUsed() == true)
				{
					possibleTargetRooms.push_back(params[0]);
				}
			}
		}
	
	}
	for (Object object : objects)
	{
		possibleTargetObjects.push_back(object);
		if (object.getName().find("key") > 0 && object.getName().find("key") < 15 && object.getName().find("keypad") > 100 )
		{
			possibleActions.push_back(Actions::PICKUP);
		}
		if (object.getName().find("lamp") > 0 && object.getName().find("lamp") < 15)
		{
			possibleActions.push_back(Actions::PICKUP);
		}
	}
	if (nextrooms.front() != "empty")
	{
		possibleActions.push_back(Actions::GOTO);
	}
	if (objects.front().getName() != "empty")
	{
		possibleActions.push_back(Actions::USE);
	}
	
}
std::vector<Actions> InputManager::getPossibleActions() {
	return this->possibleActions ;
}
std::list<std::string> InputManager::getPossibleTargetRooms() {
	return this->possibleTargetRooms;
}
std::list<Object> InputManager::getPossibleTargetObjects() {
	return this->possibleTargetObjects;
}
