//
// Created by ianpo on 19/07/2023.
//

#pragma once

// Imported from glfw3.h
namespace PC {
	enum class Mouse : int
	{
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,
		Last = Button8,
		Left = Button1,
		Right = Button2,
		Middle = Button3,
	};
}

#define PC_MOUSE_BUTTON_1         ::PC::Mouse::Button1
#define PC_MOUSE_BUTTON_2         ::PC::Mouse::Button2
#define PC_MOUSE_BUTTON_3         ::PC::Mouse::Button3
#define PC_MOUSE_BUTTON_4         ::PC::Mouse::Button4
#define PC_MOUSE_BUTTON_5         ::PC::Mouse::Button5
#define PC_MOUSE_BUTTON_6         ::PC::Mouse::Button6
#define PC_MOUSE_BUTTON_7         ::PC::Mouse::Button7
#define PC_MOUSE_BUTTON_8         ::PC::Mouse::Button8
#define PC_MOUSE_BUTTON_LAST      ::PC::Mouse::Last
#define PC_MOUSE_BUTTON_LEFT      ::PC::Mouse::Left
#define PC_MOUSE_BUTTON_RIGHT     ::PC::Mouse::Right
#define PC_MOUSE_BUTTON_MIDDLE    ::PC::Mouse::Middle