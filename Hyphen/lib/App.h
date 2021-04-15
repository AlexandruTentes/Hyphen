#pragma once

#define APP_H_

#include "Platform.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"
#include "Math/UtilityFunctions.h"
#include "GraphicEngine/ModelParser/Parser.h"
#include "../lib/GraphicEngine/Shader.h"
#include "../lib/GraphicEngine/Buffer/VertexBufferLayout.h"
#include "../lib/Storage/Filesystem.h"

namespace Hyphen
{
	class API App
	{
	public:
		void run();

		virtual ~App() = default;
	protected:
		LayerStack & layer_stack = LayerStack::get_instance();
		Filesystem& folder = Filesystem::get_instance();
	};

	App * create();
}