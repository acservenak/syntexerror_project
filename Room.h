#pragma once
#include <string>
#include <list>
#include <vector>
#include "object.h"

class Room
{
public:
	Room(std::string roomName, std::string previousRoomName, std::list<std::string> nextRoomsNames, std::vector<Object> objects, std::string storyText, std::string bgfilePath);
	Room();
	~Room();
	std::string getStoryString() {
		return storyText;
	};
	std::string getPreviousName() {
		return previousRoomName;
	};
	std::list<std::string> getNextNames() {
		return nextRoomsNames;
	};
	std::vector<Object>* getObjectList() {
		return &objectList;
	};
	std::string getRoomName() {
		return roomName;
	};
	std::string bgfilePath() {
		return bgFileName;
	};
	void setObjectUsedInList(std::string objectName) {
		for (auto object: objectList)
		{
			if (object.getName() == objectName)
			{
				object.setUsed(true);
			}
		}
	};

private:
	std::string roomName;
	std::string previousRoomName;
	std::list<std::string> nextRoomsNames;
	std::vector<Object> objectList;
	std::string storyText;
	std::string bgFileName;

	
};


