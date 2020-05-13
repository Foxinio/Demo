#pragma once

#include <vector>
#include <Windows.h>

namespace Interface {

	enum MenuElement {
		MenuChoosable,
		MenuChangebleValue,
		MenuChangableList,
		MenuChangableBool,
		MenuHeader
	};

	enum Colors {
		Black,
		Blue,
		Green,
		Cyan,
		Red,
		Magenta,
		Brown,
		LightGray,
		DarkGray,
		LightBlue,
		LightGreen,
		LightCyan,
		LightRed,
		LightMagenta,
		Yellow,
		White
	};

	class MenuObject {
	protected:
		void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	public:
		MenuElement objectType = MenuElement::MenuChoosable;
		std::string name;

		virtual ~MenuObject();
		virtual void drawSimple();
		virtual void drawChoosen();
	};

	class Choosable : public MenuObject {
	public:
		Choosable(std::string _name);

		void drawSimple();
		void drawChoosen();
	};

	class Changable : public MenuObject {
	public:
		int value = 0;
		virtual void sub();
		virtual void add();
	};

	class ChangableValue : public Changable {
		int minValue = 0;
		int maxValue = 0;
		int interval = 1;
	public:

		ChangableValue(std::string _name, int defaultValue, int _minValue, int _maxValue, int _interval);

		void sub();
		void add();

		void drawSimple();
		void drawChoosen();
	};

	class ChangableList : public Changable {
		int arrayLenght;
		std::vector<std::string> choosingArray;
	public:

		ChangableList(std::string _name, std::vector<std::string> _choosingArray, int defaultValue);

		std::vector<std::string> GetArray();

		void sub();
		void add();

		void drawSimple();
		void drawChoosen();
	};

	class ChangableBool : Changable {
	public:
		bool boolValue;

		ChangableBool(std::string _name, bool defaultValue);

		void sub();
		void add();

		void drawSimple();
		void drawChoosen();
	};

	class Header : MenuObject {
	public:
		Header(std::string _name);

		void drawSimple();
		void drawChoosen();
	};

	enum Keys {
		UpArrow = 72,
		DownArrow = 80,
		RightArrow = 77,
		LeftArrow = 75,
		Enter = 13,
		Escape = 27,
		Space = 32
	};

	class MenuHandler {
	public:
		std::vector<MenuObject*> collection;

		MenuHandler(unsigned int lenght);

		MenuHandler(std::initializer_list<MenuObject*> l);

		~MenuHandler();

		int Run();
	};
};
