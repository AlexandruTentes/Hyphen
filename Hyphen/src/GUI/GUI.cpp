#include "../../lib/GUI/GUI.h"

#ifdef GUI_H_

namespace Hyphen
{
	void GUI::attach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplWin32_Init(handler);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void GUI::detach()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplOpenGL3_DestroyDeviceObjects();
	}

	void GUI::update()
	{
		RECT rect;
		GetClientRect(handler, &rect);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplWin32_NewFrame(rect);
		ImGui::NewFrame();

		//Temporary
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::event(Event & e)
	{

	}
}

#endif