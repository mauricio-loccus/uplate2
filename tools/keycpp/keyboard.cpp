// TKeyboard.cpp
#include "keyboard.h"
#include <string>    // For std::string
#include <stdexcept> // For std::runtime_error
#include <algorithm> // For std::find
#include <sstream>   // For std::stringstream (replacement for std::to_string)

// Initialize static members. These are defined here because they are static
// and belong to the class, not to individual objects.
std::map<std::string, WORD>TKeyboard::specialKeysMap;
std::map<char, WORD>TKeyboard::modifierMap;
std::map<std::string, char>TKeyboard::escapedCharsMap;
std::map<char, KeyMapping>TKeyboard::charToVkMap;
bool TKeyboard::mapsInitialized = false;

/**
 * @brief Internal helper function for controlled delays.
 * Uses std::this_thread::sleep_for or Windows' Sleep() based on _USE_STD_CHRONO_AND_THREAD define.
 * @param milliseconds The duration of the sleep in milliseconds. Defaults to TYPING_DELAY_MS.
 */
void TKeyboard::internal_sleep(DWORD milliseconds) {
#ifdef _USE_STD_CHRONO_AND_THREAD
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
#else
	Sleep(milliseconds);
#endif
}

/**
 * @brief Sends a single keyboard event (press or release) to the system.
 * This is the lowest-level abstraction interacting directly with SendInput.
 * @param vkCode The virtual key code of the key.
 * @param dwFlags Flags for the key event (e.g., 0 for press, KEYEVENTF_KEYUP for release).
 * @throws std::runtime_error if SendInput fails.
 */
void TKeyboard::send_key_event(WORD vkCode, DWORD dwFlags) {
	INPUT input = {0}; // Initialize INPUT structure to all zeros
	input.type = INPUT_KEYBOARD; // Specify that this is a keyboard event
	input.ki.wVk = vkCode; // Set the virtual key code
	// Map virtual key code to scan code for robustness.
	// This is important for some applications to correctly interpret the input.
	input.ki.wScan = MapVirtualKeyA(vkCode, MAPVK_VK_TO_VSC);
	input.ki.time = 0; // Let the system generate the timestamp
	input.ki.dwExtraInfo = 0; // No extra information
	input.ki.dwFlags = dwFlags; // Set the flags for press/release

	// If the key is an extended key (e.g., right ALT, right CTRL, Insert, Delete etc.),
	// add the KEYEVENTF_EXTENDEDKEY flag. This is crucial for correct behavior of some keys.
	if ((vkCode >= VK_LWIN && vkCode <= VK_APPS) ||
		// Windows keys (Left/Right Win, Apps key)
		vkCode == VK_SNAPSHOT || // Print Screen
		vkCode == VK_INSERT || vkCode == VK_DELETE || // Insert, Delete
		vkCode == VK_HOME || vkCode == VK_END || // Home, End
		vkCode == VK_PRIOR || vkCode == VK_NEXT || // Page Up/Down
		vkCode == VK_UP || vkCode == VK_DOWN || // Arrow keys
		vkCode == VK_LEFT || vkCode == VK_RIGHT || vkCode == VK_DIVIDE ||
		// Numpad divide key
		vkCode == VK_NUMLOCK) { // Num Lock key
		input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
	}

	// Send the input event to the system.
	// SendInput returns the number of events successfully inserted.
	UINT result = SendInput(1, &input, sizeof(INPUT));
	if (result != 1) {
		// Throw an exception if the event could not be sent successfully.
		std::stringstream ss;
		ss << "Error: SendInput failed for VK: 0x" << std::hex << vkCode;
		throw std::runtime_error(ss.str());
	}
}

/**
 * @brief Initializes all static maps used for key mappings.
 * This function is called once on the first use of TKeyboard.
 * It populates the maps with modifier symbols, special key names,
 * escaped characters, and character-to-VK code mappings.
 */
