#include "../lib/GlobalVariables.h"

namespace Hyphen
{
	unsigned int width = 700, height = 700;
	bool unfocused = false;												// Check if the window is focused
	bool center_cursor_status = true;									// Store a flag to know if to set the cursor to center
	unsigned int prev_width = -1, prev_height = -1;
	int min_width = 900, min_height = 600;
	float aspect_ratio = 1.0f;											// Store current aspect ratio
}