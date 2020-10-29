#include "Hyphen.h"
#include "../lib/Layers.h"
#include "../lib/Event.h"

class Sandbox : public Hyphen::App
{
public:
	Sandbox() 
	{
		push_layer(layer1);
		push_layer(layer2);
	};

	virtual ~Sandbox()
	{
		delete layer1;
		delete layer2;
	};
private:
	LayerExample * layer1 = new LayerExample();
	AnotherLayerExample * layer2 = new AnotherLayerExample();
};

Hyphen::App * Hyphen::create()
{
	return new Sandbox;
}