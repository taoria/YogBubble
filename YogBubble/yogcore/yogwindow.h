#pragma once
#include "windows.h"
#include "../yogcore/Module/IYogModule.h"

class YOG_DLL_EXPORT YogWindow:public IYogModule{
public:
	YogWindow();
	static YogWindow* get_instance();
	HINSTANCE AppInst() const;
	HWND MainWindow() const;
	float aspect_ration() const;
	bool InitWindow();
	bool Init3DEnvironment();
	void CreateSwapChain();
	virtual LRESULT msg_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void ResolveModuleDependency() override;
	void run();
	void OnModuleInit() override;
	void OnModuleUpdate() override;
	void OnModuleRelease() override;
	void dock_to(HWND hwnd);
protected:
	static YogWindow* yog_app;
	HINSTANCE _h_app_inst = nullptr; // application instance handle
	HWND      _h_main_window = nullptr; // main window handle
	int _i_client_width = 1440;
	int _i_client_height = 900;

};

