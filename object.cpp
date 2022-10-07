#include "object.h"

#include <vector>

Object::Object(std::string nameP, std::string usageParamP, bool isUsed)
{
	name = nameP;
	usageParam = usageParamP;
	isUsed = isUsed;
}
Object::Object(std::string xmlString)
{
	std::string delimiter = ";";
	size_t pos = 0;
	std::string temp;
	std::vector<std::string> attr = {};
	while ((pos = xmlString.find(delimiter)) != std::string::npos) {
		temp = xmlString.substr(0, pos);
		attr.push_back(temp);
		xmlString.erase(0, pos + delimiter.length());
	}
	name = attr[0];
	usageParam = attr[1];
	isUsed = false;
}
Object::Object()
{
}

Object::~Object()
{
}