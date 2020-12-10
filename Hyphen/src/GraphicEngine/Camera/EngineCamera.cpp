#include "../../../lib/GraphicEngine/Camera/EngineCamera.h"

namespace Hyphen
{
	EngineCamera::EngineCamera(Matrix4d<float>& view)
	{
		view.set(	0, 0, -3, 0,
					0, 0, 1, 0,
					0, 1, 0, 0,
					0, 0, 0, 0);

		camera.set_camera_data(view);
	}

	void EngineCamera::attach()
	{
		
	}

	void EngineCamera::detach()
	{

	}

	void EngineCamera::update()
	{
		camera.calculate_lookpoint();
		camera.set_lookat_point(view);
	}

	void EngineCamera::event(Event& e)
	{
		DISPATCH(EngineCamera::on_mouse_move, e);
	}

	void EngineCamera::on_mouse_move(MouseMove& e)
	{
		std::cout << "KEK" << "\n";
		camera.camera_motion(e.get_x(), e.get_y());
	}
}