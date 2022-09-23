#include "Room.h"

Room::Room(std::string stext)
{
	storyText = stext;
	objectList = { "Red door", "Red key", "lamp" };
}

Room::Room()
{
	storyText = "default text";
	objectList = { "Red door", "Red key", "lamp" };
}


Room::~Room()
{
}