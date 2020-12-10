#pragma once

#define APP_H_

#include "Platform.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"
#include "Math/UtilityFunctions.h"
#include "GraphicEngine/Camera/EngineCamera.h"
#include "GraphicEngine/ModelParser/Parser.h"

namespace Hyphen
{
	class API App
	{
	public:
		void run();

		virtual ~App() = default;
	protected:
		LayerStack & layer_stack = LayerStack::get_instance();
	};

	App * create();
}