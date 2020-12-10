#include "../../../lib/Window/Platform/Windows.h"

//===== Check if the OS is Windows =====//
#ifdef WINDOWS_H_

//===== Declaring WindowAPI namespace members =====//
namespace Hyphen
{
	//===== Defining the extern create_window function which returns an Windows window =====//
	Window * Window::create_window(const WindowSpecs & specs)
	{
		return new Windows(specs);
	}

	//////////////////////////////////////////////////////////////////
	//===== Declarations of the Windows class member functions =====//
	//////////////////////////////////////////////////////////////////

	Windows::Windows(const WindowSpecs & specs) :
		specs(specs)
	{}

	void Windows::create()
	{}

	void Windows::update()
	{
		window_msg_handler();
	}

	void Windows::destroy()
	{
		layer_stack.pop_all_layers();
		layer_stack.pop_all_overlays();
		is_running = false;
		window_manager_instance.remove(handler);
	}

	Windows::~Windows()
	{
		kill_window();

		is_running = false;

		if (handler)
			return;

		window_manager_instance.remove(handler);
		DestroyWindow(handler);
	}

	void Windows::resize()
	{
		//Branchless if(specs.height == 0) then specs.height = 1, else retain previous height
		//division by 0 protection!
		specs.height = (specs.height != 0) * specs.height + 1 * (specs.height == 0);
		aspect_ratio = (float)specs.width / specs.height;
		glViewport(0, 0, specs.width, specs.height);
		glMatrixMode(GL_PROJECTION_MATRIX);

		glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
		glLoadIdentity();
	}

	void Windows::kill_window()
	{
		if (is_fullscreen)
			ChangeDisplaySettings(NULL, 0);

		if (hdc && //In case there is a device context
			!ReleaseDC(handler, hdc)) //Attempt to free the device context
		{
			MessageBox(handler, "Could not free the device context!", "Window Closure Error", MB_OK);
			hdc = NULL;
		}

		if (hinstance &&
			!UnregisterClass(class_name.c_str(), hinstance)) //Attempt to unregister the window class name
		{
			MessageBox(handler, "Could not unregister class!", "Window Closure Error", MB_OK);
			hinstance = NULL;
		}
	}

	void Windows::window_msg_handler()
	{
		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(& msg);
			DispatchMessage(& msg);
		}

