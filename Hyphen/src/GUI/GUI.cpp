#include "../../lib/GUI/GUI.h"

namespace Hyphen
{
	void GUI::attach()
	{
		features.insert({ "Models", std::pair<GUIType, GUIData>(GUIType::DYNAMIC, GUIData::MODELS) });
		features.insert({ "Shaders", std::pair<GUIType, GUIData>(GUIType::DYNAMIC, GUIData::SHADERS) });

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
		scene->no = renderer->scenes_no;
		renderer->scenes_no++;
		scene->load_scene_data(this);
		scenes.add(scene, scene->name);
		renderer->bound_scene = "Scene0";
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

		scenes_gui.show(this);						//Draw Scenes GUI list
		miscs_gui.show(this);						//Draw Miscs GUI (camera, etc)
		scenes.get(renderer->bound_scene)->GUI();	//Draw Scene GUI

		Scene* scene = scenes.get(renderer->bound_scene);
		bool is_engine_focus = io.WantCaptureMouse;
		if(!camera->is_cursor_visible)
			if (!is_engine_focus)
				camera->set_view(scene->cameras[scene->bound_camera]);
			else
				camera->set_view(cameras[bound_camera]);

		//Begin the GUI implementation
		ImGui::SetNextWindowSize(ImVec2(0, height * 0.5));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::Begin(window_title, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		renderer->view = scene->cameras[scene->bound_camera].view;
		renderer->draw_scene();
		
		if(!selected_feature || feature_type == GUIType::STATIC)
			for (auto &feature : features)
				if (ImGui::Button(feature.first.c_str(), ImVec2(aspect_ratio * 50.0, aspect_ratio * 15.0)))
				{
					selected_feature = feature.second.second + 1;
					feature_type = feature.second.first;
					break;
				}

		if (selected_feature && feature_type == GUIType::DYNAMIC && ImGui::Button("<"))
				selected_feature = 0;

		switch (selected_feature - 1)
		{
		case GUIData::MODELS:
		{
			renderer->view = cameras[bound_camera].view;
			models_gui.show(this);
			break;
		}
		case GUIData::SHADERS:
		{
			shaders_gui.show(this);
			break;
		}
		}

		ImGui::End();
		ImGui::Render();
#ifdef OPENGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
		bound_count = 0;
	}

	bool GUI::is_cursor_over_gui()
	{
		return ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenDisabled |
			ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_AllowWhenBlockedByPopup);
	}

	void GUI::drag_model_to_scene(unsigned int i, std::string & name,
		Collection<FileAndPath, std::string>& files, void(*at_drop)(GUI*, Model*, ModelTransfData*))
	{
		bound_count++;

		// Get the model index when drag is detected inside gui window
		if (ImGui::IsItemHovered() && drag && !start_drag)
		{
			drag_model_name = name;
			drag_model_index = i;
			start_drag = true;
			bound = bound_count;
		}

		if (bound_count != bound)
			return;

		// While dragging inside gui window, make model image follow cursor
		// Also read model data from disk
		if (start_drag && drag && is_cursor_over_gui() && i == drag_model_index && !is_preview)
		{
			model_dragndrop = true;
			read_raw_model(*files.get(drag_model_index));
			ImGui::OpenPopup("");
			ImGui::SetNextWindowPos(ImVec2(ImGui::GetMousePos().x - aspect_ratio * 30.0 * 0.5,
				ImGui::GetMousePos().y - aspect_ratio * 30.0 * 0.5));
			ImGui::BeginPopup("", ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs);
			ImGui::Image((ImTextureID)i, ImVec2(aspect_ratio * 30.0, aspect_ratio * 30.0));
			ImGui::EndPopup();
		}

		// Once a drop is detected after a drag from the gui, reset drag'n'drop data
		if (dragndrop && model_dragndrop)
		{
			Model* m = models.get(drag_model_name);
			std::string model_scene_name = m->model_root +
				std::to_string(scenes.get(renderer->bound_scene)->no) +
				std::to_string(m->model_scene_no);

			if (at_drop && !is_cursor_over_gui())
				at_drop(this, m, model_transf_data.get(model_scene_name));

			// If a model has been added to the scene, increment the model counter in case 
			// a copy of the same model will be added later on
			if (!is_cursor_over_gui())
				models.get(drag_model_name)->model_scene_no++;

			start_drag = false;
			dragndrop = false;
			model_dragndrop = false;
		}

		// While deragging inside the scene, load the model into the scene and make it follow the cursor
		if (start_drag && drag && !is_cursor_over_gui())
		{
			// Calculate a unique name for the new model
			Model * m = models.get(drag_model_name);
			std::string model_scene_name = m->model_root +
				std::to_string(scenes.get(renderer->bound_scene)->no) +
				std::to_string(m->model_scene_no);

			// Load the model into the scene if it is not already, else make it follow the cursor
			if (!scenes.get(renderer->bound_scene)->models.count(model_scene_name))
			{
				ModelTransfData* data = new ModelTransfData();
				data->position->vec[0] = (float)ImGui::GetMousePos().x / width;
				data->position->vec[2] = (float)ImGui::GetMousePos().y / height;
				model_transf_data.add(data, model_scene_name);
				m->bind_data(model_scene_name);
				renderer->render_model(m);
				scenes.get(renderer->bound_scene)->models[model_scene_name] = m;
			}
			else
			{
				model_transf_data.get(model_scene_name)->position->vec[0] = -(float)ImGui::GetMousePos().x / width * 10;
				//model_transf_data.get(model_scene_name)->translation[2] = -(float) 1 / ImGui::GetMousePos().y;
			}
		}
	}

	void GUI::bind_scene(std::string& name)
	{
		renderer->bound_scene = name;
		camera->set_view(scenes.get(name)->cameras[scenes.get(name)->bound_camera]);
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