#include <iostream> // For console output (std::cout, std::cerr)

#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>

#include <stdio.h>

#include "tests.h"

int _tmain(int argc, _TCHAR* argv[]) {
	std::cout << "Starting TKeyboard Tests...\n";
	std::cout << "Tests will run with a short delay between actions.\n\n";

	//Sleep(2000);

	// Uncomment the tests you wish to run by removing '//' at the beginning of the line.
	// To disable a test, add '//' back.

	// test_basic_press_release();
	// test_write_lowercase();
	// test_write_uppercase();
	// test_write_mixed_case();
	// test_special_keys(); // This test requires specific focus on special keys
	// test_alt_f_combination(); // Test for ALT+O combination
	// test_write_macro_basic();
	// test_write_macro_modifiers();
	// test_write_macro_grouping();
	// test_write_macro_nested_grouping();
	// test_write_macro_alt_o();
	// test_write_macro_win_shift_s();
	// test_write_macro_escaped_chars();
	// test_write_macro_invalid_syntax();

	test_uPlate_case();

	std::cout << "\nTKeyboard Tests Finished.\n";
	// std::cout << "Press any key to exit...\n";
	// std::cin.get(); // Wait for user input before closing console

	return 0;
}
