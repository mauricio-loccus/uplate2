#include "p-keyboard.h"

// Define the static members outside the class definition (in the.cpp file)
// These are the virtual key codes that typically require the KEYEVENTF_EXTENDEDKEY flag.
// [1, 2]

const WORD TPreviousKeyboard::extended_key_codes[] = {
	VK_LWIN, VK_RWIN, VK_APPS, VK_SNAPSHOT, VK_INSERT, VK_DELETE, VK_HOME,
	VK_END, VK_PRIOR, VK_NEXT, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_DIVIDE,
	VK_NUMLOCK};

const int TPreviousKeyboard::extended_key_codes_count =
	sizeof(TPreviousKeyboard::extended_key_codes) / sizeof
	(TPreviousKeyboard::extended_key_codes);
