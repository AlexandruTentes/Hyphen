#pragma once

#define LAYERSTACK_H_

#include "../CompiledHeaders.h"
#include "../Platform.h"
#include "../Math/DynamicDatastructure.h"
#include "Layer.h"
#include "Overlay.h"

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
		void push_overlay(Overlay * overlay);
		void pop_layer(Layer * layer);
		void pop_overlay(Overlay * overlay);
		void pop_all_layers();
		void pop_all_overlays();

		Stack<Layer *> & get_layers();
		Stack<Overlay *> & get_overlays();

		virtual ~LayerStack();
	private:
		Stack<Layer *> layer;
		Stack<Overlay *> overlay;
	};
}