void TKeyboard::init_maps() {
	// Populate modifierMap: Maps single-character symbols to their respective
	// virtual key codes for modifier keys.
	TKeyboard::modifierMap['+'] = VK_SHIFT; // Shift key
	TKeyboard::modifierMap['^'] = VK_CONTROL; // Control key
	TKeyboard::modifierMap['%'] = VK_MENU; // Alt key
	TKeyboard::modifierMap['*'] = VK_LWIN;
	// Left Windows key (as requested by user)

	// Populate escapedCharsMap: Maps string representations of special characters
	// (when they need to be sent literally) to their actual character values.
	TKeyboard::escapedCharsMap["+"] = '+';
	TKeyboard::escapedCharsMap["^"] = '^';
	TKeyboard::escapedCharsMap["%"] = '%';
	TKeyboard::escapedCharsMap["~"] = '~';
	TKeyboard::escapedCharsMap["("] = '(';
	TKeyboard::escapedCharsMap[")"] = ')';
	TKeyboard::escapedCharsMap["{"] = '{';
	TKeyboard::escapedCharsMap["}"] = '}';

	// Populate specialKeysMap: Maps string names of special keys (e.g., function keys,
	// navigation keys) to their virtual key codes.
	TKeyboard::specialKeysMap["F1"] = VK_F1;
	TKeyboard::specialKeysMap["F2"] = VK_F2;
	TKeyboard::specialKeysMap["F3"] = VK_F3;
	TKeyboard::specialKeysMap["F4"] = VK_F4;
	TKeyboard::specialKeysMap["F5"] = VK_F5;
	TKeyboard::specialKeysMap["F6"] = VK_F6;
	TKeyboard::specialKeysMap["F7"] = VK_F7;
	TKeyboard::specialKeysMap["F8"] = VK_F8;
	TKeyboard::specialKeysMap["F9"] = VK_F9;
	TKeyboard::specialKeysMap["F10"] = VK_F10;
	TKeyboard::specialKeysMap["F11"] = VK_F11;
	TKeyboard::specialKeysMap["F12"] = VK_F12;
	TKeyboard::specialKeysMap["F13"] = VK_F13;
	TKeyboard::specialKeysMap["F14"] = VK_F14;
	TKeyboard::specialKeysMap["F15"] = VK_F15;
	TKeyboard::specialKeysMap["ESC"] = VK_ESCAPE;
	TKeyboard::specialKeysMap["ESCAPE"] = VK_ESCAPE;
	TKeyboard::specialKeysMap["ENTER"] = VK_RETURN;
	TKeyboard::specialKeysMap["RETURN"] = VK_RETURN; // Alias for ENTER
	TKeyboard::specialKeysMap["TAB"] = VK_TAB;
	TKeyboard::specialKeysMap["BACKSPACE"] = VK_BACK;
	TKeyboard::specialKeysMap["BS"] = VK_BACK; // Alias for BACKSPACE
	TKeyboard::specialKeysMap["BKSP"] = VK_BACK; // Alias for BACKSPACE
	TKeyboard::specialKeysMap["DELETE"] = VK_DELETE;
	TKeyboard::specialKeysMap["DEL"] = VK_DELETE; // Alias for DELETE
	TKeyboard::specialKeysMap["INSERT"] = VK_INSERT;
	TKeyboard::specialKeysMap["INS"] = VK_INSERT; // Alias for INSERT
	TKeyboard::specialKeysMap["HOME"] = VK_HOME;
	TKeyboard::specialKeysMap["END"] = VK_END;
	TKeyboard::specialKeysMap["PGUP"] = VK_PRIOR; // Page Up
	TKeyboard::specialKeysMap["PAGEUP"] = VK_PRIOR; // Alias for Page Up
	TKeyboard::specialKeysMap["PGDN"] = VK_NEXT; // Page Down
	TKeyboard::specialKeysMap["PAGEDOWN"] = VK_NEXT; // Alias for Page Down
	TKeyboard::specialKeysMap["LEFT"] = VK_LEFT; // Left Arrow
	TKeyboard::specialKeysMap["RIGHT"] = VK_RIGHT; // Right Arrow
	TKeyboard::specialKeysMap["UP"] = VK_UP; // Up Arrow
	TKeyboard::specialKeysMap["DOWN"] = VK_DOWN; // Down Arrow
	TKeyboard::specialKeysMap["SPACE"] = VK_SPACE; // Spacebar
	TKeyboard::specialKeysMap["CAPSLOCK"] = VK_CAPITAL; // Caps Lock
	TKeyboard::specialKeysMap["NUMLOCK"] = VK_NUMLOCK; // Num Lock
	TKeyboard::specialKeysMap["SCROLLLOCK"] = VK_SCROLL; // Scroll Lock
	TKeyboard::specialKeysMap["PRTSC"] = VK_SNAPSHOT; // Print Screen
	TKeyboard::specialKeysMap["PRINTSCREEN"] = VK_SNAPSHOT;
	// Alias for Print Screen
	TKeyboard::specialKeysMap["PAUSE"] = VK_PAUSE; // Pause Break

	// Populate charToVkMap using VkKeyScan for a more robust mapping.
	// VkKeyScan determines the virtual key code and shift state required for a character
	// based on the current keyboard layout. This is crucial for international layouts.
	for (int i = 32; i <= 126; ++i) { // Iterate through printable ASCII range
		char c = (char)i;
		SHORT vk_scan_info = VkKeyScan(c); // Get VK code and shift state
		if (vk_scan_info != -1) { // If a mapping exists
			WORD vk_code = LOBYTE(vk_scan_info); // Low byte is the VK code
			bool needs_shift = (HIBYTE(vk_scan_info) & 1) != 0;
			// High byte bit 0 indicates Shift
			TKeyboard::charToVkMap[c] = KeyMapping(vk_code, needs_shift);
		}
	}
}

