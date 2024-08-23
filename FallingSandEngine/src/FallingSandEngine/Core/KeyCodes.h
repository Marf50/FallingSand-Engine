#pragma once
namespace FallingSandEngine
{
	typedef enum class KeyCode : uint16_t
	{
		// from glfw 3
		Space = 32,
		Apostrophe = 39,
		Comma = 44,
		Minus = 45,
		Period = 46, /* . */
		Slash = 47, /* / */
		D0 = 48,
		D1 = 49,
		D2 = 50,
		D3 = 51,
		D4 = 52,
		D5 = 53,
		D6 = 54,
		D7 = 55,
		D8 = 56,
		D9 = 57,
		Semicolon = 59, /* ; */
		Equal = 61, /* = */
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		Left_Bracket = 91, /* [ */
		Backslash = 92, /* \ */
		Right_Bracket = 93, /* ] */
		Grave_Accent = 96, /* ` */
		World_1 = 161,/* non-US #1 */
		World_2 = 162,/* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		Page_up = 266,
		Page_Down = 267,
		Home = 268,
		End = 269,
		Caps_Lock = 280,
		Scroll_Lock = 281,
		Num_Lock = 282,
		Print_Screen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		KP_0 = 320,
		KP_1 = 321,
		KP_2 = 322,
		KP_3 = 323,
		KP_4 = 324,
		KP_5 = 325,
		KP_6 = 326,
		KP_7 = 327,
		KP_8 = 328,
		KP_9 = 329,
		KP_Decimal = 330,
		KP_Divide = 331,
		KP_Multiply = 332,
		KP_Subtract = 333,
		KP_Add = 334,
		KP_Enter = 335,
		KP_Equal = 336,
		Left_Shift = 340,
		Left_Control = 341,
		Left_Alt = 342,
		Left_Super = 343,
		Right_Shift = 344,
		Right_Control = 345,
		Right_Alt = 346,
		Right_Super = 347,
		Menu = 348,


	};
	//	
	//		// from glfw 3
	//#define FSE_KEY_SPACE              32
	//#define FSE_KEY_APOSTROPHE         39  /* ' */
	//#define FSE_KEY_COMMA              44  /* , */
	//#define FSE_KEY_MINUS              45  /* - */
	//#define FSE_KEY_PERIOD             46  /* . */
	//#define FSE_KEY_SLASH              47  /* / */
	//#define FSE_KEY_0                  48
	//#define FSE_KEY_1                  49
	//#define FSE_KEY_2                  50
	//#define FSE_KEY_3                  51
	//#define FSE_KEY_4                  52
	//#define FSE_KEY_5                  53
	//#define FSE_KEY_6                  54
	//#define FSE_KEY_7                  55
	//#define FSE_KEY_8                  56
	//#define FSE_KEY_9                  57
	//#define FSE_KEY_SEMICOLON          59  /* ; */
	//#define FSE_KEY_EQUAL              61  /* = */
	//#define FSE_KEY_A                  65
	//#define FSE_KEY_B                  66
	//#define FSE_KEY_C                  67
	//#define FSE_KEY_D                  68
	//#define FSE_KEY_E                  69
	//#define FSE_KEY_F                  70
	//#define FSE_KEY_G                  71
	//#define FSE_KEY_H                  72
	//#define FSE_KEY_I                  73
	//#define FSE_KEY_J                  74
	//#define FSE_KEY_K                  75
	//#define FSE_KEY_L                  76
	//#define FSE_KEY_M                  77
	//#define FSE_KEY_N                  78
	//#define FSE_KEY_O                  79
	//#define FSE_KEY_P                  80
	//#define FSE_KEY_Q                  81
	//#define FSE_KEY_R                  82
	//#define FSE_KEY_S                  83
	//#define FSE_KEY_T                  84
	//#define FSE_KEY_U                  85
	//#define FSE_KEY_V                  86
	//#define FSE_KEY_W                  87
	//#define FSE_KEY_X                  88
	//#define FSE_KEY_Y                  89
	//#define FSE_KEY_Z                  90
	//#define FSE_KEY_LEFT_BRACKET       91  /* [ */
	//#define FSE_KEY_BACKSLASH          92  /* \ */
	//#define FSE_KEY_RIGHT_BRACKET      93  /* ] */
	//#define FSE_KEY_GRAVE_ACCENT       96  /* ` */
	//#define FSE_KEY_WORLD_1            161 /* non-US #1 */
	//#define FSE_KEY_WORLD_2            162 /* non-US #2 */
	//
	///* Function keys */
	//#define FSE_KEY_ESCAPE             256
	//#define FSE_KEY_ENTER              257
	//#define FSE_KEY_TAB                258
	//#define FSE_KEY_BACKSPACE          259
	//#define FSE_KEY_INSERT             260
	//#define FSE_KEY_DELETE             261
	//#define FSE_KEY_RIGHT              262
	//#define FSE_KEY_LEFT               263
	//#define FSE_KEY_DOWN               264
	//#define FSE_KEY_UP                 265
	//#define FSE_KEY_PAGE_UP            266
	//#define FSE_KEY_PAGE_DOWN          267
	//#define FSE_KEY_HOME               268
	//#define FSE_KEY_END                269
	//#define FSE_KEY_CAPS_LOCK          280
	//#define FSE_KEY_SCROLL_LOCK        281
	//#define FSE_KEY_NUM_LOCK           282
	//#define FSE_KEY_PRINT_SCREEN       283
	//#define FSE_KEY_PAUSE              284
	//#define FSE_KEY_F1                 290
	//#define FSE_KEY_F2                 291
	//#define FSE_KEY_F3                 292
	//#define FSE_KEY_F4                 293
	//#define FSE_KEY_F5                 294
	//#define FSE_KEY_F6                 295
	//#define FSE_KEY_F7                 296
	//#define FSE_KEY_F8                 297
	//#define FSE_KEY_F9                 298
	//#define FSE_KEY_F10                299
	//#define FSE_KEY_F11                300
	//#define FSE_KEY_F12                301
	//#define FSE_KEY_F13                302
	//#define FSE_KEY_F14                303
	//#define FSE_KEY_F15                304
	//#define FSE_KEY_F16                305
	//#define FSE_KEY_F17                306
	//#define FSE_KEY_F18                307
	//#define FSE_KEY_F19                308
	//#define FSE_KEY_F20                309
	//#define FSE_KEY_F21                310
	//#define FSE_KEY_F22                311
	//#define FSE_KEY_F23                312
	//#define FSE_KEY_F24                313
	//#define FSE_KEY_F25                314
	//#define FSE_KEY_KP_0               320
	//#define FSE_KEY_KP_1               321
	//#define FSE_KEY_KP_2               322
	//#define FSE_KEY_KP_3               323
	//#define FSE_KEY_KP_4               324
	//#define FSE_KEY_KP_5               325
	//#define FSE_KEY_KP_6               326
	//#define FSE_KEY_KP_7               327
	//#define FSE_KEY_KP_8               328
	//#define FSE_KEY_KP_9               329
	//#define FSE_KEY_KP_DECIMAL         330
	//#define FSE_KEY_KP_DIVIDE          331
	//#define FSE_KEY_KP_MULTIPLY        332
	//#define FSE_KEY_KP_SUBTRACT        333
	//#define FSE_KEY_KP_ADD             334
	//#define FSE_KEY_KP_ENTER           335
	//#define FSE_KEY_KP_EQUAL           336
	//#define FSE_KEY_LEFT_SHIFT         340
	//#define FSE_KEY_LEFT_CONTROL       341
	//#define FSE_KEY_LEFT_ALT           342
	//#define FSE_KEY_LEFT_SUPER         343
	//#define FSE_KEY_RIGHT_SHIFT        344
	//#define FSE_KEY_RIGHT_CONTROL      345
	//#define FSE_KEY_RIGHT_ALT          346
	//#define FSE_KEY_RIGHT_SUPER        347
	//#define FSE_KEY_MENU               348
	//
	//#define FSE_KEY_LAST               FSE_KEY_MENU
	//
}