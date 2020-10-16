#include "../../lib/Event/EventController.h"

EventController::EventController()
{
	listener.register_event(on_key_pressed);
}