#include "../lib/Window.h"

bool window::Window::window_resize_status = false;

void window::Window::check_window_procedure_message()
{/*
 auto check_resize = []()
 {
 try
 {
 bool window_msg_status = false;
 MSG msg;

 // Check for a user's msg to the window
 while ((window_msg_status = GetMessage(&msg, 0, 0, 0)))
 if (window_msg_status != -1)
 // Calling window resize handler
 if (msg.message == WM_SIZE)
 {
 ClipCursor(NULL);
 std::cout << "CALLED" << std::endl;
 window_resize_status = true;
 };

 std::chrono::milliseconds duration(1000);
 std::this_thread::sleep_for(duration);
 }
 catch (const std::exception& e)
 {
 std::cout << e.what() << std::endl;
 }
 };

 std::thread check_resize_thread(check_resize);*/
}

void window::Window::check_refocus()
{
	// Get the currently focused screen
	HWND foreground_window_handler = GetForegroundWindow();

	// If the user changed the focus, remember this and unclip
	if (handler != foreground_window_handler)
	{
		global::unfocused = true;
		ClipCursor(NULL);
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}

	// If the user changed the focus back to the window remember this and clip
	if (handler == foreground_window_handler && global::unfocused == true)
	{
		glutSetCursor(GLUT_CURSOR_NONE);
		global::unfocused = false;

		// We recalculate the boundaries in case the user decided 
		// to change the window possition on the screen
		set_window_cursor_boundary(window_name);
	}
}

void window::Window::set_window_size(int width, int height)
{
	if (global::width != width)
		global::prev_width = global::width;

	if (global::height != height)
		global::prev_height = global::height;

	global::width = width;
	global::height = height;
}

void window::Window::clip()
{
	// If it is possible to clip the cursor, then do it
	if (clipping_status)
	{
		// Lower the boundaries of the window size
		window_rect.top += global::width / 10;
		window_rect.bottom -= global::width / 10;
		window_rect.left += global::width / 10;
		window_rect.right -= global::width / 10;

		// If the window undergoes resizing, forget the clipping
		if (!window_resize_status)
			// Clip the cursor to those boundaries
			ClipCursor(&window_rect);
	}
}

void window::Window::set_window_cursor_boundary(char * window_name)
{
	// Set window name
	this->window_name = window_name;

	// Get the handler of the window name
	handler = FindWindowA(NULL, (LPCSTR)window_name);

	// Set the focus to the window
	SetFocus(handler);

	// Get the window boundaries and save the failure status
	clipping_status = GetWindowRect(handler, &window_rect);

	clip();
}