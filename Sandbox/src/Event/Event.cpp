#include "../../lib/Event/Event.h"

void on_key_pressed(Hyphen::KeyDown & e)
{
	std::cout << "Key pressed: " << e.get_key() << std::endl;
}

void on_window_create(Hyphen::WindowCreate & e)
{
	std::cout << "Window width: " << e.get_width() << ", Window height: " << e.get_height() << std::endl;
}

void on_mouse_move(Hyphen::MouseMove & e)
{
	std::cout << "Mouse coords: x: " << e.get_x() << ", y:" << e.get_y() << std::endl;
}