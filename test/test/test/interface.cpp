#include "pch.h"

#include "interface.h"
#include <string>
#include <iostream>
#include <conio.h>



namespace Interface {
	MenuObject::~MenuObject() { }
	void MenuObject::drawSimple() {};
	void MenuObject::drawChoosen() {};

	Choosable::Choosable(std::string _name)
	{
		name = _name;
		objectType = MenuElement::MenuChoosable;
	}

	void Choosable::drawSimple() {
		std::cout << " " << name << " " << std::endl;
	}
	void Choosable::drawChoosen() {
		SetConsoleTextAttribute(hConsole, Green);
		std::cout << " " << name << " " << std::endl;
		SetConsoleTextAttribute(hConsole, White);
	}


	void Changable::sub() {};
	void Changable::add() {};

	ChangableValue::ChangableValue(std::string _name, int defaultValue, int _minValue, int _maxValue, int _interval) {
			name = _name;
			objectType = MenuElement::MenuChangebleValue;
			interval = _interval;
			value = defaultValue;
			minValue = _minValue;
			maxValue = _maxValue;
		}

	void ChangableValue::sub() {
		value -= interval;
		if (value < minValue)
			value = maxValue;
	}
	void ChangableValue::add() {
		value += interval;
		if (value > maxValue)
			value = minValue;
	}

	void ChangableValue::drawSimple() {
		std::cout << " " << name << "	  " << value << "  " << std::endl;
	}
	void ChangableValue::drawChoosen() {
		SetConsoleTextAttribute(hConsole, Green);
		std::cout << " " << name << "	< " << value << " >" << std::endl;
		SetConsoleTextAttribute(hConsole, White);
	}

	ChangableList::ChangableList(std::string _name, std::vector<std::string> _choosingArray, int defaultValue) {
		name = _name;
		objectType = MenuElement::MenuChangableList;
		value = defaultValue >= 0 ? defaultValue < _choosingArray.size() ? defaultValue : _choosingArray.size() - 1 : 0;
		choosingArray = _choosingArray;
	}

	std::vector<std::string> ChangableList::GetArray() {
		return choosingArray;
	}

	void ChangableList::sub() {
		value -= 1;
		if (value < 0)
			value = choosingArray.size() - 1;
	}
	void ChangableList::add() {
		value += 1;
		if (value > choosingArray.size() - 1)
			value = 0;
	}

	void ChangableList::drawSimple() {
		std::cout << " " << name << "	  " << choosingArray[value] << "  " << std::endl;
	}
	void ChangableList::drawChoosen() {
		SetConsoleTextAttribute(hConsole, Green);
		std::cout << " " << name << "	< " << choosingArray[value] << " >" << std::endl;
		SetConsoleTextAttribute(hConsole, White);
	}


	ChangableBool::ChangableBool(std::string _name, bool defaultValue) {
		name = _name;
		objectType = MenuElement::MenuChangableBool;
		boolValue = defaultValue;
	}

	void ChangableBool::sub() {
		boolValue = !boolValue;
	}
	void ChangableBool::add() {
		boolValue = !boolValue;
	}

	void ChangableBool::drawSimple() {
		if (boolValue)
			std::cout << " " << name << "	  YES  " << std::endl;
		else
			std::cout << " " << name << "	  NO  " << std::endl;
	}
	void ChangableBool::drawChoosen() {
		SetConsoleTextAttribute(hConsole, Green);
		if (boolValue)
			std::cout << " " << name << "	< YES >" << std::endl;
		else
			std::cout << " " << name << "	< NO >" << std::endl;
		SetConsoleTextAttribute(hConsole, White);
	}


	Header::Header(std::string _name) {
		name = _name;
		objectType = MenuElement::MenuHeader;
	}

	void Header::drawSimple() {
		std::cout << "	" << name << " " << std::endl << std::endl;
	}
	void Header::drawChoosen() {}

	MenuHandler::MenuHandler(std::initializer_list<MenuObject*> l) {
		collection = l;
	}
	MenuHandler::~MenuHandler() {
		for (size_t i = 0; i < collection.size(); i++) {
			delete collection[i];
		}
	}

	int MenuHandler::run() {
		unsigned int index = 0;
		Keys keyPressed;
		if (collection[index]->objectType == MenuElement::MenuHeader) {
			index++;
		}
		while (true) {
			draw(index);
			switch (getKey()) {
			case Keys::DownArrow:
				index++;
				index = (index + collection.size()) % collection.size();
				if (collection[index]->objectType == MenuElement::MenuHeader) {
					index++;
				}
				break;
			case Keys::UpArrow:
				index--;
				if (collection[index]->objectType == MenuElement::MenuHeader) {
					index--;
				}
				index = (index + collection.size()) % collection.size();
				break;
			case Keys::RightArrow:
				if (collection[index]->objectType != MenuElement::MenuChoosable && collection[index]->objectType != MenuElement::MenuHeader) {
					auto temp = dynamic_cast<Changable*>(collection[index]);
					temp->add();
				}
				break;
			case Keys::LeftArrow:
				if (collection[index]->objectType != MenuElement::MenuChoosable && collection[index]->objectType != MenuElement::MenuHeader) {
					auto temp = dynamic_cast<Changable*>(collection[index]);
					temp->sub();
				}
				break;
			case Keys::Enter:
				if (collection[index]->objectType == MenuElement::MenuChoosable) {
					return index;
				}
				break;
			case Keys::Escape:
				return collection.size() - 1;
			default:
				break;
			}
		}
	}

	Keys MenuHandler::getKey() {
		int keyPressed = _getch();
		if (keyPressed == 0 || keyPressed == 224) {
			keyPressed = _getch();
		}
		return (Keys)keyPressed;
	}

	void MenuHandler::draw(int index) {
		system("cls");
		for (int i = 0; i < collection.size(); i++) {
			if (i == index) {
				collection[i]->drawChoosen();
			}
			else {
				collection[i]->drawSimple();
			}
		}
	}
};