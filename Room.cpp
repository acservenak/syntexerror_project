#include "Room.h"

Room::Room(std::string roomNameP, std::string previousRoomNameP, std::list<std::string> nextRoomsNamesP, std::vector<Object> objects, std::string storyTextP, std::string bgfilePath)
{
	roomName = roomNameP;
	previousRoomName = previousRoomNameP;
	nextRoomsNames = nextRoomsNamesP;
	objectList = objects;
	storyText = storyTextP;
	bgFileName= bgfilePath;

}

Room::Room()
{
}


Room::~Room()
{
}