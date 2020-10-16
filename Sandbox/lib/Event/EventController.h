#pragma once

#include "../CompiledHeaders.h"
#include "Listener.h"
#include "Event.h"

class EventController
{
public:
	EventController();	
private:
	Hyphen::Listener & listener = Hyphen::Listener::get_instance();
};