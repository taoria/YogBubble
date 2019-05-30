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
#include "yogcore/Resource/ModelManager.h"
#include "yogcore/Graphic/ModelComponent.h"
#include "yogcore/Scene/Scene.h"
#include "yogcore/Entity/UIEntity.h"
#include "yogcore/physics/Collider.h"
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
	// cout << "pan to" << endl;
	// camera.SetMainCamera();
}
void OnCollider(IEvent* arg){
	auto res = dynamic_cast<ICollider*>(arg->GetArg("first"));
	auto res2 = dynamic_cast<ICollider*>(arg->GetArg("second"));
	LOG_N_F(YOG_INFO, "Triggering collision event, Entities are %d %d", res->entity->GetId(), res2->entity->GetId());
}
GameEntity *gameEntity;
GameEntity *ball;
UIEntity *gameEntity2;
Scene scene;
void OnInit(IEvent* i_event){
	PanCamera();
 	gameEntity = new GameEntity;
	gameEntity2 = new UIEntity;
	ball = new GameEntity;
 	TransformComponent *transformComponent = gameEntity->GetComponent<TransformComponent>();
 	transformComponent->scale = Vec3(1.0f, 1.0f, 1.0f)*0.05;
	//注册资源
	ModelManager* modeManager = ModelManager::GetInstance();
	modeManager->RegisterModel("iron man", "E:\\YogBuild\\IronMan.obj");
	//modeManager->RegisterModel("flight", "E:\\YogBuild\\Model\\plane\\Futuristic combat jet.fbx");
	modeManager->RegisterModel("earth", "E:\\YogBuild\\Model\\earth\\earth.obj");
	auto com = gameEntity->GetComponent<ModelComponent>();
	modeManager->AddReference(com, "earth");
	auto com2 = ball->GetComponent<ModelComponent>();
	modeManager->AddReference(com2, "flight");
	gameEntity->AddComponent<BallCollider>();
	ball->AddComponent<BallCollider>();
	scene.SceneAddEntity(gameEntity);
	scene.SceneAddEntity(ball);
}
Vec3 preposition;
bool mouseDown= false;
void OnMouseWheeling(IEvent* iEvent){

}
void OnRightButtonDown(IEvent* iEvent){
	if(mouseDown==false){
		Vec3 vec3 = GetWrappedInfo<Vec3>(iEvent, "data");
		preposition = vec3;
		mouseDown = true;
		ShowCursor(false);
	}
}

void OnKeyDown(IEvent* ievent){
	if (Input::KeyCodeDown(KeyCode::L)) {
		scene.Save("E:\\YogBuild\\test.json");

	
	}
	if (Input::KeyCodeDown(KeyCode::H)) {
		scene.Load("E:\\YogBuild\\test.json");
		if (scene.gameEntities[0] == nullptr) {
		}
		else {
			gameEntity = static_cast<GameEntity*>(scene.gameEntities[0]);
		}

	}

}
void OnRightButtonUp(IEvent* iEvent){
	mouseDown = false;
	ShowCursor(true);
}
void OnUpdate(IEvent* events){
	TransformComponent *transformComponent = camera.GetComponent<TransformComponent>();
	if(Input::MouseRightPressed){
		Vec3 vec = Input::MousePosition;
		LOG_N_F(YOG_DEBUG, "%f %f %f", vec.x, vec.y, 0.0f);
		Vec3 diff = (vec - preposition);
		if(diff.Magnitude()!=0){
			diff = diff.Norm();
		}
		TransformComponent *transformComponent = camera.GetComponent<TransformComponent>();
		if (!transformComponent) return;
		transformComponent->rotation += Vec3(diff.y, diff.x, 0)*0.00235f* Data::TimerData::deltaTime;
		YogHelper::SetMousePosition(preposition);
	}
	float cameraSpeed = 0.004f;
	if (!transformComponent) return;
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
	transformComponent =  gameEntity->GetComponent<TransformComponent>();
	if (!transformComponent) return;
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
	if( Input::KeyCodeDown(KeyCode::SPACE)){
		transformComponent->position += transformComponent->GetUp()*Data::TimerData::deltaTime *cameraSpeed;
	}
	if (Input::KeyCodeDown(KeyCode::Z)) {
		transformComponent->position -= transformComponent->GetUp()*Data::TimerData::deltaTime *cameraSpeed;
	}
	camera.GetComponent<TransformComponent>()->position = transformComponent->position + transformComponent->GetForward() * 2 + transformComponent->GetUp() * 3;
	camera.GetComponent<TransformComponent>()->LookAtPos(transformComponent->position);

}
void OnLeftButtonDown(IEvent* event){

	Vec3 vec = Input::MousePosition;
	LOG_N_F(YOG_DEBUG, "Mouse is down at (%f ,%f)", vec.x, vec.y);
}
void OnLeftButtonUp(IEvent* event) {
	Vec3 vec = Input::MousePosition;
	LOG_N_F(YOG_DEBUG, "Mouse is up at (%f ,%f)", vec.x, vec.y);
}
void RegisterEvent(){
	EventSystem* eventSystem = dynamic_cast<EventSystem*>(get_manager("event system"));
	eventSystem->RegisterEvent("after init", OnInit);
	eventSystem->RegisterEvent("mouse right down", OnRightButtonDown);
	eventSystem->RegisterEvent("mouse right up", OnRightButtonUp);
	eventSystem->RegisterEvent("mouse left down", OnLeftButtonDown);
	eventSystem->RegisterEvent("mouse left up", OnLeftButtonUp);
	eventSystem->RegisterEvent("mouse wheel", OnMouseWheeling);
	eventSystem->RegisterEvent("on update", OnUpdate);
	eventSystem->RegisterEvent("key down", OnKeyDown);
	eventSystem->RegisterEvent("on collision",OnCollider);

}

void RegisterResource(){

};
int main(int argc, char **argv) {
	if(argc){
		if(argc==3){
			s = argv[2];
			EventSystem* event_system = dynamic_cast<EventSystem*>(get_manager("event system"));
			event_system->RegisterEvent("after init", OnInit);
		}
	}
	RegisterEvent();
	RegisterResource();
	yog* yogs = new yog;

	return 0;
}

