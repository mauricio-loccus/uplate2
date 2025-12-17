#include <iostream> // For console output (std::cout, std::cerr)

#include "tests.h"
#include "keyboard.h"

// --- Test functions implementations ---

/**
 * @brief Demonstrates basic key press and release for a single character.
 * Uses the instance methods `press` and `release`.
 */
void test_basic_press_release() {
	std::cout << "--- Running Test: Basic Press and Release ---\n";
	TKeyboard keyboard; // Create an instance of TKeyboard
	std::cout << "Typing 'a' then 'B' using press/release...\n";
	try {
		keyboard.press('a');
		keyboard.release('a');
		Sleep(100); // Small pause between keys
		keyboard.press('B'); // Should automatically press Shift then B
		keyboard.release('B'); // Should automatically release B then Shift
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_basic_press_release: " << e.what()
			<< std::endl;
	}
	Sleep(1000); // Pause for observation
	std::cout << "Finished Test: Basic Press and Release.\n\n";
}

/**
 * @brief Demonstrates typing a string of lowercase characters using the `write` method.
 */
void test_write_lowercase() {
	std::cout << "--- Running Test: Write Lowercase Text ---\n";
	TKeyboard keyboard;
	std::cout << "Typing 'hello world'...\n";
	try {
		keyboard.write("hello world");
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_lowercase: " << e.what() << std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: Write Lowercase Text.\n\n";
}

/**
 * @brief Demonstrates typing a string of uppercase characters using the `write` method,
 * showcasing internal Shift key management.
 */
void test_write_uppercase() {
	std::cout << "--- Running Test: Write Uppercase Text ---\n";
	TKeyboard keyboard;
	std::cout << "Typing 'HELLO WORLD'...\n";
	try {
		keyboard.write("HELLO WORLD");
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_uppercase: " << e.what() << std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: Write Uppercase Text.\n\n";
}

/**
 * @brief Demonstrates typing a string with mixed case, numbers, and symbols using the `write` method.
 * Relies on `VkKeyScan` for correct symbol mapping and Shift handling based on keyboard layout.
 */
void test_write_mixed_case() {
	std::cout << "--- Running Test: Write Mixed Case and Symbols ---\n";
	TKeyboard keyboard;
	std::cout <<
		"Typing 'Hello World 123!@#$%^&*()_+-=[]{}\\|;:'\",<.>/?`~'...\n";
	try {
		keyboard.write("Hello World 123!@#$%^&*()_+-=[]{}\\|;:'\",<.>/?`~");
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_mixed_case: " << e.what()
			<< std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: Write Mixed Case and Symbols.\n\n";
}

/**
 * @brief Demonstrates pressing and releasing special keys using VK codes directly
 * via the static methods `press_key_vk` and `release_key_vk`.
 */
void test_special_keys() {
	std::cout << "--- Running Test: Special Keys (Direct VK) ---\n";
	std::cout << "Pressing Enter, Tab, and Esc...\n";

	try {
		TKeyboard::press_key_vk(VK_RETURN); // Press Enter
		Sleep(TYPING_DELAY_MS);
		TKeyboard::release_key_vk(VK_RETURN); // Release Enter
		Sleep(500); // Pause

		TKeyboard::press_key_vk(VK_TAB); // Press Tab
		Sleep(TYPING_DELAY_MS);
		TKeyboard::release_key_vk(VK_TAB); // Release Tab
		Sleep(500); // Pause

		TKeyboard::press_key_vk(VK_ESCAPE); // Press Esc
		Sleep(TYPING_DELAY_MS);
		TKeyboard::release_key_vk(VK_ESCAPE); // Release Esc
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_special_keys: " << e.what() << std::endl;
	}
	Sleep(1000); // Pause
	std::cout << "Finished Test: Special Keys (Direct VK).\n\n";
}

/**
 * @brief Demonstrates basic `writeMacro` functionality with plain text and special keys.
 */
void test_write_macro_basic() {
	std::cout << "--- Running Test: writeMacro Basic ---\n";
	TKeyboard keyboard;
	std::cout << "Typing 'Hello World{ENTER}This is a test{TAB}123{F5}'...\n";
	try {
		keyboard.writeMacro("Hello World{ENTER}This is a test{TAB}123{F5}");
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_macro_basic: " << e.what()
			<< std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: writeMacro Basic.\n\n";
}

/**
 * @brief Demonstrates `writeMacro` with modifier prefixes (+, ^, %, *).
 */
void test_write_macro_modifiers() {
	std::cout << "--- Running Test: writeMacro Modifiers ---\n";
	TKeyboard keyboard;
	std::cout << "Typing Ctrl+S, Shift+A, Alt+F4...\n";
	try {
		keyboard.writeMacro("^+S"); // Ctrl+S (typically Save)
		Sleep(500);
		keyboard.writeMacro("+a"); // Shift+A (produces uppercase 'A')
		Sleep(500);
		keyboard.writeMacro("%{F4}");
		// Alt+F4 (typically closes the active window)
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_macro_modifiers: " << e.what()
			<< std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: writeMacro Modifiers.\n\n";
}

/**
 * @brief Demonstrates `writeMacro` with grouping parentheses `()`.
 * Modifiers preceding the group are held for the entire group.
 */
void test_write_macro_grouping() {
	std::cout << "--- Running Test: writeMacro Grouping ---\n";
	TKeyboard keyboard;
	std::cout << "Typing Shift+(abc), then Ctrl+(def)...\n";
	try {
		keyboard.writeMacro("+(abc)"); // Shift held for 'a', 'b', 'c'
		Sleep(500);
		keyboard.writeMacro("^(def)"); // Ctrl held for 'd', 'e', 'f'
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_macro_grouping: " << e.what()
			<< std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: writeMacro Grouping.\n\n";
}

/**
 * @brief Demonstrates `writeMacro` with nested grouping.
 * Modifiers apply to their direct scope and are inherited by inner scopes.
 */
void test_write_macro_nested_grouping() {
	std::cout << "--- Running Test: writeMacro Nested Grouping ---\n";
	TKeyboard keyboard;
	std::cout <<
		"Typing Ctrl+(a+b). This should be Ctrl+A, then Ctrl+Shift+B...\n";
	try {
		keyboard.writeMacro("^(a+(b))");
		// Ctrl held for 'a', then Ctrl+Shift held for 'b'
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_macro_nested_grouping: " << e.what()
			<< std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: writeMacro Nested Grouping.\n\n";
}

/**
 * @brief Specific test for ALT+O, as requested by the user.
 */
void test_write_macro_alt_o() {
	std::cout << "--- Running Test: writeMacro ALT+O ---\n";
	TKeyboard keyboard;
	std::cout << "Typing Alt+O...\n";
	try {
		keyboard.writeMacro("%O"); // Alt+O
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_macro_alt_o: " << e.what()
			<< std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: writeMacro ALT+O.\n\n";
}

/**
 * @brief Specific test for Windows+Shift+S, as requested by the user.
 * This combination typically opens the Snip & Sketch tool on modern Windows.
 */
void test_write_macro_win_shift_s() {
	std::cout << "--- Running Test: writeMacro Windows+Shift+S ---\n";
	TKeyboard keyboard;
	std::cout <<
		"Typing Windows+Shift+S (should open Snip & Sketch on modern Windows)...\n";
	try {
		keyboard.writeMacro("*+S"); // Windows+Shift+S
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_macro_win_shift_s: " << e.what()
			<< std::endl;
	}
	Sleep(2000);
	// Longer delay to observe Snip & Sketch or other system response
	std::cout << "Finished Test: writeMacro Windows+Shift+S.\n\n";
}

/**
 * @brief Demonstrates `writeMacro` with escaped characters.
 * These characters are normally syntax elements but are sent literally when escaped.
 */
void test_write_macro_escaped_chars() {
	std::cout << "--- Running Test: writeMacro Escaped Characters ---\n";
	TKeyboard keyboard;
	std::cout << "Typing literal: + ^ % ~ ( ) { } ...\n";
	try {
		keyboard.writeMacro("{+}{^}{%}{~}{(}{)}{{}{}}"); // Send literal symbols
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Error in test_write_macro_escaped_chars: " << e.what()
			<< std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: writeMacro Escaped Characters.\n\n";
}

/**
 * @brief Demonstrates `writeMacro` with invalid syntax (mismatched parentheses/braces).
 * This test is expected to print error messages to the console (std::cerr) by catching exceptions.
 */
void test_write_macro_invalid_syntax() {
	std::cout << "--- Running Test: writeMacro Invalid Syntax ---\n";
	TKeyboard keyboard;

	std::cout <<
		"Attempting to type macro with mismatched parenthesis: ^(abc...\n";
	try {
		keyboard.writeMacro("^(abc"); // Mismatched parenthesis - should throw
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}
	Sleep(500);

	std::cout << "Attempting to type macro with mismatched brace: {F1...\n";
	try {
		keyboard.writeMacro("{F1"); // Mismatched brace - should throw
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}
	Sleep(500);

	std::cout <<
		"Attempting to type macro with unknown special key: {UNKNOWN}...\n";
	try {
		keyboard.writeMacro("{UNKNOWN}"); // Unknown special key - should throw
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}
	Sleep(1000);
	std::cout << "Finished Test: writeMacro Invalid Syntax.\n\n";
}

void press_release(int key, int interval = TYPING_DELAY_MS) {
	TKeyboard::press_key_vk(key);
	Sleep(interval);
	TKeyboard::release_key_vk(key);
}

void uPlate_selectWindow(const wchar_t* title) {
	// HWND hwnd = FindWindowW(NULL, L"µPlate");
	HWND hwnd = FindWindowW(NULL, title);
	if (hwnd == NULL)
		return;

	SetForegroundWindow(hwnd); // Traz a janela para frente
	// ShowWindow(hwnd, SW_RESTORE); // Restaura se estiver minimizada
	Sleep(500);
}

HWND g_foundDialog = NULL;

HWND uPlate_GetTopmostFocusedWindow() {
	HWND hFocused = GetForegroundWindow();

	if (hFocused != NULL && IsWindowVisible(hFocused) && GetParent(hFocused)
		== NULL)
		return hFocused;

	return NULL;
}

BOOL CALLBACK uPlate_EnumWindowsOpenDialogProc(HWND hWnd, LPARAM lParam) {
	char className[256];
	char windowText[256];

	GetClassNameA(hWnd, className, sizeof(className));
	GetWindowTextA(hWnd, windowText, sizeof(windowText));

	if (strcmp(className, "#32770") == 0) // Verifica se é um diálogo padrão
	{
		 g_foundDialog = hWnd;
		 return FALSE; // Parar enumeração
	}

	return TRUE;
}

BOOL CALLBACK uPlate_EnumWindowsProc(HWND hWnd, LPARAM parentHwnd) {
	char className[256];

	GetClassNameA(hWnd, className, sizeof(className));
	if (strcmp(className, "#32770") == 0) {
		HWND parent = GetParent(hWnd);
		if (parent == (HWND)parentHwnd) {
			g_foundDialog = hWnd;
			return FALSE; // Se encontrar parar enumeração
		}
	}

	return TRUE;
}

HWND uPlate_WaitForOpenDialog(HWND parentHwnd, DWORD timeoutMs = 10000) {
	g_foundDialog = NULL;

	DWORD start;
	DWORD finish;
	//BOOL  found;

	start = GetTickCount();
	do {
		finish = GetTickCount();

		EnumWindows(uPlate_EnumWindowsProc, (LPARAM)parentHwnd);

		//found  = true;
		//found &= (g_foundDialog != NULL);
		//found &= IsWindowVisible(g_foundDialog);
		if (g_foundDialog != NULL && IsWindowVisible(g_foundDialog) && GetForegroundWindow() == g_foundDialog)
		//if (found)
		{
			std::cout << "Open dialog encontrado em " << ((finish - start) / 1) << " ms " << std::endl;
			return g_foundDialog;
		}
		Sleep(100);
	}
	while ((finish - start) < timeoutMs);
	std::cout << "Timeout waiting open dialog" << std::endl;

	return NULL; // Timeout
}

/*
 bool IsOpenFileDialogReady()
 {
 g_foundDialog = NULL;
 EnumWindows(EnumWindowsProc, 0);

 return (g_foundDialog != NULL && GetForegroundWindow() == g_foundDialog);
 }
 */

void uPlate_LoginAutoCompleted()
{
	TKeyboard::press_key_vk(VK_RETURN); // Enter key [1]
	Sleep(TYPING_DELAY_MS);
	TKeyboard::release_key_vk(VK_RETURN);
	Sleep(1000);
}

int uPlate_SelectFileOpenedDialog(TKeyboard& keyboard, std::string Filename,
	HWND hMainHwnd) {
	TKeyboard::press_key_vk(VK_MENU); // Press ALT key [1]
	Sleep(500);

	TKeyboard::press_key_vk(0x4E);
	// Press 'N' key (Virtual Key Code for 'N' is 0x4E) [2]
	Sleep(TYPING_DELAY_MS);

	TKeyboard::release_key_vk(0x4E); // Release 'N' key
	Sleep(TYPING_DELAY_MS);

	TKeyboard::release_key_vk(VK_MENU); // Release ALT key
	// 1Sleep(4000);
	HWND dialog = uPlate_WaitForOpenDialog(hMainHwnd, 10000);
	if (!dialog)
	{
		std::cout << "Dialog not found..." << std::endl;
		return 1;
	}

	// Digita o nome do arquivo
	keyboard.write(Filename);
	Sleep(500);

	// Aciona <ENTER> após escolha do arquivo
	TKeyboard::press_key_vk(VK_RETURN);                         // Enter key [1]
	Sleep(TYPING_DELAY_MS);
	TKeyboard::release_key_vk(VK_RETURN);

	return 0;
}

void uPlate_FileOpenProtocol(TKeyboard& keyboard, std::string Filename,
	HWND parentMainWnd) {
	TKeyboard::press_key_vk(VK_MENU); // Press ALT key [1]
	Sleep(500);

	TKeyboard::press_key_vk(0x41);
	// Press 'A' key (Virtual Key Code for 'A' is 0x41) [2]
	Sleep(500);

	TKeyboard::release_key_vk(0x41); // Release 'A' key
	Sleep(TYPING_DELAY_MS);

	TKeyboard::release_key_vk(VK_MENU); // Release ALT key
	Sleep(500);

	keyboard.write("p");
	Sleep(500);
	keyboard.write("c");

	int result = uPlate_SelectFileOpenedDialog(keyboard, Filename, parentMainWnd);
	if (!result)
	{
		return;
	}

	Sleep(3500);
}

void uPlate_FillPlates1() {

}


void uPlate_FillPlates3()
{
	//TKeyboard::press_key_vk(VK_MENU); // Press ALT key [1]
	//Sleep(500);
	//TKeyboard::press_key_vk(0x50);
	//Sleep(200);
	//TKeyboard::release_key_vk(0x50); // Release 'P' key
	//Sleep(TYPING_DELAY_MS);
	//TKeyboard::release_key_vk(VK_MENU); // Release ALT key
	//Sleep(200);

	TKeyboard::press_key_vk(VK_CONTROL); // Press ALT key [1]
	Sleep(400);
	TKeyboard::press_key_vk(0x52);
	Sleep(200);
	TKeyboard::release_key_vk(0x52); // Release 'P' key
	Sleep(TYPING_DELAY_MS);
	TKeyboard::release_key_vk(VK_CONTROL); // Release ALT key
	Sleep(200);

	TKeyboard::press_key_vk  (0x56);   // Press 'A' key (Virtual Key Code for 'V' is 0x41) [2]
	Sleep(200);
	TKeyboard::release_key_vk(0x56);     // Release 'V' key
	Sleep(TYPING_DELAY_MS);
	Sleep(3000);

	TKeyboard::press_key_vk(0x46);
	Sleep(200);
	TKeyboard::release_key_vk(0x46);     // Release 'F' key
	Sleep(TYPING_DELAY_MS);

	TKeyboard::press_key_vk  (0x56);     // Press 'V' key (Virtual Key Code for 'V' is 0x56)
	Sleep(200);
	TKeyboard::release_key_vk(0x56);     // Release 'V' key
	Sleep(TYPING_DELAY_MS);
	Sleep(2000);

	TKeyboard::press_key_vk(0x46);
	Sleep(200);

	TKeyboard::press_key_vk  (0x56);     // Press 'V' key (Virtual Key Code for 'V' is 0x56)
	Sleep(200);
	TKeyboard::release_key_vk(0x56);     // Release 'V' key
	Sleep(TYPING_DELAY_MS);
	Sleep(2000);

	TKeyboard::release_key_vk(0x46); // Release 'F' key
	Sleep(TYPING_DELAY_MS);

	TKeyboard::press_key_vk(VK_RETURN); // Enter key [1]
	Sleep(TYPING_DELAY_MS);
	TKeyboard::release_key_vk(VK_RETURN);
	Sleep(1000);

	TKeyboard::press_key_vk  (0x56);     // Press 'V' key (Virtual Key Code for 'V' is 0x56)
	Sleep(200);
	TKeyboard::release_key_vk(0x56);     // Release 'V' key
	Sleep(TYPING_DELAY_MS);
	Sleep(2000);

	TKeyboard::press_key_vk(0x46);
	Sleep(200);
	TKeyboard::release_key_vk(0x46); // Release 'F' key
	Sleep(TYPING_DELAY_MS);

	TKeyboard::press_key_vk(0x46);
	Sleep(200);
	TKeyboard::release_key_vk(0x46); // Release 'F' key
	Sleep(TYPING_DELAY_MS);

	TKeyboard::press_key_vk(VK_RETURN); // Enter key [1]
	Sleep(TYPING_DELAY_MS);
	TKeyboard::release_key_vk(VK_RETURN);
	Sleep(1000);

	TKeyboard::press_key_vk(0x46);
	Sleep(200);
	TKeyboard::release_key_vk(0x46); // Release 'F' key
	Sleep(TYPING_DELAY_MS);

	press_release(VK_RETURN); // Enter key [1]
	Sleep(1000);

	press_release(VK_ESCAPE);
	Sleep(1000);
}



void uPlate_OpenInputLabels()
{
	TKeyboard::press_key_vk(VK_CONTROL);     // Press CTRL key [1]
	Sleep(400);
	TKeyboard::press_key_vk(0x49);
	Sleep(200);
	TKeyboard::release_key_vk(0x49);         // Release 'I' key
	Sleep(TYPING_DELAY_MS);
	TKeyboard::release_key_vk(VK_CONTROL);   // Release CTRL key
	Sleep(200);

	/*
	TKeyboard::press_key_vk(VK_MENU);
	Sleep(500);

	press_release(0x49, 200);

	TKeyboard::release_key_vk(VK_MENU); // Release ALT key
	Sleep(200);
	*/
}


void uPlate_Another(TKeyboard& keyboard) {
	// uPlate_selectWindow(L"µPlate");
	uPlate_selectWindow(L"Rótulos");

	TKeyboard::press_key_vk(VK_UP);
	Sleep(200);
	TKeyboard::release_key_vk(VK_UP);
	Sleep(300);

	TKeyboard::press_key_vk(VK_UP);
	Sleep(200);
	TKeyboard::release_key_vk(VK_UP);
	Sleep(300);

	// Digita sequencia
	keyboard.write("abcdefghijklm");
	Sleep(300);

	// Aciona <ENTER> após escolha do arquivo
	TKeyboard::press_key_vk(VK_RETURN); // Enter key [1]
	Sleep(TYPING_DELAY_MS);
	TKeyboard::release_key_vk(VK_RETURN);
}


void test_uPlate_case()
{
	std::cout << "--- Running Test: uPlate run ---" << std::endl;

	// SetConsoleOutputCP(65001);
	// SetConsoleCP(65001);
	// std::cout << "Acentos: áéíóúç" << std::endl;

	int option;

	do {
		std::cout << "Digite uma opção : ";

		bool status = std::cin >> option;
		if (status)
			break;

		std::cout << "Entrada invalida. A opção deve ser numérica." <<
			std::endl << std::endl;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}
	while (true);

	TKeyboard keyboard;
	HWND hMainWindow;

	uPlate_selectWindow(L"Login na Aplicação");
	uPlate_LoginAutoCompleted();

	hMainWindow = uPlate_GetTopmostFocusedWindow();

	switch (option)
	{
		case 1:
			std::cout << "Main Window Handle : " << hMainWindow << std::endl;

			uPlate_FileOpenProtocol(keyboard, "p-3-placas.ptrl", hMainWindow);
			uPlate_FillPlates3();
			uPlate_OpenInputLabels();
			break;

	case 2:
		uPlate_FileOpenProtocol(keyboard, "x1.ptrl", hMainWindow);
		// uPlate_FillPlates3();
		break;

	case 9:
		uPlate_Another(keyboard);
		break;

	default:
		std::cout << "Opção não encontrada" << std::endl << std::endl;
		break;

	}

	std::cout << "Finished Test.\n\n";

	std::cout << "Sleeping " << 10 << " seconds" << std::endl;
	Sleep(10 * 1000);
}


