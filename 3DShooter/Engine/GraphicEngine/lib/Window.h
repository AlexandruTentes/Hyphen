#pragma once

#define WINDOW_H_

#include "Utility/IncludeAll.h"

namespace window
{
	class Window
	{
		private:
			//========================//
			//	Window specific data  //
			//========================//


			HWND handler;														// The window handler
			RECT window_rect;													// The window location on the screen (in coords x and y)

			bool static window_resize_status;									// A flag which tells if the window undergoes resizing
			char * window_name;													// The window name (needed to get window handler)
			bool clipping_status = false;										// The clipping status of the mouse (can we clip it
																				// inside the window boundaries
		public:

			// Function which checks for this window's procedure message
			void check_window_procedure_message();

			// Function which checks if the window has been refocused and clips cursor if so
			void check_refocus();

			// Get the window handler, rect and then clip the cursor inside window boundaries
			void set_window_cursor_boundary(char * window_name);

			// Sets the window size
			void set_window_size(int width, int height);

		//Private functions
		private:

			// Clips the cursor inside window boundaries
			void clip();
	};
}