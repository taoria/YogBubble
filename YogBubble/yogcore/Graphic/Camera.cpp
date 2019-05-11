#include "Camera.h"
#include "../../tools/helper.h"
#include "../../mods/graphic/GFX.h"
#include "../Manager/YogManager.h"
#include "../../mods/graphic/D3DCamera.h"
#include "../Entity/TransformComponent.h"


void Camera::CameraAttatchedToGraphicCamera(D3DCamera* yogCamera){
	yogCamera->Initialize(this);
}


void Camera::SetMainCamera(){
	IYogManager*  i_manager = get_manager("module manager");
	GFX*  gfx = dynamic_cast<GFX*>(i_manager->GetTargetFromName("renderer"));
	CameraAttatchedToGraphicCamera(gfx->GetGfxCamera());
}

Camera::~Camera(){
}


Camera::Camera(){
	AddComponent<TransformComponent>();
	AddComponent<CameraComponent>();
}

YID Camera::GetId() { return 0; }

void Camera::SetId(YID id){}
std::string Camera::GetName() { return "camera"; }
void Camera::SetName(std::string){}
void Camera::OnInit(){}
void Camera::OnRelease(){}