/**
 * @brief Private static helper to get VK code and shift information for a character.
 * It first checks the pre-populated charToVkMap. If not found, it tries VkKeyScan directly.
 * @param c The character to map.
 * @return KeyMapping struct containing the VK code and needsShift flag.
 * @throws std::runtime_error if no virtual key code is found for the character.
 */
KeyMapping TKeyboard::get_char_key_mapping(char c) {
	std::map<char, KeyMapping>::iterator it = TKeyboard::charToVkMap.find(c);
	if (it != TKeyboard::charToVkMap.end()) {
		return it->second; // Return from pre-populated map
	}
	// Fallback: If not in map, try VkKeyScan directly. This might be for less common chars.
	SHORT vk_scan_info = VkKeyScan(c);
	if (vk_scan_info != -1) {
		WORD vk_code = LOBYTE(vk_scan_info);
		bool needs_shift = (HIBYTE(vk_scan_info) & 1) != 0;
		return KeyMapping(vk_code, needs_shift);
	}
	// If no mapping is found, throw an exception.
	std::stringstream ss;
	ss << "Warning: No virtual key code found for character: '" << c << "'";
	throw std::runtime_error(ss.str());
}

/**
 * @brief Private static helper to press a key (VK code).
 * Used internally by the class methods to abstract the send_key_event call.
 * @param vkCode The virtual key code of the key to press.
 */
void TKeyboard::internal_press_key_vk(WORD vkCode) {
	send_key_event(vkCode, 0); // 0 flags for key press
}

/**
 * @brief Private static helper to release a key (VK code).
 * Used internally by the class methods to abstract the send_key_event call.
 * @param vkCode The virtual key code of the key to release.
 */
void TKeyboard::internal_release_key_vk(WORD vkCode) {
	send_key_event(vkCode, KEYEVENTF_KEYUP); // KEYEVENTF_KEYUP for key release
}

/**
 * @brief Releases all modifiers currently held in the modifier_scope_stack.
 * This is a cleanup function, especially important before throwing exceptions.
 * @param modifier_scope_stack The stack containing currently active modifiers.
 */
