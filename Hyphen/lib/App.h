#pragma once

#define APP_H_

#include "Platform.h"
#include "Window/Window.h"
#include "Layer/LayerStack.h"

namespace Hyphen
{
	class API App
	{
	public:
		void run();

		void push_layer(Layer * layer);
		void push_overlay(Layer* overlay);
		void pop_layer(Layer * layer);
		void pop_overlay(Layer* overlay);

		virtual ~App() = default;
	private:
		LayerStack & layer_stack = LayerStack::get_instance();
	};

	App * create();
}