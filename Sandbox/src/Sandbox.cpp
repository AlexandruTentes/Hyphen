#include "Hyphen.h"
#include "../lib/Event/EventController.h"

class Sandbox : public Hyphen::App
{
public:
	Sandbox() {};
private:
	EventController event_controller;
};

Hyphen::App * Hyphen::create()
{
	return new Sandbox;
}