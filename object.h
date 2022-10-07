#pragma once
#include <string>
class Object
{
public:
	Object(std::string nameP, std::string usageParamP, bool isUsed);
	Object(std::string xmlString);
	Object();
	~Object();
	void setUsed(bool param) {
		isUsed = param;
	}
	std::string getName() {
		return name;
	}
	std::string getUsageParam() {
		return usageParam;
	}
	bool getIsUsed() {
		return isUsed;
	}

private:
	std::string name;
	std::string usageParam;
	bool isUsed;
};

