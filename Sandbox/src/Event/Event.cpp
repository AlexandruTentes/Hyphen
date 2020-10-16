#include "../../lib/Event/Event.h"

void on_key_pressed(WindowAPI::KeyDown & e)
{
	std::cout << "Key pressed: " << e.get_key() << std::endl;
}