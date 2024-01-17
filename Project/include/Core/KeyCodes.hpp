//
// Created by ianpo on 19/07/2023.
//

#pragma once

// Imported from VXM3.h

/* The unknown key */
#define PC_KEY_UNKNOWN            -1

/* Printable keys */
#define PC_KEY_SPACE              32
#define PC_KEY_APOSTROPHE         39  /* ' */
#define PC_KEY_COMMA              44  /* , */
#define PC_KEY_MINUS              45  /* - */
#define PC_KEY_PERIOD             46  /* . */
#define PC_KEY_SLASH              47  /* / */
#define PC_KEY_0                  48
#define PC_KEY_1                  49
#define PC_KEY_2                  50
#define PC_KEY_3                  51
#define PC_KEY_4                  52
#define PC_KEY_5                  53
#define PC_KEY_6                  54
#define PC_KEY_7                  55
#define PC_KEY_8                  56
#define PC_KEY_9                  57
#define PC_KEY_SEMICOLON          59  /* ; */
#define PC_KEY_EQUAL              61  /* = */
#define PC_KEY_A                  65
#define PC_KEY_B                  66
#define PC_KEY_C                  67
#define PC_KEY_D                  68
#define PC_KEY_E                  69
#define PC_KEY_F                  70
#define PC_KEY_G                  71
#define PC_KEY_H                  72
#define PC_KEY_I                  73
#define PC_KEY_J                  74
#define PC_KEY_K                  75
#define PC_KEY_L                  76
#define PC_KEY_M                  77
#define PC_KEY_N                  78
#define PC_KEY_O                  79
#define PC_KEY_P                  80
#define PC_KEY_Q                  81
#define PC_KEY_R                  82
#define PC_KEY_S                  83
#define PC_KEY_T                  84
#define PC_KEY_U                  85
#define PC_KEY_V                  86
#define PC_KEY_W                  87
#define PC_KEY_X                  88
#define PC_KEY_Y                  89
#define PC_KEY_Z                  90
#define PC_KEY_LEFT_BRACKET       91  /* [ */
#define PC_KEY_BACKSLASH          92  /* \ */
#define PC_KEY_RIGHT_BRACKET      93  /* ] */
#define PC_KEY_GRAVE_ACCENT       96  /* ` */
#define PC_KEY_WORLD_1            161 /* non-US #1 */
#define PC_KEY_WORLD_2            162 /* non-US #2 */


/* Function keys */
#define PC_KEY_ESCAPE             256
#define PC_KEY_ENTER              257
#define PC_KEY_TAB                258
#define PC_KEY_BACKSPACE          259
#define PC_KEY_INSERT             260
#define PC_KEY_DELETE             261
#define PC_KEY_RIGHT              262
#define PC_KEY_LEFT               263
#define PC_KEY_DOWN               264
#define PC_KEY_UP                 265
#define PC_KEY_PAGE_UP            266
#define PC_KEY_PAGE_DOWN          267
#define PC_KEY_HOME               268
#define PC_KEY_END                269
#define PC_KEY_CAPS_LOCK          280
#define PC_KEY_SCROLL_LOCK        281
#define PC_KEY_NUM_LOCK           282
#define PC_KEY_PRINT_SCREEN       283
#define PC_KEY_PAUSE              284
#define PC_KEY_F1                 290
#define PC_KEY_F2                 291
#define PC_KEY_F3                 292
#define PC_KEY_F4                 293
#define PC_KEY_F5                 294
#define PC_KEY_F6                 295
#define PC_KEY_F7                 296
#define PC_KEY_F8                 297
#define PC_KEY_F9                 298
#define PC_KEY_F10                299
#define PC_KEY_F11                300
#define PC_KEY_F12                301
#define PC_KEY_F13                302
#define PC_KEY_F14                303
#define PC_KEY_F15                304
#define PC_KEY_F16                305
#define PC_KEY_F17                306
#define PC_KEY_F18                307
#define PC_KEY_F19                308
#define PC_KEY_F20                309
#define PC_KEY_F21                310
#define PC_KEY_F22                311
#define PC_KEY_F23                312
#define PC_KEY_F24                313
#define PC_KEY_F25                314
#define PC_KEY_KP_0               320
#define PC_KEY_KP_1               321
#define PC_KEY_KP_2               322
#define PC_KEY_KP_3               323
#define PC_KEY_KP_4               324
#define PC_KEY_KP_5               325
#define PC_KEY_KP_6               326
#define PC_KEY_KP_7               327
#define PC_KEY_KP_8               328
#define PC_KEY_KP_9               329
#define PC_KEY_KP_DECIMAL         330
#define PC_KEY_KP_DIVIDE          331
#define PC_KEY_KP_MULTIPLY        332
#define PC_KEY_KP_SUBTRACT        333
#define PC_KEY_KP_ADD             334
#define PC_KEY_KP_ENTER           335
#define PC_KEY_KP_EQUAL           336
#define PC_KEY_LEFT_SHIFT         340
#define PC_KEY_LEFT_CONTROL       341
#define PC_KEY_LEFT_ALT           342
#define PC_KEY_LEFT_SUPER         343
#define PC_KEY_RIGHT_SHIFT        344
#define PC_KEY_RIGHT_CONTROL      345
#define PC_KEY_RIGHT_ALT          346
#define PC_KEY_RIGHT_SUPER        347
#define PC_KEY_MENU               348
#define PC_KEY_LAST               PC_KEY_MENU

namespace PC {

