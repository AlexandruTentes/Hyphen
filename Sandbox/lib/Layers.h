#pragma once

#include "HyphenLayer.h"
#include "HyphenEvents.h"

class AnotherLayerExample : public Hyphen::Layer
{
public:
	void event(Hyphen::Event & event) override
	{
		DISPATCH(AnotherLayerExample::mouse_move_event, event);
		DISPATCH(AnotherLayerExample::key_down_event, event);
		DISPATCH(AnotherLayerExample::mouse_btndown_event, event);
	}

	void key_down_event(Hyphen::KeyDown & e)
	{
		std::cout << "another example layer: key: " << e.get_key() << std::endl;
		/*
		while (true)
		{
			std::cout << "always loop" << std::endl;
		}*/
	}

	void mouse_move_event(Hyphen::MouseMove & e)
	{
		std::cout << "another example layer: x: " << e.get_x() << ", y:" << e.get_y() << std::endl;
	}

	void mouse_btndown_event(Hyphen::MouseButtonDown & e)
	{
		std::cout << "another example layer: x: " << e.get_x() << ", y:" << e.get_y() << ", btn: " << e.get_button() << std::endl;
	}
};