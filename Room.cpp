#include "Room.h"

Room::Room(std::string roomNameP, std::string previousRoomNameP, std::list<std::string> nextRoomsNamesP, std::list<std::string> objects, std::string storyTextP, std::string bgfilePath)
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
	storyText = "default text";
	objectList = { "Red door", "Red key", "lamp" };
}


Room::~Room()
{
}