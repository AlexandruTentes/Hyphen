#pragma once

#define GUI_H_

#include "../CompiledHeaders.h"
#include "../Layer/Overlay.h"
#include "../Math/Math.h"
#include "../GraphicEngine/Renderer.h"
#include "../GraphicEngine/ModelParser/Parser.h"
#include "../GraphicEngine/Camera/EngineCamera.h"
#include "../Layer/LayerStack.h"
#include "../GraphicEngine/Scene.h"
#include "ImGuiInclude.h"
#include "ModelsGUI.h"
#include "ScenesGUI.h"
#include "ShadersGUI.h"
#include "MiscsGUI.h"

namespace Hyphen
{
	//Main GUI data
	enum GUIData
	{
		MODELS,
		SHADERS
	};
	enum GUIType
	{
		DYNAMIC,
		STATIC
	};
	static std::map<std::string, std::pair<GUIType, GUIData>> features;

	class GUI : public Overlay
	{
	public:
		HANDLER handler = NULL;
	public:
		void attach() override;
		void detach() override;
		void update() override;
		void event(Event & e) override;

		void on_mouse_move(MouseMove & e);
		void on_mouse_button_down(MouseButtonDown & e);
		void on_mouse_button_up(MouseButtonUp & e);
		void on_scroll(MouseScroll & e);
		void on_key_down(KeyDown & e);
		void on_key_up(KeyUp & e);
		void on_key_typed(KeyTyped & e);

		bool is_cursor_over_gui();
		void drag_model_to_scene(unsigned int i, std::string & name, 
			Collection<FileAndPath, std::string> & files, void (* at_drop)(GUI*, Model*, ModelTransfData*) = nullptr);
		void bind_scene(std::string & name);

		virtual ~GUI() = default;
	public:
		Filesystem& folder = Filesystem::get_instance();
		LayerStack& layer_stack = LayerStack::get_instance();
		Collection<Model, std::string>& models = Collection<Model, std::string>::get_instance();
		Collection<Scene, std::string>& scenes = Collection<Scene, std::string>::get_instance();
		Collection<ModelTransfData, std::string>& model_transf_data =
			Collection<ModelTransfData, std::string>::get_instance();
	private:
		float prev_time = 0.0f;
		std::string bound_camera = "";
		bool skip_scene_camera_bind_once = true;
		bool skip_engine_camera_bind_once = true;
		std::map<std::string, ViewPort> cameras;
		
		Renderer* renderer = nullptr;
		EngineCamera* camera = nullptr;

		//Other GUI components
		ModelsGUI models_gui;
		ScenesGUI scenes_gui;
		ShadersGUI shaders_gui;
		MiscsGUI miscs_gui;

		//Drag and drop
		bool dragndrop = false;
		bool drag = false;
		bool is_drag = false;
		bool is_left_click = false;
		unsigned int fail_safe = 5;	//No of mouse pos changes before drag is detected
		unsigned int safe = 0;
		bool start_drag = false;
		unsigned int drag_model_index = 0;
		std::string drag_model_name = "";
		bool is_preview = false;
		bool model_dragndrop = false;

		// A simple way to put a mutex functionality on a function call with no threading
		unsigned short int bound = 0;				// Index of the drag'n'drop function call (n-th function call for drag'n'drop)
		unsigned short int bound_count = 0;			// A count to check which n-th call matches with the bound index

		friend class ModelsGUI;
		friend class ShadersGUI;
		friend class ScenesGUI;
		friend class MiscsGUI;
		friend class Scene;
	private:
		unsigned short int feature_type = 0;
		unsigned int selected_feature = 0;
	};
}