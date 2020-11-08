#include "../../lib/Layer/LayerStack.h"

namespace Hyphen
{
	void LayerStack::push_layer(Layer * layer)
	{
		layer->set_id(this->layer.get_size() + 1);
		this->layer.push(layer);
		layer->attach();
	}

	void LayerStack::push_overlay(Overlay * overlay)
	{
		overlay->set_id(this->overlay.get_size() + 1);
		this->overlay.push(overlay);
		overlay->attach();
	}

	void LayerStack::pop_layer(Layer * layer)
	{
		if (layer == nullptr)
			return;

		unsigned int index = layer->get_id();

		if (index == 0)
			return;

		this->layer.pop(index - 1);
		layer->detach();
	}

	void LayerStack::pop_overlay(Overlay * overlay)
	{
		if (overlay == nullptr)
			return;

		unsigned int index = overlay->get_id();

		if (index == 0)
			return;

		this->overlay.pop(index - 1);
		overlay->detach();
	}

	void LayerStack::pop_all_layers()
	{
		if (layer.get_size() < 1)
			return;

		for (unsigned int i = layer.get_size(); i >= 1; i--)
			layer.pop(i - 1);
	}

	void LayerStack::pop_all_overlays()
	{
		if (overlay.get_size() < 1)
			return;

		for (unsigned int i = overlay.get_size(); i >= 1; i--)
			overlay.pop(i - 1);
	}

	Stack<Layer *> & LayerStack::get_layers()
	{
		return layer;
	}

	Stack<Overlay *> & LayerStack::get_overlays()
	{
		return overlay;
	}

	LayerStack::~LayerStack()
	{
		pop_all_layers();
		pop_all_overlays();
	}
}