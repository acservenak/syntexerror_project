#pragma once
#include "Room.h"

class RoomManager
{
public:
	RoomManager();
	~RoomManager();
	Room getCurrentRoom() {
		return currentRoom;
	}
	void setCurrentRoom(Room pushedRoom) {
		currentRoom = pushedRoom;
	}
private:
	Room currentRoom;
};


