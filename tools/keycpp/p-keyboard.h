#include <string>    // For string manipulation (std::string)
#include <windows.h> // For Windows API calls (SendInput, MapVirtualKeyA, Sleep, VK_*, KEYEVENTF_*)
#include <stdexcept>    // For std::exception
#include <map>       // For std::map (character to virtual key code mapping)
#include <cctype>    // For tolower (C-style character conversion)

// Define a small delay to simulate human typing speed and allow OS to process events.
// This is crucial for reliable UI automation.
const int TYPING_DELAY_MS = 20;

/**
 * @brief TKeyboard class provides methods to simulate keyboard input.
 *        It offers both static utility functions and virtual instance methods
 *        for polymorphic behavior.
 */
class TPreviousKeyboard {
private:
	// List of virtual key codes that require the KEYEVENTF_EXTENDEDKEY flag.
	// Defined as a static array for compatibility with older C++ standards.
	static const WORD extended_key_codes[];

	static const int extended_key_codes_count;

	/**
	 * @brief Checks if a given virtual key code is considered an extended key.
	 *        Extended keys often require the KEYEVENTF_EXTENDEDKEY flag.
	 * @param vkCode The virtual key code to check.
	 * @return True if the key is an extended key, false otherwise.
	 */
	static bool is_extended_key(WORD vkCode) {
		for (int i = 0; i < extended_key_codes_count; ++i) {
			if (TPreviousKeyboard::extended_key_codes[i] == vkCode) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Sends a single keyboard event (press or release) to the system.
	 *        This is the lowest-level abstraction interacting directly with SendInput.
	 * @param vkCode The virtual key code of the key.
	 * @param dwFlags Flags for the key event (e.g., KEYEVENTF_KEYUP for release).
	 */
	static void send_key_event(WORD vkCode, DWORD dwFlags) {
		INPUT input = {0}; // Initialize INPUT structure to all zeros
		input.type = INPUT_KEYBOARD; // Specify keyboard input

		input.ki.wVk = vkCode; // Set the virtual key code
		// Map virtual key code to scan code for robustness.
		// MapVirtualKeyA is used for ANSI character sets.
		input.ki.wScan = MapVirtualKeyA(vkCode, MAPVK_VK_TO_VSC);
		input.ki.dwFlags = dwFlags; // Set flags (press or release)

		// If the key is an extended key, add the extended flag.
		// This is crucial for correct behavior of certain keys (e.g., right ALT, arrow keys).
		if (is_extended_key(vkCode)) {
			input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
		}

		// Send the input event. SendInput returns the number of events successfully inserted.
		UINT result = SendInput(1, &input, sizeof(INPUT));
		if (result != 1) {
			// Log an error if SendInput fails for debugging purposes.
			// std::cerr << "Error: SendInput failed for VK: 0x" << std::hex << vkCode << std::endl;
			throw std::runtime_error("Error: SendInput failed for VK: 0x");
			// std::hex << vkCode << std::endl;
		}
	}

	/**
	 * @brief Provides a static map for character to virtual key code mappings.
	 *        This function ensures the map is initialized only once,
	 *        compatible with older C++ standards that might not fully support
	 *        static const map initializer lists.
	 * @return A reference to the static map.
	 */
	static std::map<char, WORD>& get_char_map() {
		static std::map<char, WORD>charMap;
		if (charMap.empty()) { // Populate only once
			charMap['a'] = 0x41;
			charMap['b'] = 0x42;
			charMap['c'] = 0x43;
			charMap['d'] = 0x44;
			charMap['e'] = 0x45;
			charMap['f'] = 0x46;
			charMap['g'] = 0x47;
			charMap['h'] = 0x48;
			charMap['i'] = 0x49;
			charMap['j'] = 0x4A;
			charMap['k'] = 0x4B;
			charMap['l'] = 0x4C;
			charMap['m'] = 0x4D;
			charMap['n'] = 0x4E;
			charMap['o'] = 0x4F;
			charMap['p'] = 0x50;
			charMap['q'] = 0x51;
			charMap['r'] = 0x52;
			charMap['s'] = 0x53;
			charMap['t'] = 0x54;
			charMap['u'] = 0x55;
			charMap['v'] = 0x56;
			charMap['w'] = 0x57;
			charMap['x'] = 0x58;
			charMap['y'] = 0x59;
			charMap['z'] = 0x5A;
			charMap['0'] = 0x30;
			charMap['1'] = 0x31;
			charMap['2'] = 0x32;
			charMap['3'] = 0x33;
			charMap['4'] = 0x34;
			charMap['5'] = 0x35;
			charMap['6'] = 0x36;
			charMap['7'] = 0x37;
			charMap['8'] = 0x38;
			charMap['9'] = 0x39;
			charMap[' '] = VK_SPACE;
			charMap['\t'] = VK_TAB;
			charMap['\n'] = VK_RETURN;
			// Common symbols (US keyboard layout assumed for simplicity)
			// These VK codes are from Microsoft documentation [1]
			charMap[';'] = VK_OEM_1;
			charMap['='] = VK_OEM_PLUS;
			charMap[','] = VK_OEM_COMMA;
			charMap['-'] = VK_OEM_MINUS;
			charMap['.'] = VK_OEM_PERIOD;
			charMap['/'] = VK_OEM_2;
			charMap['`'] = VK_OEM_3;
			charMap['['] = VK_OEM_4;
			charMap['\\'] = VK_OEM_5;
			charMap[']'] = VK_OEM_6;
			charMap['\''] = VK_OEM_7;
		}
		return charMap;
	}

	/**
	 * @brief Maps a common character to its corresponding virtual key code.
	 *        Handles alphanumeric and some common symbol keys.
	 * @param c The character to map.
	 * @return The virtual key code, or 0 if not found.
	 */
	static WORD char_to_vk_code(char c) {
		char lower_c = tolower(c);
		// Convert to lowercase for mapping (from <cctype>)
		std::map<char, WORD>&charMap = get_char_map();
		// Use iterator for map lookup, compatible with older C++ standards
		std::map<char, WORD>::const_iterator it = charMap.find(lower_c);
		if (it == charMap.end()) {
			// std::cerr << "Warning: No virtual key code found for character: '" << c << "'" << std::endl;
			throw std::runtime_error
				("Warning: No virtual key code found for character: '");
		}

		return it->second;
		// return 0; // Return 0 for unknown characters
	}

public:
	/**
	 * @brief Static method to press a key using its virtual key code.
	 *        This provides direct, non-instantiated utility access.
	 * @param vkCode The virtual key code of the key to press.
	 */
	static void press_key_vk(WORD vkCode) {
		send_key_event(vkCode, 0); // 0 flags for key press
	}

	/**
	 * @brief Static method to release a key using its virtual key code.
	 *        This provides direct, non-instantiated utility access.
	 * @param vkCode The virtual key code of the key to release.
	 */
	static void release_key_vk(WORD vkCode) {
		send_key_event(vkCode, KEYEVENTF_KEYUP);
		// KEYEVENTF_KEYUP for key release
	}

	/**
	 * @brief Virtual method to simulate pressing a single character key.
	 *        This is an instance method, allowing for polymorphism.
	 *        Handles Shift for uppercase characters.
	 * @param keyChar The character to press.
	 */
	virtual void press(char keyChar) {
		WORD vkCode = char_to_vk_code(keyChar);
		if (vkCode == 0)
			return; // Do nothing if character is not mapped

		bool is_uppercase = (keyChar >= 'A' && keyChar <= 'Z');
		if (is_uppercase) {
			TPreviousKeyboard::press_key_vk(VK_SHIFT);
			// Press Shift for uppercase [1]
			Sleep(TYPING_DELAY_MS); // Small delay to ensure Shift is registered
		}
		TPreviousKeyboard::press_key_vk(vkCode);
	}

	/**
	 * @brief Virtual method to simulate releasing a single character key.
	 *        This is an instance method, allowing for polymorphism.
	 *        Handles releasing Shift if it was pressed for an uppercase character.
	 * @param keyChar The character to release.
	 */
	virtual void release(char keyChar) {
		WORD vkCode = char_to_vk_code(keyChar);
		if (vkCode == 0)
			return; // Do nothing if character is not mapped

		TPreviousKeyboard::release_key_vk(vkCode);
		bool is_uppercase = (keyChar >= 'A' && keyChar <= 'Z');
		if (is_uppercase) {
			Sleep(TYPING_DELAY_MS); // Small delay
			TPreviousKeyboard::release_key_vk(VK_SHIFT); // Release Shift [1]
		}
	}

	/**
	 * @brief Virtual method to simulate typing a string of text.
	 *        This is an instance method, allowing for polymorphism.
	 *        Manages Shift key for uppercase characters, mimicking Python's library behavior.
	 * @param text The string to type.
	 */
	virtual void write(const std::string& text) {
		// Use traditional for loop for compatibility with older C++ standards (e.g., C++ Builder XE 32-bit)
		for (unsigned int i = 0; i < text.length(); ++i) {
			char c = text[i];
			WORD vkCode = char_to_vk_code(c);
			if (vkCode == 0)
				continue; // Skip unknown characters

			bool is_uppercase = (c >= 'A' && c <= 'Z');
			bool needs_shift = is_uppercase;
			// For simple alphanumeric, shift is only for uppercase

			// For symbols, a more complex mapping might be needed (e.g., '!' requires Shift+1).
			// This implementation handles Shift for uppercase letters based on their VK codes.

			if (needs_shift) {
				TPreviousKeyboard::press_key_vk(VK_SHIFT);
				Sleep(TYPING_DELAY_MS);
			}

			TPreviousKeyboard::press_key_vk(vkCode);
			Sleep(TYPING_DELAY_MS);
			TPreviousKeyboard::release_key_vk(vkCode);

			if (needs_shift) {
				Sleep(TYPING_DELAY_MS);
				TPreviousKeyboard::release_key_vk(VK_SHIFT);
			}
			Sleep(TYPING_DELAY_MS); // Delay between characters
		}
	}
};
