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
	}

	void GUI::detach()
	{
#ifdef WINDOWS
		ImGui_ImplWin32_Shutdown();
#endif
#ifdef OPENGL
		ImGui_ImplOpenGL3_DestroyDeviceObjects();
#endif
	}

	void GUI::update()
	{
		ImGuiIO & io = ImGui::GetIO();
		handled = io.WantCaptureMouse || io.WantCaptureKeyboard;

#ifdef OPENGL
		ImGui_ImplOpenGL3_NewFrame();
#endif
#ifdef WINDOWS
		RECT rect;
		GetClientRect(handler, &rect);
		ImGui_ImplWin32_NewFrame(rect);
#endif
		ImGui::NewFrame();

		//Temporary
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

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
	}

	void GUI::on_mouse_button_down(MouseButtonDown & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.MouseDown[e.get_button()] = true;
	}

	void GUI::on_mouse_button_up(MouseButtonUp & e)
	{
		ImGuiIO & io = ImGui::GetIO();
		io.MouseDown[e.get_button()] = false;
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