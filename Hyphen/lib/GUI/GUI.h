#pragma once

#define GUI_H_

#include "../CompiledHeaders.h"
#include "../Layer/Layer.h"

namespace Hyphen
{
	class GUI : public Layer
	{
	public:
		void attach() override;
		void detach() override;
		void update() override;
		void event(Event & e) override;
	private:
	};
}