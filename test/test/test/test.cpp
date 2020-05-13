
//#ifndef PCH_REFERENCE
//#define PCH_REFERENCE
#include "pch.h"
//#endif

#include "interface.h"
#include <iostream>
#include <string>
#include <conio.h>

#define LOG(x) std::cout << x << std::endl

int main()
{
	Interface::ChangableValue* changableValue = new Interface::ChangableValue("World Size", 100, 10, 1000, 10);
	Interface::ChangableList* changableList = new Interface::ChangableList("Difficulty", { "Easy", "Intermediate", "Difficult" }, 1);
	Interface::MenuHandler handler = Interface::MenuHandler(
		{
			new Interface::Header("Main Menu"),
			changableValue,
			changableList,
			new Interface::ChangableBool("PvP", true),
			new Interface::Choosable("Accept"),
			new Interface::Choosable("Return")
		}
	);

	if (handler.Run() == 4) {
		auto Array = changableList->GetArray();
		LOG("You've choosen: ");
		LOG(std::string(std::string("World Size: ") + std::to_string(changableValue->value)));
		LOG(std::string(std::string("Difficulty: ") + Array[changableList->value]));
		LOG(std::string(std::string("PvP: ") + (dynamic_cast<Interface::ChangableBool*>(handler.collection[3])->boolValue ? "ON" : "OFF")));
	}
	else {
		LOG("You didn't choose anything.");
	}
}