	enum class Key : int {
		Unknown = PC_KEY_UNKNOWN,
		Space = PC_KEY_SPACE,
		Apostrophe = PC_KEY_APOSTROPHE,
		Comma = PC_KEY_COMMA,
		Minus = PC_KEY_MINUS,
		Period = PC_KEY_PERIOD,
		Slash = PC_KEY_SLASH,
		Key0 = PC_KEY_0,
		Key1 = PC_KEY_1,
		Key2 = PC_KEY_2,
		Key3 = PC_KEY_3,
		Key4 = PC_KEY_4,
		Key5 = PC_KEY_5,
		Key6 = PC_KEY_6,
		Key7 = PC_KEY_7,
		Key8 = PC_KEY_8,
		Key9 = PC_KEY_9,
		Semicolon = PC_KEY_SEMICOLON,
		Equal = PC_KEY_EQUAL,
		A = PC_KEY_A,
		B = PC_KEY_B,
		C = PC_KEY_C,
		D = PC_KEY_D,
		E = PC_KEY_E,
		F = PC_KEY_F,
		G = PC_KEY_G,
		H = PC_KEY_H,
		I = PC_KEY_I,
		J = PC_KEY_J,
		K = PC_KEY_K,
		L = PC_KEY_L,
		M = PC_KEY_M,
		N = PC_KEY_N,
		O = PC_KEY_O,
		P = PC_KEY_P,
		Q = PC_KEY_Q,
		R = PC_KEY_R,
		S = PC_KEY_S,
		T = PC_KEY_T,
		U = PC_KEY_U,
		V = PC_KEY_V,
		W = PC_KEY_W,
		X = PC_KEY_X,
		Y = PC_KEY_Y,
		Z = PC_KEY_Z,
		LeftBracket = PC_KEY_LEFT_BRACKET,
		Backslash = PC_KEY_BACKSLASH,
		RightBracket = PC_KEY_RIGHT_BRACKET,
		GraveAccent = PC_KEY_GRAVE_ACCENT,
		World1 = PC_KEY_WORLD_1,
		World2 = PC_KEY_WORLD_2,

		Escape = PC_KEY_ESCAPE,
		Enter = PC_KEY_ENTER,
		Tab = PC_KEY_TAB,
		Backspace = PC_KEY_BACKSPACE,
		Insert = PC_KEY_INSERT,
		Delete = PC_KEY_DELETE,
		Right = PC_KEY_RIGHT,
		Left = PC_KEY_LEFT,
		Down = PC_KEY_DOWN,
		Up = PC_KEY_UP,
		PageUp = PC_KEY_PAGE_UP,
		PageDown = PC_KEY_PAGE_DOWN,
		Home = PC_KEY_HOME,
		End = PC_KEY_END,
		CapsLock = PC_KEY_CAPS_LOCK,
		ScrollLock = PC_KEY_SCROLL_LOCK,
		NumLock = PC_KEY_NUM_LOCK,
		PrintScreen = PC_KEY_PRINT_SCREEN,
		Pause = PC_KEY_PAUSE,
		F1 = PC_KEY_F1,
		F2 = PC_KEY_F2,
		F3 = PC_KEY_F3,
		F4 = PC_KEY_F4,
		F5 = PC_KEY_F5,
		F6 = PC_KEY_F6,
		F7 = PC_KEY_F7,
		F8 = PC_KEY_F8,
		F9 = PC_KEY_F9,
		F10 = PC_KEY_F10,
		F11 = PC_KEY_F11,
		F12 = PC_KEY_F12,
		F13 = PC_KEY_F13,
		F14 = PC_KEY_F14,
		F15 = PC_KEY_F15,
		F16 = PC_KEY_F16,
		F17 = PC_KEY_F17,
		F18 = PC_KEY_F18,
		F19 = PC_KEY_F19,
		F20 = PC_KEY_F20,
		F21 = PC_KEY_F21,
		F22 = PC_KEY_F22,
		F23 = PC_KEY_F23,
		F24 = PC_KEY_F24,
		F25 = PC_KEY_F25,
		Kp0 = PC_KEY_KP_0,
		Kp1 = PC_KEY_KP_1,
		Kp2 = PC_KEY_KP_2,
		Kp3 = PC_KEY_KP_3,
		Kp4 = PC_KEY_KP_4,
		Kp5 = PC_KEY_KP_5,
		Kp6 = PC_KEY_KP_6,
		Kp7 = PC_KEY_KP_7,
		Kp8 = PC_KEY_KP_8,
		Kp9 = PC_KEY_KP_9,
		KpDecimal = PC_KEY_KP_DECIMAL,
		KpDivide = PC_KEY_KP_DIVIDE,
		KpMultiply = PC_KEY_KP_MULTIPLY,
		KpSubtract = PC_KEY_KP_SUBTRACT,
		KpAdd = PC_KEY_KP_ADD,
		KpEnter = PC_KEY_KP_ENTER,
		KpEqual = PC_KEY_KP_EQUAL,
		LeftShift = PC_KEY_LEFT_SHIFT,
		LeftControl = PC_KEY_LEFT_CONTROL,
		LeftAlt = PC_KEY_LEFT_ALT,
		LeftSuper = PC_KEY_LEFT_SUPER,
		RightShift = PC_KEY_RIGHT_SHIFT,
		RightControl = PC_KEY_RIGHT_CONTROL,
		RightAlt = PC_KEY_RIGHT_ALT,
		RightSuper = PC_KEY_RIGHT_SUPER,
		Menu = PC_KEY_MENU,
		Last = PC_KEY_LAST,
	};
}