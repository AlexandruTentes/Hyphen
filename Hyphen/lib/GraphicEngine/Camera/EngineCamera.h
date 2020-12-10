#pragma once

#define ENGINE_CAMERA_H_

#include "../../CompiledHeaders.h"
#include "../../Layer/Overlay.h"
#include "../../Math/Math.h"
#include "Camera.h"

namespace Hyphen
{
	class EngineCamera : public Overlay
	{
	public:
		EngineCamera(Matrix4d<float> & view);
		void attach() override;
		void detach() override;
		void update() override;
		void event(Event& e) override;

		void on_mouse_move(MouseMove& e);

		virtual ~EngineCamera() = default;
	public:
		Matrix4d<float> view;
	private:
		Camera camera;
	};
}