void TKeyboard::release_all_modifiers
	(std::stack<std::vector<WORD> >& modifier_scope_stack) {
	while (!modifier_scope_stack.empty()) {
		std::vector<WORD>&current_mods = modifier_scope_stack.top();
		for (unsigned int j = 0; j < current_mods.size(); ++j) {
			internal_release_key_vk(current_mods[j]); // Release each modifier
			internal_sleep(); // Small delay after releasing each modifier
		}
		modifier_scope_stack.pop(); // Pop the scope from the stack
	}
}

/**
 * @brief Public static method to press a key using its virtual key code.
 * Provides direct, non-instantiated utility access for low-level control.
 * @param vkCode The virtual key code of the key to press.
 */
void TKeyboard::press_key_vk(WORD vkCode) {
	internal_press_key_vk(vkCode);
}

/**
 * @brief Public static method to release a key using its virtual key code.
 * Provides direct, non-instantiated utility access for low-level control.
 * @param vkCode The virtual key code of the key to release.
 */
void TKeyboard::release_key_vk(WORD vkCode) {
	internal_release_key_vk(vkCode);
}

/**
 * @brief Simulates pressing a single character key.
 * Handles the Shift key automatically for uppercase characters or symbols that require it.
 * @param keyChar The character to press.
 * @throws std::runtime_error if the character cannot be mapped to a virtual key code.
 */
void TKeyboard::press(char keyChar) {
	KeyMapping mapping = get_char_key_mapping(keyChar);
	// get_char_key_mapping throws if vkCode is 0, so no need to check here.

	if (mapping.needsShift) {
		internal_press_key_vk(VK_SHIFT);
		// Press Shift if the character requires it
		internal_sleep(); // Small delay to ensure Shift registers
	}
	internal_press_key_vk(mapping.vkCode); // Press the actual character key
}

/**
 * @brief Simulates releasing a single character key.
 * Handles releasing the Shift key if it was pressed for the character.
 * @param keyChar The character to release.
 * @throws std::runtime_error if the character cannot be mapped to a virtual key code.
 */
void TKeyboard::release(char keyChar) {
	KeyMapping mapping = get_char_key_mapping(keyChar);
	// get_char_key_mapping throws if vkCode is 0, so no need to check here.

	internal_release_key_vk(mapping.vkCode); // Release the actual character key
	if (mapping.needsShift) {
		internal_sleep(); // Small delay before releasing Shift
		internal_release_key_vk(VK_SHIFT); // Release Shift if it was pressed
	}
}

/**
 * @brief Simulates typing a string of text character by character.
 * Manages Shift key for uppercase characters and common symbols, mimicking
 * the behavior of Python's keyboard libraries.
 * @param text The string to type.
 * @throws std::runtime_error if any character in the string cannot be mapped.
 */
void TKeyboard::write(const std::string& text) {
	// Ensure maps are initialized on the first call.
	if (!mapsInitialized) {
		init_maps();
		mapsInitialized = true;
	}

	for (unsigned int i = 0; i < text.length(); ++i) {
		char c = text[i];
		try {
			KeyMapping mapping = get_char_key_mapping(c);
			// get_char_key_mapping throws if vkCode is 0, so no need to check here.

			if (mapping.needsShift) {
				internal_press_key_vk(VK_SHIFT);
				// Press Shift if the character requires it
				internal_sleep(); // Delay after pressing modifier
			}

			internal_press_key_vk(mapping.vkCode); // Press the character key
			internal_sleep(); // Delay after pressing character
			internal_release_key_vk(mapping.vkCode);
			// Release the character key

			if (mapping.needsShift) {
				internal_sleep(); // Delay before releasing modifier
				internal_release_key_vk(VK_SHIFT);
				// Release Shift if it was pressed
			}
			internal_sleep(); // Delay after the full character cycle
		}
		catch (const std::runtime_error& e) {
			// Re-throw the exception to the caller.
			throw e;
		}
	}
}

/**
 * @brief Simulates typing a macro string, similar to Visual Basic's SendKeys function.
 * Supports modifier prefixes (+, ^, %, *), special keys ({F1}, {ENTER}),
 * escape sequences ({+}, {()}), and grouping with parentheses.
 * Modifiers preceding a group apply to the entire content within the group.
 * @param macroString The macro string to process.
 * @throws std::runtime_error for syntax errors (mismatched braces/parentheses, unknown keys).
 */
