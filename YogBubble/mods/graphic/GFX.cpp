#include "GFX.h"
#include "../../tools/helper.h"
#include "../../yogcore/Graphic/RendererData.h"

GFX::GFX(YogWindow* yog_window) {
	// env_ = new D3DEnv();
	env = new Environment;
	env->InitD3DEnv(yog_window->MainWindow());



}
void GFX::CreateRenderTargetView() {

}
void GFX::BeginFrame() {
	
	env->env_start();
	
}
void GFX::EndFrame() {
	env->env_end();
	
}
void GFX::RenderFrame() {
	this->BeginFrame();
	this->EndFrame();
}
GFX::~GFX()
{
}
D3DCamera* GFX::GetGfxCamera(){
	return &env->camera;
}
void GFX::ResolveModuleDependency() {
}

void GFX::OnModuleInit() {
}
void GFX::OnModuleUpdateLogic(){
	this->GetGfxCamera()->UpdateFromEntity();
	for(auto modelCm : *RendererData::GetInstance()){
		if(modelCm->entity){
			YogModel* aYogModel = new YogModel;
			aYogModel->Initialize(env);
			aYogModel->entity = modelCm->entity;
			env->yogModels.push_back(aYogModel);
		}
	}
	RendererData::GetInstance()->clear();
	for (auto model : env->yogModels) {
		if (model->entity)
			model->UpdateFromTransform();
	}

}
void GFX::OnModuleUpdate() {
	this->OnModuleUpdateLogic();
	this->RenderFrame();
}

void GFX::OnModuleRelease() {

}