		glLoadIdentity();
		SwapBuffers(hdc);
		//===== Prevent cpu throttle =====//
		Sleep(0);
	}

	bool Windows::init()
	{
		RECT window_size;
		DWORD window_ex_style;
		DWORD window_style;
		DEVMODE device_screen_settings;
		WNDCLASSEX wcex;
		PIXELFORMATDESCRIPTOR pixel_format;
		int pixel_format_index;

		hinstance = GetModuleHandle(NULL); //Get this file handle

		//===== Specifying the window details =====//
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.cbClsExtra = NULL;
		wcex.cbWndExtra = NULL;
		wcex.hbrBackground = NULL;
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hInstance = hinstance;
		wcex.lpszClassName = class_name.c_str();
		wcex.lpszMenuName = NULL;
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;;
		wcex.lpfnWndProc = & WndProc;

		//===== Specifying the window pixel format =====//
		memset(&pixel_format, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pixel_format.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixel_format.nVersion = 1;
		pixel_format.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixel_format.iPixelType = PFD_TYPE_RGBA;
		pixel_format.cColorBits = 32;
		pixel_format.cDepthBits = 24;
		pixel_format.cAlphaBits = 16;
		pixel_format.cAccumAlphaBits = 16;
		pixel_format.iLayerType = PFD_MAIN_PLANE;

		//===== Registering the window details for validation =====//
		if (!RegisterClassEx(& wcex))
		{
			MessageBox(handler, "Could not register class!", "Window Creation Error", MB_OK);
			kill_window();
			return false;
		}

		if (is_fullscreen)
		{
			//===== Specifying the device mode for fullscreen =====//
			memset(& device_screen_settings, 0, sizeof(device_screen_settings));
			device_screen_settings.dmSize = sizeof(device_screen_settings);
			device_screen_settings.dmPelsWidth = specs.width;
			device_screen_settings.dmPelsHeight = specs.height;
			device_screen_settings.dmBitsPerPel = pixel_format.cColorBits;
			device_screen_settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			//===== Attempt to set the mode, where CDS_FULLSCREEN gets rid of the task bar =====//
			if (ChangeDisplaySettings(&device_screen_settings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			{
				MessageBox(handler, "Could not set full screen!", "Window Creation Error", MB_OK);
				is_fullscreen = false;
			}
		}

		if (is_fullscreen)
		{
			window_ex_style = WS_EX_APPWINDOW;
			window_style = WS_POPUP; //Gets rid of unnecessary boarders
		}
		else
		{
			window_ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			window_style = WS_OVERLAPPEDWINDOW;

			//===== Make sure the borders of the window don't overlap over the window dimensions =====//
			window_size.left = (long) 0;
			window_size.right = (long)specs.width;
			window_size.top = (long) 0;
			window_size.bottom = (long) specs.height;
		}

		//===== Don't paint over subwindows =====//
		window_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | window_style;

		//===== Store the current class instance to be called by WM_CREATE procedure at create time =====//
		window_manager_instance.window_initialization(this);

		//===== Force winapi to use the exact given dimensions(needed for windowed mode) =====//
		AdjustWindowRectEx(&window_size, window_style, FALSE, window_ex_style);

		//===== Create the window and get the handler, catch any errors =====//
		if (!(handler = CreateWindowEx(window_ex_style, class_name.c_str(), specs.title.c_str(),
			window_style, 0, 0, 
			window_size.right - window_size.left,
			window_size.bottom - window_size.top,
			NULL, NULL, hinstance, NULL)))
		{
			MessageBox(handler, "Could not create window!", "Window Creation Error", MB_OK);
			kill_window();
			return false;
		}

		//===== Getting the GDI device context for opengl =====//
		if (!(hdc = GetDC(handler)))
		{
			MessageBox(handler, "Could not get device context!", "Window Creation Error", MB_OK);
			kill_window();
			return false;
		}

		//===== Check if windows has this pixel format =====//
		if (!(pixel_format_index = ChoosePixelFormat(hdc, & pixel_format)))
		{
			MessageBox(handler, "Could not find the pixel format!", "Window Creation Error", MB_OK);
			kill_window();
			return false;
		}

		//===== Attempt to set the pixel format =====//
		if (!SetPixelFormat(hdc, pixel_format_index, & pixel_format))
		{
			MessageBox(handler, "Could not set the pixel format!", "Window Creation Error", MB_OK);
			kill_window();
			return false;
		}

		resize();

		//===== Store this instance at given handler location for later use =====//
		window_manager_instance.insert(handler, this);

		return true;
	}

	void Windows::show()
	{
		if (!handler)
			return;

		//===== Display the window =====//
		ShowWindow(handler, SW_SHOW);

		//===== Redraws the content of the window =====//
		UpdateWindow(handler);

		is_running = true;
	}

	std::tuple<float, float> Windows::get_float_xy(int x, int y)
	{
		//Get OS dpi scaling and normalize it to windows (96 pixels per unit)
		float dip_x = GetDeviceCaps(hdc, LOGPIXELSX) / 96.0f;
		float dip_y = GetDeviceCaps(hdc, LOGPIXELSY) / 96.0f;

		return std::make_tuple(((float)x) / dip_x, ((float)x) / dip_y);
	}
}

/////////////////////////////////////////////////////////////////////////////
//===== The window procedure callback function of each window created =====//
/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	using namespace Hyphen;

#define POLL(T, e)	EventPoll::get_instance().event_poll[e.type] = true; \
					delete EventPoll::get_instance().event_array[T::type]; \
					T * cpy = new T(); \
					* cpy = e; \
					EventPoll::get_instance().event_array[e.type] = cpy;

	switch (msg)
	{
	case WM_CREATE: //Event fired when the window has been created
	{
		LPCREATESTRUCTA lpcrstr = (LPCREATESTRUCTA) lparam;
		WindowCreate create(lpcrstr->cx, lpcrstr->cy);
		window_manager_instance.get_one_window(hwnd)->on_event<WindowCreate>(create);
		window_manager_instance.get_one_window(hwnd)->create();
		POLL(WindowCreate, create)
		return 0;
	}
	case WM_ACTIVATE:
	{
		if (!HIWORD(wparam)) //Check if window is minimized
		{
			//window_manager_instance.get_one_window(hwnd)->on_event();
			window_manager_instance.get_one_window(hwnd)->is_minimized = false;
			window_manager_instance.get_one_window(hwnd)->is_focused = true;
		}
		else
		{
			//window_manager_instance.get_one_window(hwnd)->on_event();
			window_manager_instance.get_one_window(hwnd)->is_minimized = true;
			window_manager_instance.get_one_window(hwnd)->is_focused = false;
		}

		return 0; //Returns to the message loop
	}
	case WM_KEYDOWN:
	{
		KeyDown key_down(LOWORD(wparam));
		window_manager_instance.get_one_window(hwnd)->on_event<KeyDown>(key_down);
		POLL(KeyDown, key_down)
		return 0;
	}
	case WM_KEYUP:
	{
		KeyUp key_up(LOWORD(wparam));
		window_manager_instance.get_one_window(hwnd)->on_event<KeyUp>(key_up);
		POLL(KeyUp, key_up)
		return 0;
	}
	case WM_SIZE:
	{
		WindowResize resize(LOWORD(lparam), HIWORD(lparam));
		window_manager_instance.get_one_window(hwnd)->on_event<WindowResize>(resize);
		window_manager_instance.get_one_window(hwnd)->resize();
		POLL(WindowResize, resize)
		return 0;
	}
	case WM_DESTROY: //Event fired when the window has been destroyed
	{
		WindowClose close;
		window_manager_instance.get_one_window(hwnd)->on_event<WindowClose>(close);
		window_manager_instance.get_one_window(hwnd)->destroy();
		POLL(WindowClose, close)
		PostQuitMessage(0); // Tells the window api that this window has requested to terminate
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		std::tuple<float, float> xy_tuple = ((Windows *)window_manager_instance.get_one_window(hwnd))->get_float_xy(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		MouseMove mouse(std::get<0>(xy_tuple), std::get<1>(xy_tuple));
		window_manager_instance.get_one_window(hwnd)->on_event<MouseMove>(mouse);
		POLL(MouseMove, mouse)
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		MouseButtonDown button((float)LOWORD(lparam), (float)HIWORD(lparam), LEFT_BTN);
		window_manager_instance.get_one_window(hwnd)->on_event<MouseButtonDown>(button);
		POLL(MouseButtonDown, button)
		return 0;
	}
	case WM_LBUTTONUP:
	{
		MouseButtonUp button((float)LOWORD(lparam), (float)HIWORD(lparam), LEFT_BTN);
		window_manager_instance.get_one_window(hwnd)->on_event<MouseButtonUp>(button);
		POLL(MouseButtonUp, button)
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		MouseButtonDown button((float)LOWORD(lparam), (float)HIWORD(lparam), RIGHT_BTN);
		window_manager_instance.get_one_window(hwnd)->on_event<MouseButtonDown>(button);
		POLL(MouseButtonDown, button)
		return 0;
	}
	case WM_RBUTTONUP:
	{
		MouseButtonUp button((float)LOWORD(lparam), (float)HIWORD(lparam), RIGHT_BTN);
		window_manager_instance.get_one_window(hwnd)->on_event<MouseButtonUp>(button);
		POLL(MouseButtonUp, button)
		return 0;
	}
	case WM_MOUSEWHEEL:
	{
		MouseScroll scroll(0, HIWORD(wparam) == 120 ? (float) 0.5 : (float) -0.5);
		window_manager_instance.get_one_window(hwnd)->on_event<MouseScroll>(scroll);
		POLL(MouseScroll, scroll)
		return 0;
	}
	case WM_CHAR:
	{
		KeyTyped key(LOWORD(wparam));
		window_manager_instance.get_one_window(hwnd)->on_event<KeyTyped>(key);
		POLL(KeyTyped, key)
		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

#endif // WINDOWS