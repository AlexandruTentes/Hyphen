#pragma once

#define KEYCODES_H_

#include "../CompiledHeaders.h"
#include "../Math/UtilityMacros.h"

namespace Hyphen
{
	class KeyCodes
	{
	public:
		SINGLETONIZE(KeyCodes)

		virtual ~KeyCodes() = default;
	public:
		static const unsigned short int key_map_size = 128;
		bool key_map[key_map_size];
	};

	//===== Keyboard key codes =====//
	enum HYKeyboardCodes
	{
		HY_BACKSPACE = 8,
		HY_ENTER = 10,
		HY_ESC = 27,			
		HY_SPACE = 32,				
		HY_EXCLAMATION,				// !
		HY_QUOTATION,				// "
		HY_HASHTAG,					// #
		HY_DOLLAR,					// $
		HY_PERCENTAGE,				// %
		HY_AMPERSAND,				// &
		HY_APOSTROPHE,				// '
		HY_OPEN_BRACKETS,			// (
		HY_CLOSE_BRACKETS,			// )
		HY_STAR,					// *
		HY_PLUS,					// +
		HY_MINUS = 45,				// -
		HY_DOT,						// .
		HY_FORWARD_SLASH,			// /
		HY_0,						// 0
		HY_1,						// 1
		HY_2,						// 2
		HY_3,						// 3
		HY_4,						// 4
		HY_5,						// 5
		HY_6,						// 6
		HY_7,						// 7
		HY_8,						// 8
		HY_9,						// 9
		HY_COLON,					// :
		HY_SEMICOLON,				// ;
		HY_LESSTHAN,				// <
		HY_EQUAL,					// =
		HY_GREATERTHAN,				// >
		HY_QUESTION,				// ?
		HY_AT,						// @
		HY_OPEN_SQUAREBRACK = 91,	// [
		HY_BACKWARD_SLASH,			/* \ */
		HY_CLOSE_SQUAREBRACK,		// ]
		HY_CARET,					// ^
		HY_UNDERSCORE,				// _
		HY_GRAVE,					// `
		HY_A,						// A
		HY_B,						// B
		HY_C,						// C
		HY_D,						// D
		HY_E,						// E
		HY_F,						// F
		HY_G,						// G
		HY_H,						// H
		HY_I,						// I
		HY_J,						// J
		HY_K,						// K
		HY_L,						// L
		HY_M,						// M
		HY_N,						// N
		HY_O,						// O
		HY_P,						// P
		HY_Q,						// Q
		HY_R,						// R
		HY_S,						// S
		HY_T,						// T
		HY_U,						// U
		HY_V,						// V
		HY_W,						// W
		HY_X,						// X
		HY_Y,						// Y
		HY_Z,						// Z
		HY_OPEN_CURLYBRACK,			// {
		HY_VERTICAL_SLASH,			// |
		HY_CLOSE_CURLYBRACK,		// }
		HY_TILDE,					// ~
		HY_DELETE
	};
}