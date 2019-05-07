#include "GFX.h"
#include "../../tools/helper.h"

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

void GFX::OnModuleUpdate() {
	this->RenderFrame();
}

void GFX::OnModuleRelease() {

}