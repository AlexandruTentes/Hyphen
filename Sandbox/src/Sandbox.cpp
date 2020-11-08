#include "Hyphen.h"
#include "../lib/Layers.h"
#include "../lib/Event.h"

class Sandbox : public Hyphen::App
{
public:
	Sandbox() 
	{
		layer_stack.push_layer(& layer2);
	};

	virtual ~Sandbox()
	{
		layer_stack.pop_all_layers();
	};
private:
	AnotherLayerExample layer2;
	UserDefinedEvents e;
};

Hyphen::App * Hyphen::create()
{
	return new Sandbox;
}