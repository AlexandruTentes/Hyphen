#include "../../lib/Platform/Windows.h"

//===== Check if the OS is Windows =====//
#ifdef WINDOWS_H_

//===== Declaring WindowAPI namespace members =====//
namespace WindowAPI
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
		//===== Redraws the content of the window =====//
		UpdateWindow(handler);
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

		//===== Prevent cpu throttle =====//
		Sleep(0);
	}

	void Windows::on_event(Event & e)
	{
		std::cout << & KeyDown::get_instance() << std::endl;
		dispacher.dispatch<KeyDown>(e, KeyDown::get_instance().callback);
	}

	bool Windows::init()
	{
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
		pixel_format.cColorBits = specs.color_bits;
		pixel_format.cDepthBits = specs.depth_bits;

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
			device_screen_settings.dmBitsPerPel = specs.color_bits;
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
			RECT window_size;
			window_size.left = (long) 0;
			window_size.right = (long)specs.width;
			window_size.top = (long) 0;
			window_size.bottom = (long) specs.height;

			//===== Only expand the widnwo for border filling in windowed mode =====//
			AdjustWindowRectEx(& window_size, window_style, FALSE, window_ex_style);
		}

		//===== Don't paint over subwindows =====//
		window_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | window_style;

		//===== Store the current class instance to be called by WM_CREATE procedure at create time =====//
		window_manager_instance.window_initialization(this);

		//===== Create the window and get the handler, catch any errors =====//
		if (!(handler = CreateWindowEx(window_ex_style, class_name.c_str(), specs.title.c_str(),
			window_style, 0, 0, specs.width, specs.height,
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
}

/////////////////////////////////////////////////////////////////////////////
//===== The window procedure callback function of each window created =====//
/////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	using namespace WindowAPI;

	switch (msg)
	{
	case WM_CREATE: //Event fired when the window has been created
	{
		//window_manager_instance.get_one_window(hwnd)->on_event();

		window_manager_instance.get_one_window(hwnd)->create();

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
		KeyDown key_down(wparam);

		window_manager_instance.get_one_window(hwnd)->on_event(key_down);

		return 0;
	}
	case WM_KEYUP:
	{
		KeyUp(11);

		//window_manager_instance.get_one_window(hwnd)->on_event();

		return 0;
	}
	case WM_SIZE:
	{
		//window_manager_instance.get_one_window(hwnd)->on_event();

		window_manager_instance.get_one_window(hwnd)->resize();

		return 0;
	}
	case WM_DESTROY: //Event fired when the window has been destroyed
	{
		//window_manager_instance.get_one_window(hwnd)->on_event();

		window_manager_instance.get_one_window(hwnd)->destroy();

		PostQuitMessage(0); // Tells the window api that this window has requested to terminate

		return 0;
	}
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

#endif // WINDOWS