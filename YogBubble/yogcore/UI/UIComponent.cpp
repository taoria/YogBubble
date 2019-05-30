#include "UIComponent.h"
#include "../../mods/ui/imgui.h"
#include "../../mods/ui/imgui_impl_win32.h"
#include "../../mods/ui/imgui_impl_dx11.h"

void UIComponent::OnUpdate(){
	
}

void UIComponent::OnDraw(){


	ImGui::Begin("Test");
	ImGui::Text("this is example text");
	//ImGui::DragFloat("Alpha", &alpha, 0.1f, 0, 1);
	ImGui::End();

}

COMPONENT_MARK UIComponent::GetComponentMark(){
	return COMPONENT_RENDER;
}