void TKeyboard::writeMacro(const std::string& macroString) {
	// Ensure maps are initialized on the first call.
	if (!mapsInitialized) {
		init_maps();
		mapsInitialized = true;
	}

	// Stack to manage the *set* of currently active modifiers for each scope.
	// Each element in the stack is a vector representing the modifiers that are
	// currently pressed and should remain held for the current processing scope.
	// This allows for correct handling of nested groups and modifier persistence.
	std::stack<std::vector<WORD> >modifier_scope_stack;
	// Push an initial empty vector for the base scope (no modifiers active initially).
	modifier_scope_stack.push(std::vector<WORD>());

	// Iterate through the macro string character by character.
	for (unsigned int i = 0; i < macroString.length(); ++i) {
		char current_char = macroString[i];

		try {
			// 1. Handle modifier prefixes (+, ^, %, *).
			// Check if the current character is a known modifier symbol.
			std::map<char, WORD>::iterator modifier_it =
				modifierMap.find(current_char);
			if (modifier_it != modifierMap.end()) {
				WORD modifier_vk = modifier_it->second;
				// Get the VK code for the modifier
				internal_press_key_vk(modifier_vk); // Press the modifier key
				// Add the pressed modifier to the current scope's active modifiers.
				modifier_scope_stack.top().push_back(modifier_vk);
				internal_sleep(); // Small delay after pressing modifier
				continue; // Move to the next character in the macro string
			}

			// 2. Handle grouping start '('.
			// When an opening parenthesis is found, it signifies the start of a new group.
			if (current_char == '(') {
				// Push a *copy* of the current active modifiers onto the stack.
				// This ensures that modifiers from the outer scope are inherited by the inner scope,
				// meaning they remain pressed throughout the inner group's execution.
				modifier_scope_stack.push(modifier_scope_stack.top());
				internal_sleep();
				continue; // Move to the next character (inside the group)
			}

			// 3. Handle grouping end ')'.
			// When a closing parenthesis is found, it signifies the end of the current group.
			if (current_char == ')') {
				// Check if there's a corresponding opening parenthesis scope to pop.
				// If stack size is 1, it means we are at the base scope and cannot pop further.
				if (modifier_scope_stack.size() <= 1) {
					release_all_modifiers(modifier_scope_stack);
					// Clean up modifiers before throwing
					std::stringstream ss;
					ss << "Error: Mismatched closing parenthesis in macro string at index "
						<< i;
					throw std::runtime_error(ss.str());
				}

				// Get the modifiers that were active in the scope that is now being exited.
				std::vector<WORD>mods_in_exiting_scope =
					modifier_scope_stack.top();
				modifier_scope_stack.pop();
				// Pop the current scope from the stack.

				// Get the modifiers that will be active in the new current scope (which is the parent scope).
				std::vector<WORD>&new_current_scope_mods =
					modifier_scope_stack.top();

				// Release only those modifiers that were in the exiting scope but are NOT
				// in the new current (parent) scope. This ensures that inherited modifiers
				// from outer scopes remain pressed.
				for (unsigned int k = 0; k < mods_in_exiting_scope.size(); ++k)
				{
					bool found_in_new_scope = false;
					// Use std::find for better readability and efficiency than manual loop
					if (std::find(new_current_scope_mods.begin(),
						new_current_scope_mods.end(), mods_in_exiting_scope[k])
						!= new_current_scope_mods.end()) {
						found_in_new_scope = true;
					}
					if (!found_in_new_scope) {
						internal_release_key_vk(mods_in_exiting_scope[k]);
						internal_sleep();
					}
				}
				internal_sleep();
				continue; // Move to the next character (after the group)
			}

			// 4. Handle special key or escape sequence enclosed in curly braces '{...}'.
			if (current_char == '{') {
				// Find the closing curly brace.
				unsigned int brace_end = macroString.find('}', i);
				if (brace_end == std::string::npos) {
					release_all_modifiers(modifier_scope_stack);
					// Clean up modifiers before throwing
					std::stringstream ss;
					ss << "Error: Mismatched curly brace in macro string at index "
						<< i;
					throw std::runtime_error(ss.str());
				}
				// Extract the content inside the curly braces.
				std::string key_content =
					macroString.substr(i + 1, brace_end - i - 1);

				// First, check if it's an escaped literal character (e.g., "{+}" for a literal plus sign).
				std::map<std::string, char>::iterator escaped_it =
					escapedCharsMap.find(key_content);
				if (escaped_it != escapedCharsMap.end()) {
					char literal_char = escaped_it->second;
					// Get the actual literal character
					KeyMapping mapping = get_char_key_mapping(literal_char);
					// Get its VK code and Shift info
					// get_char_key_mapping throws if vkCode is 0, so no need to check here.

					// Apply Shift if the literal character requires it.
					if (mapping.needsShift) {
						internal_press_key_vk(VK_SHIFT);
						internal_sleep();
					}
					internal_press_key_vk(mapping.vkCode);
					// Press the literal character key
					internal_sleep();
					internal_release_key_vk(mapping.vkCode);
					// Release the literal character key
					if (mapping.needsShift) {
						internal_sleep();
						internal_release_key_vk(VK_SHIFT); // Release Shift
					}
					internal_sleep();
				}
				// If not an escaped character, check if it's a known special key (e.g., "{F1}", "{ENTER}").
				else {
					std::map<std::string, WORD>::iterator special_it =
						specialKeysMap.find(key_content);
					if (special_it != specialKeysMap.end()) {
						WORD vk_code = special_it->second;
						// Get the VK code for the special key
						internal_press_key_vk(vk_code); // Press the special key
						internal_sleep();
						internal_release_key_vk(vk_code);
						// Release the special key
						internal_sleep();
					}
					else {
						// If the content inside braces is neither an escaped char nor a special key, it's an error.
						release_all_modifiers(modifier_scope_stack);
						// Clean up modifiers before throwing
						std::stringstream ss;
						ss << "Error: Unknown special key or escape sequence: {"
							<< key_content << "} at index " << i;
						throw std::runtime_error(ss.str());
					}
				}
				i = brace_end; // Move the loop index past the closing brace
				continue; // Move to the next character after the brace sequence
			}

			// 5. Handle '~' (tilde), which is a shortcut for the ENTER key.
			if (current_char == '~') {
				internal_press_key_vk(VK_RETURN); // Press Enter
				internal_sleep();
				internal_release_key_vk(VK_RETURN); // Release Enter
				internal_sleep();
				continue; // Move to the next character
			}

			// 6. Handle literal characters (any character not matched by the above rules).
			KeyMapping mapping = get_char_key_mapping(current_char);
			// Get VK code and Shift info for the character
			// get_char_key_mapping throws if vkCode is 0, so no need to check here.

			if (mapping.needsShift) {
				internal_press_key_vk(VK_SHIFT);
				// Press Shift if the character requires it
				internal_sleep(); // Delay after pressing modifier
			}
			internal_press_key_vk(mapping.vkCode);
			// Press the literal character key
			internal_sleep(); // Delay after pressing character
			internal_release_key_vk(mapping.vkCode);
			// Release the literal character key
			if (mapping.needsShift) {
				internal_sleep(); // Delay before releasing modifier
				internal_release_key_vk(VK_SHIFT); // Release Shift
			}
			internal_sleep(); // Delay after the full character cycle

		}
		catch (const std::runtime_error& e) {
			// Re-throw the exception to the caller after ensuring modifiers are released.
			release_all_modifiers(modifier_scope_stack);
			// Ensure all modifiers are released on error
			throw e;
		}
	}

	// After processing the entire macro string, release any modifiers that are still pressed
	// from the base scope or any unclosed scopes (in case of error).
	release_all_modifiers(modifier_scope_stack);
}
