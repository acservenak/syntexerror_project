#pragma once
#include <list>
#include <string>

class Room
{
public:
	Room(std::string roomName, std::string previousRoomName, std::list<std::string> nextRoomsNames, std::list<std::string> objects, std::string storyText, std::string bgfilePath);
	Room();
	~Room();
	std::string getStoryString() {
		return storyText;
	};

private:
	std::string roomName;
	std::string previousRoomName;
	std::list<std::string> nextRoomsNames;
	std::list<std::string> objectList;
	std::string storyText;
	std::string bgFileName;

	
};


