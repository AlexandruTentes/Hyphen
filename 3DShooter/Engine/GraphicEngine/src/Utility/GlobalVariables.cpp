#include "../../lib/Utility/GlobalVariables.h"

GLint global::width = 1000, global::height = 600;
bool global::unfocused = false;												// Check if the window is focused
bool global::center_cursor_status = true;									// Store a flag to know if to set the cursor to center
GLint global::prev_width = -1, global::prev_height = -1;
int global::min_width = 900, global::min_height = 600;