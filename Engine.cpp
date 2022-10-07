#include "Engine.h"
#include "RoomManager.h"
#include "tinyxml2.h"
#include "InputManager.h"
#include "object.h"

Engine::Engine(int height, int weight)
{
	window.create(sf::VideoMode(height, weight), "TextGame", sf::Style::Close | sf::Style::Titlebar);
	tinyxml2::XMLDocument doc;
	roomList = {};

	if (doc.LoadFile( "rooms.xml" ) == false )
	{
		tinyxml2::XMLElement* pRoot = doc.FirstChildElement("rooms");
		for (tinyxml2::XMLElement* currentRroom = pRoot->FirstChildElement("room"); currentRroom != NULL; currentRroom = currentRroom->NextSiblingElement())
		{
			std::string name = currentRroom->FirstChildElement("name")->GetText();
			std::string prevRoomName = currentRroom->FirstChildElement("previousroomname")->GetText();
			std::list<std::string> nextRoomsNames = {};
			std::vector<Object> roomObjects = {};
			tinyxml2::XMLElement* roomnames = currentRroom->FirstChildElement("nextrooms");
			for (tinyxml2::XMLElement* nextRoomName = roomnames->FirstChildElement("roomname"); nextRoomName != NULL; nextRoomName = nextRoomName->NextSiblingElement())
			{
				nextRoomsNames.push_back(nextRoomName->GetText());
			}
			tinyxml2::XMLElement* objects = currentRroom->FirstChildElement("objects");
			for (tinyxml2::XMLElement* object = objects->FirstChildElement("object"); object != NULL; object = object->NextSiblingElement())
			{
				if (object->GetText() != "empty")
				{
					std::cout << object->GetText() << std::endl;
					Object currentObject = Object(object->GetText());
					roomObjects.push_back(currentObject);
				}
				
			}
			std::string storyText = currentRroom->FirstChildElement("text")->GetText();
			std::string bgfilepath = currentRroom->FirstChildElement("bgfilename")->GetText();
			roomList.push_back(Room(name, prevRoomName, nextRoomsNames, roomObjects, storyText, bgfilepath));
		}
	}
	else
	{
		std::cout << "Can't load file";
	}

	Rmanager = RoomManager();
	Rmanager.setCurrentRoom(roomList.front());
	Imanager = InputManager(Rmanager);
}

void Engine::start()
{
	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		std::cout << "can't load font" << std::endl;
	}
	else
	{
		text.setFont(font);
	}
	// set the string to display
	/*std::cout << text.getString().toAnsiString();*/
	text.setString(Rmanager.getCurrentRoom().getStoryString());
	// set the character size
	text.setCharacterSize(24); // in pixels

	// set the color
	text.setFillColor(sf::Color::White);
	text.setPosition(20, 20);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::String playerInput;
	sf::Text playerText("", font, 24);
	playerText.setCharacterSize(24); // in pixels

	// set the color
	playerText.setFillColor(sf::Color::White);
	playerText.setPosition(50, 800);

	sf::Text result("", font, 24);
	result.setPosition(1300, 800);
	sf::CircleShape triangle(60.f, 3);
	triangle.setPosition(30, 755);
	triangle.setRotation(90.f);
	bool isInKeypad = false;

	while (window.isOpen())	
	{
		//eventmanagement with commands ami kitörlődött
			
		sf::Event event;
		while (window.pollEvent(event))
		{
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				std::string plString = playerInput.toAnsiString();
				std::string tempErase = plString + " ";
				std::transform(tempErase.begin(), tempErase.end(), tempErase.begin(),
					[](unsigned char c) { return std::tolower(c); });
				std::string delimiter = " ";
				size_t pos = 0;
				std::string temp;
				std::vector<std::string> command = {};
				int currentRoomIndex = -1;
				while ((pos = tempErase.find(delimiter)) != std::string::npos) {
					temp = tempErase.substr(0, pos);
					command.push_back(temp);
					tempErase.erase(0, pos + delimiter.length());
				}
				
				if (Rmanager.getCurrentRoom().getRoomName() == "Mail" and plString == "")
				{
					Rmanager.setCurrentRoom(roomList[1]);
					text.setString(Rmanager.getCurrentRoom().getStoryString());
				}
				else if (plString != "") {
					
						for (int i = 0; i < roomList.size(); i++)
						{
							if (roomList[i].getRoomName() == Rmanager.getCurrentRoom().getRoomName())
							{
								currentRoomIndex = i;
							}
						}
						if (isInKeypad == true and command[0] == "7823")
						{
							isInKeypad = false;
							result.setString("Opened the gate");
							
							roomList[currentRoomIndex].getObjectList()->front().setUsed(true);
						} 
						else if (command[0] == "use")
						{
							if (command[1] == "keypad")
							{
								isInKeypad = true;
								result.setString("Enter the code!");
								
							}
							else if (command.size() > 2)
							{
								if (command[2] == "key")
								{
									std::list<Object> interactable = Imanager.getPossibleTargetObjects();
									int j = 0;
									for (auto object : interactable)
									{
										if (object.getUsageParam() == command[1] + " " + command[2])
										{
											std::vector<Object> vector = * roomList[currentRoomIndex].getObjectList();
											vector[j].setUsed(true);
											result.setString("You have opened a lock");

										}
										j++;
									}
								}
								
							}

						}
						else if (command[0] == "go") {

						}
						else {
							result.setString("You can't do that");
						}
					
					
				}
			}
			else {
				switch (event.type)
				{
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
				case sf::Event::TextEntered:
				{
					//if (event.type == sf::Event::TextEntered) {
					//	if (Event.Text.Unicode == '\b') { // handle backspace explicitly
					//		playerInput.erase(playerInput.size() - 1, 1);
					//	}
					//	else { // all other keypresses
					//		playerInput += static_cast<char>(Event.Text.Unicode);
					//	}
					//}
					if (event.text.unicode == '\b') {
						if (playerInput.getSize() > 0)
						{
							playerInput.erase(playerInput.getSize() - 1, 1);
							playerText.setString(playerInput);
						}
					}
					else
					{
						if (event.text.unicode == '\r')
						{

						}
						else {
							std::cout << event.text.unicode;
							playerInput += event.text.unicode;
							playerText.setString(playerInput);
						}

					}

					break;
				}

				}
			}

			
			
		}
		window.clear();
		window.draw(triangle);
		window.draw(result);
		window.draw(text);
		window.draw(playerText);
		window.display();
		
	}
}

