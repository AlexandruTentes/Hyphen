#include "../../lib/GUI/GUI.h"

namespace Hyphen
{
	void GUI::attach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
#ifdef WINDOWS
		ImGui_ImplWin32_Init(handler);
#elif defined(LINUX)
		//Linux init
#endif
#ifdef OPENGL
		ImGui_ImplOpenGL3_Init("#version 410");

#elif defined(DIRECTX)
		//DirectX init
#endif
		if (renderer != nullptr)
			return;

		renderer = new Renderer();
		camera = new EngineCamera();

		Scene * scene = new Scene(std::string("Scene0"));

		ViewPort viewport;
		viewport.view = Matrix4d<float>(0, 1.2, -10, 0,
										0, 0, 1, 0,
										0, -1, 0, 0,
										0, 0, 0, 0);

		scene->cameras["MainCamera"] = viewport;
		scene->bound_camera = "MainCamera";
		scenes.add(scene, scene->name);
		renderer->bound_scene = 0;
		camera->set_view(scene->cameras["MainCamera"]);
		layer_stack.push_overlay(camera);
	}

	void GUI::detach()
	{
		layer_stack.pop_overlay(camera);

#ifdef WINDOWS
		ImGui_ImplWin32_Shutdown();
#endif
#ifdef OPENGL
		ImGui_ImplOpenGL3_DestroyDeviceObjects();
#endif
		delete renderer;
	}

	void GUI::update()
	{
		ImGuiIO & io = ImGui::GetIO();
		handled = !(io.WantCaptureMouse || io.WantCaptureKeyboard);

#ifdef OPENGL
		ImGui_ImplOpenGL3_NewFrame();
#endif
#ifdef WINDOWS
		RECT rect;
		GetClientRect(handler, &rect);
		ImGui_ImplWin32_NewFrame(rect);
#endif
		ImGui::NewFrame();

		Scene* scene = scenes.get(renderer->bound_scene);
		bool is_engine_focus = io.WantCaptureMouse;
		if(!camera->is_cursor_visible)
			if (!is_engine_focus)
				camera->set_view(scene->cameras[scene->bound_camera]);
			else
				camera->set_view(cameras[bound_camera]);

		//Draw Scene GUI
		scenes.get(renderer->bound_scene)->GUI();

		//Begin the GUI implementation
		ImGui::SetNextWindowSize(ImVec2(0, height * 0.5));
		ImGui::Begin(window_title, NULL, 
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		renderer->view = scene->cameras[scene->bound_camera].view;
		renderer->draw_scene();
		/*
		for (unsigned int i = 0; i < features_size; i++)
		{
			ImGui::SameLine();
			if (ImGui::Button(features[i].c_str(), ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0));)
			{
				if(i == MODELS)
					models_gui.show(this);
			}
		}*/

		renderer->view = cameras[bound_camera].view;
		models_gui.show(this);

		ImGui::End();
		ImGui::Render();
#ifdef OPENGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
	}

	void GUI::event(Event & e)
	{
		DISPATCH(GUI::on_mouse_move, e);
		DISPATCH(GUI::on_scroll, e);
		DISPATCH(GUI::on_key_down, e);
		DISPATCH(GUI::on_key_up, e);
		DISPATCH(GUI::on_mouse_button_down, e);
		DISPATCH(GUI::on_mouse_button_up, e);
		DISPATCH(GUI::on_key_typed, e);
	}

	void GUI::on_mouse_move(MouseMove & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.MousePos = ImVec2(e.get_x(), e.get_y());
		is_drag = is_left_click && safe == fail_safe;
		safe += is_left_click && safe < fail_safe;
		drag = safe == fail_safe;
	}

	void GUI::on_mouse_button_down(MouseButtonDown & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.MouseDown[e.get_button()] = true;
		is_left_click = e.get_button() == 0;
		dragndrop = false;
	}

	void GUI::on_mouse_button_up(MouseButtonUp & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.MouseDown[e.get_button()] = false;
		is_drag = false;
		is_left_click = false;
		safe = 0;
		dragndrop = drag;
		drag = false;
	}

	void GUI::on_scroll(MouseScroll & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.MouseWheelH += e.get_x();
		io.MouseWheel += e.get_y();
	}

	void GUI::on_key_down(KeyDown & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.KeysDown[e.get_key()] = true;
	}

	void GUI::on_key_up(KeyUp & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.KeysDown[e.get_key()] = false;
	}

	void GUI::on_key_typed(KeyTyped & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		if (e.get_key() < 256) io.AddInputCharacter(e.get_key());
	}
}