#include "pch.h"

#include "interface.h"
#include <iostream>
#include <string>
#include <conio.h>

int main()
{
	Interface::ChangableValue* changableValue = new Interface::ChangableValue("World Size", 100, 10, 1000, 10);
	Interface::ChangableList* changableList = new Interface::ChangableList("Difficulty", { "Easy", "Intermediate", "Difficult" }, 1);
	Interface::MenuHandler handler = Interface::MenuHandler(
		{
			new Interface::Header("Main Menu"),
			changableValue,
			changableList,
			new Interface::ChangableBool("Test-mode", true),
			new Interface::Choosable("Accept"),
			new Interface::Choosable("Return")
		}
	);


	if (handler.run() == 4) {
		system("cls");
		auto Array = changableList->GetArray();
		std::cout << "You've choosen: " << std::endl;
		std::cout << changableValue->name << ": " <<  changableValue->value << std::endl;
		std::cout << changableList->name << ": " << Array[changableList->value] << std::endl;
		std::cout << handler.collection[3]->name << ": " <<  dynamic_cast<Interface::ChangableBool*>(handler.collection[3])->boolValue ? "ON" : "OFF";
	}
	else {
		system("cls");
		std::cout << "You didn't choose anything." << std::endl;
	}
}