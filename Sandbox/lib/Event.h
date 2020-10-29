#pragma once

#include "HyphenListener.h"

class UserDefinedEvents : public Hyphen::Listener
{
public:
	UserDefinedEvents()
	{

	}

	void on_mouse_move(Hyphen::MouseMove & e)
	{
		std::cout << "Client defined custom event listener" << std::endl;
	}
};