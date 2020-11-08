#pragma once

#define OVERLAY_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"
#include "../Event/Listener.h"

namespace Hyphen
{
	class Overlay : public Listener
	{
	public:
		Overlay() {};
		virtual void attach() {};
		virtual void detach() {};
		virtual void update() {};
		virtual void event(Event & event) {};

		void set_id(unsigned short int id) { this->id = id; };
		unsigned int get_id() { return id; };
		bool get_status() { return handled; }

		virtual ~Overlay() = default;
	private:
		unsigned int id = 0;
	protected:
		bool handled = false;
	};
}