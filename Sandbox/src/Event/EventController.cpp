#include "../../lib/Event/EventController.h"

EventController::EventController()
{
	register_event(on_key_pressed);
	register_event(on_window_create);
	register_event(on_mouse_move);
}