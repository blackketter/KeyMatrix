#ifndef _KeyInfo_
#define _KeyInfo_
#include "keylayouts.h"
#include "KeyIcons.h"

typedef uint16_t keycode_t;

// some new key codes
const keycode_t NO_CODE = 0;
const keycode_t ANY_CODE = 1;
const keycode_t KEY_LEFT_FN = 200;
const keycode_t KEY_RIGHT_FN = 201;

const keycode_t KEY_TOP_PAD = 202;
const keycode_t KEY_BOTTOM_PAD = 203;
const keycode_t KEY_LEFT_PAD = 204;
const keycode_t KEY_RIGHT_PAD = 205;

const keycode_t KEY_EXIT = 206;

// 207 available

const keycode_t KEY_MOUSE_MOVE_UP         = 208;
const keycode_t KEY_MOUSE_MOVE_DOWN       = 209;
const keycode_t KEY_MOUSE_MOVE_LEFT       = 210;
const keycode_t KEY_MOUSE_MOVE_RIGHT      = 211;
const keycode_t KEY_MOUSE_BUTTON_LEFT     = 212;
const keycode_t KEY_MOUSE_BUTTON_MIDDLE   = 213;
const keycode_t KEY_MOUSE_BUTTON_RIGHT    = 214;
const keycode_t KEY_MOUSE_BUTTON_BACK     = 215;
const keycode_t KEY_MOUSE_BUTTON_FORWARD  = 216;
const keycode_t KEY_MOUSE_SCROLL_UP       = 217;
const keycode_t KEY_MOUSE_SCROLL_DOWN     = 218;
const keycode_t KEY_MOUSE_SCROLL_LEFT     = 219;
const keycode_t KEY_MOUSE_SCROLL_RIGHT    = 220;

// 221, 222 available

const keycode_t KEY_FIRST_MACRO           = 223; // leave room for 12 macros for now
const keycode_t KEY_MACRO_TOTAL           = 12;
//const keycode_t nextavailable           = KEY_FIRST_MACRO + KEY_MACRO_TOTAL;

const keycode_t MAX_SOFT_KEY = 255;

typedef uint8_t keycategory_t;

enum keyCategory {
  KEY_CATEGORY_NONE,
  KEY_CATEGORY_ALPHA,
  KEY_CATEGORY_NUM,
  KEY_CATEGORY_PUNCTUATION,
  KEY_CATEGORY_TEXT,
  KEY_CATEGORY_MODIFIER,
  KEY_CATEGORY_FUNCTION,
  KEY_CATEGORY_CURSOR,
  KEY_CATEGORY_SYSTEM,
  KEY_CATEGORY_MACRO,
  KEY_CATEGORY_MOUSE,
  KEY_CATEGORY_MEDIA,
  KEY_CATEGORY_KEYPAD
};

typedef struct modifiedkey_t {
  keycode_t code;
  char c;
} modifiedkey_t;

const modifiedkey_t shiftedKeys[] = {
  { KEY_A, 'A' },
  { KEY_B, 'B' },
  { KEY_C, 'C' },
  { KEY_D, 'D' },
  { KEY_E, 'E' },
  { KEY_F, 'F' },
  { KEY_G, 'G' },
  { KEY_H, 'H' },
  { KEY_I, 'I' },
  { KEY_J, 'J' },
  { KEY_K, 'K' },
  { KEY_L, 'L' },
  { KEY_M, 'M' },
  { KEY_N, 'N' },
  { KEY_O, 'O' },
  { KEY_P, 'P' },
  { KEY_Q, 'Q' },
  { KEY_R, 'R' },
  { KEY_S, 'S' },
  { KEY_T, 'T' },
  { KEY_U, 'U' },
  { KEY_V, 'V' },
  { KEY_W, 'W' },
  { KEY_X, 'X' },
  { KEY_Y, 'Y' },
  { KEY_Z, 'Z' },
  { KEY_1, '!' },
  { KEY_2, '@' },
  { KEY_3, '#' },
  { KEY_4, '$' },
  { KEY_5, '%' },
  { KEY_6, '^' },
  { KEY_7, '&' },
  { KEY_8, '*' },
  { KEY_9, '(' },
  { KEY_0, ')' },
  { KEY_MINUS, '_' },
  { KEY_EQUAL, '+' },
  { KEY_LEFT_BRACE, '{' },
  { KEY_RIGHT_BRACE, '}' },
  { KEY_BACKSLASH, '|' },
  { KEY_SEMICOLON, ':' },
  { KEY_QUOTE, '"' },
  { KEY_TILDE, '~' }, // tilde key is actually a ` in EN_US
  { KEY_COMMA, '<' },
  { KEY_PERIOD, '>' },
  { KEY_SLASH, '?' },
  { NO_CODE, 0 },
};

