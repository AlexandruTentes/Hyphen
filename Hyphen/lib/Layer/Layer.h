#pragma once

#define LAYER_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"
#include "../Event/Listener.h"

namespace Hyphen
{
	class API Layer : public Listener
	{
	public:
		Layer() {};

		virtual void attach() {};
		virtual void detach() {};
		virtual void event(Event & event) {};

		void set_id(unsigned short int id) { this->id = id; };
		unsigned int get_id() { return id; };

		virtual ~Layer() = default;
	public:
		unsigned int id = 0;
	};
}