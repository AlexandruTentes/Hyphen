#pragma once

#define LAYERSTACK_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"
#include "../Math/DynamicDatastructure.h"
#include "Layer.h"

namespace Hyphen
{
	class API LayerStack
	{
	public:
		static LayerStack & get_instance() { static LayerStack instance; return instance; };

		LayerStack(unsigned int layer_c = 0, unsigned int overlay_c = 0) :
			layer(layer_c), overlay(overlay_c) {};

		LayerStack(const LayerStack &) = delete;
		LayerStack(LayerStack &&) = delete;

		void push_layer(Layer * layer);
		void push_overlay(Layer * overlay);
		void pop_layer(Layer * layer);
		void pop_overlay(Layer * overlay);
		void pop_all_layers();
		void pop_all_overlays();

		Stack<Layer *> & get_layers();
		Stack<Layer *> & get_overlays();

		virtual ~LayerStack();
	private:
		Stack<Layer *> layer;
		Stack<Layer *> overlay;
	};
}