typedef struct keyinfo_t {
  const keycode_t code;
  const char c;
  const char* const label;
  const icon_t icon;
  const keycategory_t category;
} keyinfo_t;

const keyinfo_t keyInfo[] = {
// nonstandard keys
  { KEY_LEFT_FN, 0, "fn", nullptr, KEY_CATEGORY_MODIFIER },
  { KEY_RIGHT_FN, 0, "fn", nullptr, KEY_CATEGORY_MODIFIER },

  { KEY_MOUSE_MOVE_UP, 0, "mouse up", mouseUpIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_MOVE_DOWN, 0, "mouse down", mouseDownIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_MOVE_LEFT, 0, "mouse left", mouseLeftIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_MOVE_RIGHT, 0, "mouse right", mouseRightIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_BUTTON_LEFT, 0, "mouse button left", mouseButtonLeftIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_BUTTON_MIDDLE, 0, "mouse button middle", mouseButtonMiddleIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_BUTTON_RIGHT, 0, "mouse button right", mouseButtonRightIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_BUTTON_BACK, 0, "mouse button back", mouseButtonBackIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_BUTTON_FORWARD, 0, "mouse button fwd", mouseButtonFwdIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_SCROLL_UP, 0, "mouse scroll up", mouseScrollUpIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_SCROLL_DOWN, 0, "mouse scroll down", mouseScrollDownIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_SCROLL_LEFT, 0, "mouse scroll left", mouseScrollLeftIcon, KEY_CATEGORY_MOUSE },
  { KEY_MOUSE_SCROLL_RIGHT, 0, "mouse scroll right", mouseScrollRightIcon, KEY_CATEGORY_MOUSE },

  { KEY_MENU, 0, "menu", nullptr, KEY_CATEGORY_SYSTEM },

// standard keys
  { MODIFIERKEY_LEFT_CTRL, 0, "left ctrl", controlIcon, KEY_CATEGORY_MODIFIER },
  { MODIFIERKEY_LEFT_SHIFT, 0, "left shift", shiftIcon, KEY_CATEGORY_MODIFIER },
  { MODIFIERKEY_LEFT_ALT, 0, "left opt", optionIcon, KEY_CATEGORY_MODIFIER },
  { MODIFIERKEY_LEFT_GUI, 0, "left cmd", commandIcon, KEY_CATEGORY_MODIFIER },
  { MODIFIERKEY_RIGHT_CTRL, 0, "right ctrl", controlIcon, KEY_CATEGORY_MODIFIER },
  { MODIFIERKEY_RIGHT_SHIFT, 0, "right shift", shiftIcon, KEY_CATEGORY_MODIFIER },
  { MODIFIERKEY_RIGHT_ALT, 0, "right opt", optionIcon, KEY_CATEGORY_MODIFIER },
  { MODIFIERKEY_RIGHT_GUI, 0, "right cmd", commandIcon, KEY_CATEGORY_MODIFIER },

  { KEY_SYSTEM_POWER_DOWN, 0, "pow", nullptr, KEY_CATEGORY_SYSTEM },
  { KEY_SYSTEM_SLEEP, 0, "sleep", nullptr, KEY_CATEGORY_SYSTEM },
  { KEY_SYSTEM_WAKE_UP, 0, "wake", nullptr, KEY_CATEGORY_SYSTEM },

  { KEY_MEDIA_PLAY, 0, "play", playIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_PAUSE, 0, "pause", pauseIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_RECORD, 0, "rec", recordIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_FAST_FORWARD, 0, "ffw", ffIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_REWIND, 0, "rew", rewIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_NEXT_TRACK, 0, "next", ffIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_PREV_TRACK, 0, "prev", rewIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_STOP, 0, "stop", stopIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_EJECT, 0, "eject", ejectIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_RANDOM_PLAY, 0, "random", nullptr, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_PLAY_PAUSE, 0, "pause", pauseIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_PLAY_SKIP, 0, "skip", ffIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_MUTE, 0, "mute", muteIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_VOLUME_INC, 0, "vol+", volPlusIcon, KEY_CATEGORY_MEDIA },
  { KEY_MEDIA_VOLUME_DEC, 0, "vol-", volMinusIcon, KEY_CATEGORY_MEDIA },

  { KEY_FIRST_MACRO + 0, 0, "macro 0", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 1, 0, "macro 1", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 2, 0, "macro 2", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 3, 0, "macro 3", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 4, 0, "macro 4", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 5, 0, "macro 5", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 6, 0, "macro 6", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 7, 0, "macro 7", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 8, 0, "macro 8", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 9, 0, "macro 9", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 10, 0, "macro 10", macroIcon, KEY_CATEGORY_MACRO },
  { KEY_FIRST_MACRO + 11, 0, "macro 11", macroIcon, KEY_CATEGORY_MACRO },

  { KEY_A, 'a', "a", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_B, 'b', "b", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_C, 'c', "c", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_D, 'd', "d", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_E, 'e', "e", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_F, 'f', "f", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_G, 'g', "g", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_H, 'h', "h", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_I, 'i', "i", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_J, 'j', "j", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_K, 'k', "k", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_L, 'l', "l", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_M, 'm', "m", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_N, 'n', "n", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_O, 'o', "o", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_P, 'p', "p", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_Q, 'q', "q", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_R, 'r', "r", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_S, 's', "s", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_T, 't', "t", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_U, 'u', "u", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_V, 'v', "v", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_W, 'w', "w", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_X, 'x', "x", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_Y, 'y', "y", nullptr, KEY_CATEGORY_ALPHA },
  { KEY_Z, 'z', "z", nullptr, KEY_CATEGORY_ALPHA },

  { KEY_1, '1', "1", nullptr, KEY_CATEGORY_NUM },
  { KEY_2, '2', "2", nullptr, KEY_CATEGORY_NUM },
  { KEY_3, '3', "3", nullptr, KEY_CATEGORY_NUM },
  { KEY_4, '4', "4", nullptr, KEY_CATEGORY_NUM },
  { KEY_5, '5', "5", nullptr, KEY_CATEGORY_NUM },
  { KEY_6, '6', "6", nullptr, KEY_CATEGORY_NUM },
  { KEY_7, '7', "7", nullptr, KEY_CATEGORY_NUM },
  { KEY_8, '8', "8", nullptr, KEY_CATEGORY_NUM },
  { KEY_9, '9', "9", nullptr, KEY_CATEGORY_NUM },
  { KEY_0, '0', "0", nullptr, KEY_CATEGORY_NUM },

  { KEY_ENTER, '\r', "return", returnIcon, KEY_CATEGORY_TEXT },
  { KEY_ESC, 0x1b, "esc", escIcon, KEY_CATEGORY_TEXT },
  { KEY_BACKSPACE, 0x08, "bs", backspaceIcon, KEY_CATEGORY_TEXT },
  { KEY_DELETE, 0, "del", deleteIcon, KEY_CATEGORY_TEXT },
  { KEY_TAB, '\t', "tab", tabIcon, KEY_CATEGORY_TEXT },
  { KEY_SPACE, ' ', " ", spaceIcon, KEY_CATEGORY_TEXT },
  { KEY_CAPS_LOCK, 0, "caps", capsLockIcon, KEY_CATEGORY_TEXT },
  { KEY_NUM_LOCK, 0, "numlk", numLockIcon, KEY_CATEGORY_TEXT },
  { KEY_NON_US_BS, 0x08, "backspace", backspaceIcon, KEY_CATEGORY_TEXT },

  { KEY_MINUS, '-', "-", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_EQUAL, '=', "=", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_LEFT_BRACE, '[', "[", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_RIGHT_BRACE, ']', "]", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_BACKSLASH, '\\', "\\", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_NON_US_NUM, 0, "num", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_SEMICOLON, ';', ";", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_QUOTE, '\'', "'", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_TILDE, '`', "'", nullptr, KEY_CATEGORY_PUNCTUATION },  // tilde key is actually ` in EN_US
  { KEY_COMMA, ',', ",", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_PERIOD, '.', ".", nullptr, KEY_CATEGORY_PUNCTUATION },
  { KEY_SLASH, '/', "/", nullptr, KEY_CATEGORY_PUNCTUATION },

  { KEY_F1, 0, "f1", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F2, 0, "f2", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F3, 0, "f3", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F4, 0, "f4", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F5, 0, "f5", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F6, 0, "f6", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F7, 0, "f7", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F8, 0, "f8", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F9, 0, "f9", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F10, 0, "f10", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F11, 0, "f11", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F12, 0, "f12", nullptr, KEY_CATEGORY_FUNCTION },

  { KEY_PRINTSCREEN, 0, "pts", nullptr, KEY_CATEGORY_SYSTEM },
  { KEY_SCROLL_LOCK, 0, "scl", nullptr, KEY_CATEGORY_SYSTEM },
  { KEY_PAUSE, 0, "p/b", nullptr, KEY_CATEGORY_SYSTEM },
  { KEY_INSERT, 0, "ins", nullptr, KEY_CATEGORY_SYSTEM },

  { KEY_HOME, 0, "home", homeIcon, KEY_CATEGORY_CURSOR },
  { KEY_PAGE_UP, 0, "pgup", pageUpIcon, KEY_CATEGORY_CURSOR },
  { KEY_END, 0, "end", endIcon, KEY_CATEGORY_CURSOR },
  { KEY_PAGE_DOWN, 0, "pgdn", pageDownIcon, KEY_CATEGORY_CURSOR },
  { KEY_RIGHT, 0, "right", rightArrowIcon, KEY_CATEGORY_CURSOR },
  { KEY_LEFT, 0, "left", leftArrowIcon, KEY_CATEGORY_CURSOR },
  { KEY_DOWN, 0, "down", downArrowIcon, KEY_CATEGORY_CURSOR },
  { KEY_UP, 0, "up", upArrowIcon, KEY_CATEGORY_CURSOR },

  { KEYPAD_SLASH, '/', "/", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_ASTERIX, '*', "*", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_MINUS, '-', "-", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_PLUS, '+', "+", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_ENTER, '\n', "enter", returnIcon, KEY_CATEGORY_KEYPAD },
  { KEYPAD_1, '1', "1", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_2, '2', "2", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_3, '3', "3", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_4, '4', "4", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_5, '5', "5", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_6, '6', "6", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_7, '7', "7", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_8, '8', "8", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_9, '9', "9", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_0, '0', "0", nullptr, KEY_CATEGORY_KEYPAD },
  { KEYPAD_PERIOD, '.', ".", nullptr, KEY_CATEGORY_KEYPAD },

  { KEY_F13, 0, "f13", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F14, 0, "f14", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F15, 0, "f15", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F16, 0, "f16", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F17, 0, "f17", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F18, 0, "f18", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F19, 0, "f19", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F20, 0, "f20", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F21, 0, "f21", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F22, 0, "f22", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F23, 0, "f23", nullptr, KEY_CATEGORY_FUNCTION },
  { KEY_F24, 0, "f24", nullptr, KEY_CATEGORY_FUNCTION },
  // end of table marker
  { NO_CODE, 0, nullptr, nullptr, KEY_CATEGORY_NONE }
};

const keycode_t TOTALCODES = sizeof(keyInfo)/sizeof(keyInfo[0]) - 1;  // how many unique codes (not including the end of table marker


int getKeyInfoIndex(keycode_t c);
const keyinfo_t* getKeyInfo(keycode_t c);
const icon_t getKeyIcon(keycode_t c);
keycategory_t getKeyCategory(keycode_t c);
const char* getKeyLabel(keycode_t c);

#endif // _KeyInfo_
