// TKeyboard.h
#ifndef TKEYBOARD_H
#define TKEYBOARD_H

#include <string>    // For std::string
#include <windows.h> // For WORD, DWORD, INPUT, KEYEVENTF_*, VK_*, SendInput, MapVirtualKeyA, Sleep
#include <vector>    // For std::vector
#include <map>       // For std::map
#include <stack>     // For std::stack (used in writeMacro for modifier scope)
#include <cctype>    // For std::tolower
#include <stdexcept> // For std::runtime_error

// Define _USE_STD_CHRONO_AND_THREAD if your compiler supports C++11 std::chrono and std::thread.
// If not defined, the code will default to using Windows' Sleep() function.
// #define _USE_STD_CHRONO_AND_THREAD

#ifdef _USE_STD_CHRONO_AND_THREAD
#include <chrono>     // For std::chrono::milliseconds
#include <thread>     // For std::this_thread::sleep_for
#endif

// Define a small delay to simulate human typing speed and allow OS to process events.
// This is crucial for reliable UI automation.
const int TYPING_DELAY_MS = 40;
// Increased delay slightly for better reliability

// Structure to hold a key mapping: Virtual Key Code and if Shift is needed.
// This helps in mapping characters to their corresponding keyboard actions.
struct KeyMapping {
	WORD vkCode; // The Virtual Key Code (e.g., VK_A, VK_RETURN)
	bool needsShift;
	// True if this character typically requires Shift (e.g., 'A', '!')

	// Constructor for easier initialization of KeyMapping objects.
	KeyMapping(WORD vk = 0, bool shift = false) : vkCode(vk), needsShift(shift)
	{
	}
};

/**
 * @brief TKeyboard class provides methods to simulate keyboard input.
 * It offers both static utility functions for direct VK code control
 * and virtual instance methods for polymorphic behavior and higher-level
 * text/macro input.
 */
class TKeyboard {
private:
	// Static maps for key definitions, initialized once to improve performance
	// by avoiding repeated lookups or re-initialization.
		static std::map<std::string, WORD>specialKeysMap;
	// Maps special key names (e.g., "F1", "ENTER") to VK codes.
	static std::map<char, WORD>modifierMap;
	// Maps modifier symbols (e.g., '+', '^') to VK codes.
	static std::map<std::string, char>escapedCharsMap;
	// Maps escaped sequences (e.g., "{+}") to literal chars.
	static std::map<char, KeyMapping>charToVkMap;
	// Maps common characters to their VK code and Shift requirement.

	// Flag to ensure maps are initialized only once across all instances and static calls.
	static bool mapsInitialized;

	/**
	 * @brief Sends a single keyboard event (press or release) to the system.
	 * This is the lowest-level abstraction, interacting directly with the Windows SendInput API.
	 * @param vkCode The virtual key code of the key to send.
	 * @param dwFlags Flags for the key event (e.g., 0 for press, KEYEVENTF_KEYUP for release).
	 * @throws std::runtime_error if SendInput fails.
	 */
	static void send_key_event(WORD vkCode, DWORD dwFlags);

	/**
	 * @brief Initializes all static maps used for key mappings.
	 * This function is called once on the first use of any TKeyboard functionality.
	 */
	static void init_maps();

	/**
	 * @brief Private static helper to get VK code and shift information for a character.
	 * It looks up the character in charToVkMap or uses VkKeyScan as a fallback.
	 * @param c The character to map.
	 * @return KeyMapping struct containing the VK code and needsShift flag.
	 * @throws std::runtime_error if no virtual key code is found for the character.
	 */
	static KeyMapping get_char_key_mapping(char c);

	/**
	 * @brief Private static helper to press a key using its virtual key code.
	 * Used internally by the class methods.
	 * @param vkCode The virtual key code of the key to press.
	 */
	static void internal_press_key_vk(WORD vkCode);

	/**
	 * @brief Private static helper to release a key using its virtual key code.
	 * Used internally by the class methods.
	 * @param vkCode The virtual key code of the key to release.
	 */
	static void internal_release_key_vk(WORD vkCode);

	/**
	 * @brief Releases all modifiers currently held in the modifier_scope_stack.
	 * This is a cleanup function, especially important before throwing exceptions.
	 * @param modifier_scope_stack The stack containing currently active modifiers.
	 */
	static void release_all_modifiers
		(std::stack<std::vector<WORD> >& modifier_scope_stack);

	/**
	 * @brief Internal helper function for controlled delays.
	 * Uses std::this_thread::sleep_for or Windows' Sleep() based on _USE_STD_CHRONO_AND_THREAD define.
	 * @param milliseconds The duration of the sleep in milliseconds. Defaults to TYPING_DELAY_MS.
	 */
	static void internal_sleep(DWORD milliseconds = TYPING_DELAY_MS);

public:
	// Public static methods for direct virtual key code control.
	// These allow for low-level key manipulation without instantiating the class.
	static void press_key_vk(WORD vkCode);
	static void release_key_vk(WORD vkCode);

	// Virtual instance methods for polymorphism.
	// These methods can be overridden by derived classes to customize behavior.

	/**
	 * @brief Simulates pressing a single character key.
	 * Handles the Shift key automatically for uppercase characters or symbols that require it.
	 * @param keyChar The character to press.
	 * @throws std::runtime_error if the character cannot be mapped to a virtual key code.
	 */
	virtual void press(char keyChar);

	/**
	 * @brief Simulates releasing a single character key.
	 * Handles releasing the Shift key if it was pressed for the character.
	 * @param keyChar The character to release.
	 * @throws std::runtime_error if the character cannot be mapped to a virtual key code.
	 */
	virtual void release(char keyChar);

	/**
	 * @brief Simulates typing a string of text character by character.
	 * Manages Shift key for uppercase characters and common symbols, mimicking
	 * the behavior of Python's keyboard libraries.
	 * @param text The string to type.
	 * @throws std::runtime_error if any character in the string cannot be mapped.
	 */
	virtual void write(const std::string& text);

	/**
	 * @brief Simulates typing a macro string, similar to Visual Basic's SendKeys function.
	 * Supports modifier prefixes (+, ^, %, *), special keys ({F1}, {ENTER}),
	 * escape sequences ({+}, {()}), and grouping with parentheses.
	 * Modifiers preceding a group apply to the entire content within the group.
	 * @param macroString The macro string to process.
	 * @throws std::runtime_error for syntax errors (mismatched braces/parentheses, unknown keys).
	 */
	virtual void writeMacro(const std::string& macroString);

	/**
	 * @brief Constructor for the TKeyboard class.
	 * Ensures that static maps are initialized only once when the first instance
	 * is created or a static method is called.
	 */
	TKeyboard() {
		if (!mapsInitialized) {
			init_maps();
			mapsInitialized = true;
		}
	}
};

#endif // TKEYBOARD_H
