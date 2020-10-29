#include "../../lib/Layer/LayerStack.h"

namespace Hyphen
{
	void LayerStack::push_layer(Layer * layer)
	{
		layer->set_id(this->layer.get_size() + 1);
		this->layer.push(layer);
		layer->attach();
	}

	void LayerStack::push_overlay(Layer * overlay)
	{
		overlay->set_id(this->overlay.get_size() + 1);
		this->overlay.push(overlay);
		overlay->attach();
	}

	void LayerStack::pop_layer(Layer * layer)
	{
		unsigned int index = layer->get_id();

		if (index == 0)
			return;

		this->layer.pop(index - 1);
		layer->detach();
	}

	void LayerStack::pop_overlay(Layer * overlay)
	{
		unsigned int index = overlay->get_id();

		if (index == 0)
			return;

		this->overlay.pop(index - 1);
		overlay->detach();
	}

	Stack<Layer *> & LayerStack::get_layers()
	{
		return layer;
	}

	Stack<Layer *> & LayerStack::get_overlays()
	{
		return overlay;
	}

	LayerStack::~LayerStack()
	{
		for (unsigned int i = 0; i < layer.get_size(); i++)
			delete layer.get_one(i);

		for (unsigned int i = 0; i < overlay.get_size(); i++)
			delete overlay.get_one(i);
	}
}