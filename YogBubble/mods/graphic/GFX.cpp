#include "GFX.h"
#include "../../tools/helper.h"
#include "../../yogcore/Graphic/RendererData.h"
#include "../../yogcore/Resource/ModelManager.h"
std::map<YID, ModelComponent*> renderingEntity;
std::map<YID, bool> renderMark;
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
void OnModelConstruct(IEvent* args) {
	// YID id = GetWrappedInfo<YID>(args,"data");
	// ModelComponent* modelComponent = dynamic_cast<ModelComponent*>(args->GetArg("model"));
	// renderingEntity[id] = modelComponent;
}
void OnModelDeconstruct(IEvent* args) {

}
std::map<std::string, bool> map;
void GFX::OnModuleUpdateLogic(){
	this->GetGfxCamera()->UpdateFromEntity();
	for(auto modelCm : *RendererData::GetInstance()){
		if(modelCm->entity){
			YogModel* aYogModel = new YogModel;
			if (modelCm->modelName == "") continue;;
			if(map[modelCm->modelName]==false){
				aYogModel->Initialize(env, dynamic_cast<ModelResource*>(ModelManager::GetInstance()->GetTargetFromName(modelCm->modelName)));
				env->yogModels.push_back(aYogModel);	
				map[modelCm->modelName] = true;
			}
		}
	}
	RendererData::GetInstance()->clear();


}
void GFX::OnModuleUpdate() {
	this->OnModuleUpdateLogic();
	this->RenderFrame();
}

void GFX::OnModuleRelease() {

}
