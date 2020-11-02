#pragma once

#include "HyphenLayer.h"
#include "HyphenEvents.h"

class LayerExample : public Hyphen::Layer
{
public:
	void event(Hyphen::Event & event) override
	{
		DISPATCH(LayerExample::mouse_move_event, event);
	}

	void mouse_move_event(Hyphen::MouseMove & e)
	{
		std::cout << "example layer: x: " << e.get_x() << ", y:" << e.get_y() << std::endl;
	}
};

class AnotherLayerExample : public Hyphen::Layer
{
public:
	void event(Hyphen::Event & event) override
	{
		DISPATCH(AnotherLayerExample::mouse_move_event, event);
		//DISPATCH(AnotherLayerExample::key_down_event, event);
	}

	void key_down_event(Hyphen::KeyDown & e)
	{
		std::cout << "another example layer: key: " << e.get_key() << std::endl;
	}

	void mouse_move_event(Hyphen::MouseMove & e)
	{
		std::cout << "another example layer: x: " << e.get_x() << ", y:" << e.get_y() << std::endl;
	}
};