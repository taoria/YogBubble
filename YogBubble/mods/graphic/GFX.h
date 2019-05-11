#pragma once
#include "Environment.h"
#include "../../yogcore/yogwindow.h"
class GFX :public IYogModule
{
public:
	GFX(YogWindow *yog_window);
	void CreateRenderTargetView();
	void BeginFrame();
	void EndFrame();
	void RenderFrame();
	
	~GFX();
	D3DCamera* GetGfxCamera();
	void ResolveModuleDependency() override;
	void OnModuleInit() override;
	void OnModuleUpdateLogic();
	void OnModuleUpdate() override;
	void OnModuleRelease() override;
#ifdef _DEBUG
	
#endif
protected:
	Environment* env;
};

