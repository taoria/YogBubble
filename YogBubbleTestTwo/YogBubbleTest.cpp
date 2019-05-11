// YogBubbleTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "yogcore/yog.h"
#include "yogcore/Event/IEvent.h"
#include "yogcore/Manager/YogManager.h"
#include <iostream>
#include "yogcore/Event/EventSystem.h"
#include "yogcore/Graphic/Camera.h"
#include "yogcore/Event/InfoWrapper.h"
#include "tools/Data/Data.h"
#include "yogcore/Entity/TransformComponent.h"
#include "yogcore/Entity/GameEntity.h"
#include "tools/Data/Input.h"
using namespace std;
#pragma  warning(disable:4996)

#pragma warning(disable:4996) 
 // int CALLBACK WinMain(
	// HINSTANCE hInstance,
	// HINSTANCE hPrevInstance,
 // 	LPTSTR lpCmdLine,
	// int nCmdShow )
char *s;
HWND get_hwnd_from_param(char* s){
	HWND hwnd = (HWND)atoi(s);
	return hwnd;
}
Camera camera;
void PanCamera() {
	cout << "pan to" << endl;
	camera.SetMainCamera();
}
GameEntity *gameEntity;
GameEntity *gameEntity2;
void OnInit(IEvent* i_event){
	PanCamera();
	gameEntity = new GameEntity;
	gameEntity2 = new GameEntity;
}
Vec3 preposition;
bool mouseDown= false;
void OnMouseWheeling(IEvent* iEvent){
	auto wParam  = GetWrappedInfo<WPARAM>(iEvent, "data");
	auto fwKeys = GET_KEYSTATE_WPARAM(wParam);
	auto zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
	TransformComponent *transformComponent = camera.GetComponent<TransformComponent>();
	transformComponent->position += transformComponent->GetForward()*zDelta*0.0002f;
}
void OnRightButtonDown(IEvent* iEvent){
	if(mouseDown==false){
		Vec3 vec3 = GetWrappedInfo<Vec3>(iEvent, "data");
		preposition = vec3;
		mouseDown = true;
		ShowCursor(false);
	}
}
void OnRightButtonUp(IEvent* iEvent)
{
	mouseDown = false;
	ShowCursor(true);
}
void OnUpdate(IEvent* events){
	if(Input::MouseRightPressed){
		Vec3 vec = Input::MousePosition;
		LOG_N_F(YOG_DEBUG, "%f %f %f", vec.x, vec.y, 0.0f);
		Vec3 diff = (vec - preposition);
		if(diff.Magnitude()!=0){
			diff = diff.Norm();
		}
		TransformComponent *transformComponent = camera.GetComponent<TransformComponent>();
		transformComponent->rotation += Vec3(diff.y, diff.x, 0)*0.00235f* Data::TimerData::deltaTime;
		YogHelper::SetMousePosition(preposition);
	}
	float cameraSpeed = 0.004f;
	TransformComponent *transformComponent = camera.GetComponent<TransformComponent>();
	if(Input::KeyCodeDown(KeyCode::W)){
		transformComponent->position += transformComponent->GetForward()*Data::TimerData::deltaTime *cameraSpeed;
	}
	if (Input::KeyCodeDown(KeyCode::A)) {
		transformComponent->position -= transformComponent->GetRight()*Data::TimerData::deltaTime * cameraSpeed;
	}
	if (Input::KeyCodeDown(KeyCode::D)) {
		transformComponent->position += transformComponent->GetRight()*Data::TimerData::deltaTime *cameraSpeed;
	}
	if (Input::KeyCodeDown(KeyCode::S)) {
		transformComponent->position -= transformComponent->GetForward()*Data::TimerData::deltaTime *cameraSpeed;
	}
	transformComponent = gameEntity->GetComponent<TransformComponent>();
	if(Input::KeyCodeDown(KeyCode::UP)){
		transformComponent->position += transformComponent->GetForward()*Data::TimerData::deltaTime *cameraSpeed;
	}
	if (Input::KeyCodeDown(KeyCode::DOWN)) {
		transformComponent->position -= transformComponent->GetForward()*Data::TimerData::deltaTime *cameraSpeed;
	}
	if (Input::KeyCodeDown(KeyCode::LEFT)) {
		transformComponent->position -= transformComponent->GetRight()*Data::TimerData::deltaTime *cameraSpeed;
	}
	if (Input::KeyCodeDown(KeyCode::RIGHT)) {
		transformComponent->position += transformComponent->GetRight()*Data::TimerData::deltaTime *cameraSpeed;
	}
}
void RegisterEvent(){
	EventSystem* eventSystem = dynamic_cast<EventSystem*>(get_manager("event system"));
	eventSystem->RegisterEvent("after init", OnInit);
	eventSystem->RegisterEvent("mouse right down", OnRightButtonDown);
	eventSystem->RegisterEvent("mouse right up", OnRightButtonUp);
	eventSystem->RegisterEvent("mouse wheel", OnMouseWheeling);
	eventSystem->RegisterEvent("on update", OnUpdate);
}
int main(int argc, char **argv) {
	if(argc){
		if(argc==3){
			s = argv[2];
			EventSystem* event_system = dynamic_cast<EventSystem*>(get_manager("event system"));
			event_system->RegisterEvent("after init", OnInit);
		}
	}
	RegisterEvent();
	yog* yogs = new yog;

	return 0;
}

