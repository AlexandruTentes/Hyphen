#pragma once

#include "../CompiledHeaders.h"
#include "../Layer/Overlay.h"
#include "../Math/Math.h"
#include "../GraphicEngine/Renderer.h"
#include "../GraphicEngine/Collection/FolderData.h"
#include "../GraphicEngine/ModelParser/Parser.h"
#include "../GraphicEngine/Camera/EngineCamera.h"
#include "../Layer/LayerStack.h"
#include "../GraphicEngine/Scene.h"
#include "ModelsGUI.h"

#define GUI_H_

#ifdef WINDOWS //For now the GUI works only for windows machines
	#include "../../thirdparty/imgui/imgui_impl_win32.h"
	#define HANDLER HWND 
#elif defined(LINUX)
	#include "../../thirdparty/imgui/" // to be implemented later
#endif

#ifdef OPENGL //For now the GUI works only with opengl
	#include "../../thirdparty/imgui/imgui_impl_opengl3.h"
#endif

namespace Hyphen
{
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

		virtual ~GUI() = default;
	public:
		FolderData& folder = FolderData::get_instance();
		LayerStack& layer_stack = LayerStack::get_instance();
		Collection<Model, std::string>& models = Collection<Model, std::string>::get_instance();
		Collection<Scene, std::string>& scenes = Collection<Scene, std::string>::get_instance();
		Collection<ModelTransfData, std::string>& model_transf_data =
			Collection<ModelTransfData, std::string>::get_instance();
	private:
		float prev_time = 0.0f;
		
		Renderer* renderer = nullptr;
		EngineCamera* camera;

		//Other GUI components
		ModelsGUI models_gui;

		//Drag and drop
		bool dragndrop = false;
		bool drag = false;
		bool is_drag = false;
		bool is_left_click = false;
		unsigned int fail_safe = 5;	//No of mouse pos changes before drag is detected
		unsigned int safe = 0;
		bool start_drag = false;
		unsigned int drag_model_index = 0;
		bool is_preview = false;
		bool model_dragndrop = false;

		friend class ModelsGUI;
	private:
		//Main GUI data
		static const int features_size = 3;
		std::string features[features_size] = {"Models", "Shaders", "Scenes"};
		unsigned int selected_feature = 0;
	};
}