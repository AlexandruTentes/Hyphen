#include <Hyphen.h>

class Sandbox : public Hyphen::App
{

};

Hyphen::App * Hyphen::create()
{
	return new Sandbox;
}