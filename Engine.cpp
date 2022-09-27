#include "Engine.h"
#include "RoomManager.h"
#include "tinyxml2.h"

Engine::Engine(int height, int weight)
{
	window.create(sf::VideoMode(height, weight), "TextGame", sf::Style::Close | sf::Style::Titlebar);
	tinyxml2::XMLDocument doc;
	Room test;
	

	if (doc.LoadFile( "rooms.xml" ) == false )
	{
		//tinyxml2::XMLNode* pRoot = doc.RootElement();
		//tinyxml2::XMLNode* pR2 = pRoot->FirstChild();
		//tinyxml2::XMLElement* pElement = pR2->FirstChildElement("name");
		//std::string roomname = pElement->Attribute("name"); // doc.FirstChildElement("rooms")->FirstChildElement("room")->FirstChildElement("name")->GetText(); //pElement->Attribute("name");
		//std::cout << roomname;
		tinyxml2::XMLElement* pRoot = doc.FirstChildElement("rooms");
		tinyxml2::XMLElement* FirstRoom = pRoot->FirstChildElement("room");
		std::string name = FirstRoom->FirstChildElement("name")->GetText();
		std::string prevRoomName = FirstRoom->FirstChildElement("previousroomname")->GetText();
		std::list<std::string> nextRoomsNames = {};
		std::list<std::string> roomObjects = {};
		tinyxml2::XMLElement* roomnames = FirstRoom->FirstChildElement("nextrooms");
		for (tinyxml2::XMLElement* nextRoomName = roomnames->FirstChildElement("roomname"); nextRoomName != NULL; nextRoomName = nextRoomName->NextSiblingElement())
		{
			nextRoomsNames.push_back(nextRoomName->GetText());
		}
		tinyxml2::XMLElement* objects = FirstRoom->FirstChildElement("objects");
		for (tinyxml2::XMLElement* object = objects->FirstChildElement("object"); object != NULL; object = object->NextSiblingElement())
		{
			roomObjects.push_back(object->GetText());
		}
		std::string storyText = FirstRoom->FirstChildElement("text")->GetText();
		std::string bgfilepath = FirstRoom->FirstChildElement("bgfilename")->GetText();
		test = Room(name, prevRoomName, nextRoomsNames, roomObjects, storyText, bgfilepath);
		/*for (

			auto* pListElement = pRoot->FirstChildElement("room");
			pListElement != nullptr;
			pListElement = pListElement->NextSiblingElement("room"))
		{
			std::string name = pListElement->Attribute("name");
			std::string prevroomname = pListElement->Attribute("previousroomname");
			std::cout << name << std::endl;
		}*/
	}
	else
	{
		std::cout << "Cant load file";
	}


	Rmanager = RoomManager();
	Rmanager.setCurrentRoom(test);
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
	playerText.setPosition(50, 50);

	sf::Text result("", font, 24);
	result.setPosition(500, 500);
	
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			std::string plString = playerInput.toAnsiString();
			std::transform(plString.begin(), plString.end(), plString.begin(),
				[](unsigned char c) { return std::tolower(c); });
			if (plString == "use door")
			{
				//Rmanager.setCurrentRoom();
				text.setString(Rmanager.getCurrentRoom().getStoryString());
				playerInput.clear();
				result.setString("");
			}
			else
			{
				result.setString("You cant do that");
			}
			
		}	

		sf::Event event;

		while (window.pollEvent(event))
		{
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
				if (event.text.unicode == '\b'){
					if (playerInput.getSize() > 0)
					{
						playerInput.erase(playerInput.getSize() - 1, 1);
						playerText.setString(playerInput);
					}
				}
				else
				{

					std::cout << event.text.unicode;
					playerInput += event.text.unicode;
					playerText.setString(playerInput);
				}
				
				break;
			}
			
			}
			
		}
		window.clear();
		window.draw(result);
		window.draw(text);
		window.draw(playerText);
		window.display();
		
	}
}

