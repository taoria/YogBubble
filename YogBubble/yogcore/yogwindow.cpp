#include "../stdafx.h"
#include "yogwindow.h"
#include "../tools/helper.h"
#include "yog.h"
#include "Manager/YogManager.h"
#include "Event/EventSystem.h"
#include "Event/InfoWrapper.h"
#include "Math/Vec3.h"
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return YogWindow::get_instance()->msg_proc(hwnd, msg, wParam, lParam);
}

YogWindow::YogWindow(){}


YogWindow* YogWindow::yog_app = nullptr;

YogWindow* YogWindow::get_instance(){
	if (!yog_app){
		yog_app = new YogWindow();
		yog_app->InitWindow();
	}
	return yog_app;
}

HINSTANCE YogWindow::AppInst() const{
	return this->_h_app_inst;
}

HWND YogWindow::MainWindow() const{
	return this->_h_main_window;
}

float YogWindow::aspect_ration() const{
	return 0;
}

bool YogWindow::InitWindow(){
	WNDCLASS wc;
	wc.style = CS_GLOBALCLASS;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _h_app_inst;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"YogBubble";

	if (!RegisterClass(&wc)){
		YogDebugger::DebugErrorBox(L"×¢²á´°¿ÚÊ§°Ü Error Code:" + std::to_wstring(GetLastError()));
		return false;
	}
	RECT wr;
	wr.left = 100;
	wr.top = 100;
	wr.right = wr.left + _i_client_width;
	wr.bottom = wr.top + _i_client_height;
	// Compute window rectangle dimensions based on requested client area dimensions.
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	_h_main_window =	CreateWindow(L"YogBubble", L"YogBubble",
		WS_OVERLAPPEDWINDOW, wr.left,wr.top, wr.right-wr.left, wr.bottom-wr.top, nullptr, nullptr,_h_app_inst, nullptr
);
	ConsoleLogger::get_instance()->log_format(YOG_INFO, "window create:%d", _h_main_window);
	if (!_h_main_window){
		YogDebugger::DebugErrorBox(L"´´½¨´°¿ÚÊ§°Ü Error Code:" + std::to_wstring(GetLastError()));
		return false;
	}
	ShowWindow(_h_main_window, SW_SHOW);
	UpdateWindow(_h_main_window);

	return true;
}

bool YogWindow::Init3DEnvironment(){
	return false;
}

void YogWindow::CreateSwapChain(){ }
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT YogWindow::msg_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	if(ImGui_ImplWin32_WndProcHandler(hwnd,msg,wParam,lParam)){
		return true;
	}
	switch (msg){
	case WM_CREATE:
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN: {
		InfoWrapper<UINT>* params = new InfoWrapper<UINT>(wParam);
		EMIT_M("key down", "key code" ,params);
		break;
	}
	case WM_KEYUP:{
		InfoWrapper<UINT>* params = new InfoWrapper<UINT>(wParam);
		EMIT_M("key up", "key code", params);
		break;
	}
	case WM_MOUSEWHEEL:{
		InfoWrapper<UINT>* params = new InfoWrapper<UINT>(wParam);
		EMIT_M("mouse wheel", "data", params);
		break;
	}
	case WM_MOUSEMOVE:
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		Vec3 *vec = new Vec3(x, y, 0);
		InfoWrapper<Vec3>* params = new InfoWrapper<Vec3>(*vec);
		EMIT_M("mouse move", "data", params);
		break;
		}
	case WM_LBUTTONDOWN:
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		POINT p = { x,y };
	//	ScreenToClient(hwnd, &p);
		Vec3 *vec = new Vec3(static_cast<float>(p.x),static_cast<float>( p.y), 0);
		InfoWrapper<Vec3>* params = new InfoWrapper<Vec3>(*vec);
		EMIT_M("mouse left down", "data", params);
		break;
		}
	case WM_LBUTTONUP:
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		POINT p = { x,y };
	//	ScreenToClient(hwnd, &p);
		Vec3 *vec = new Vec3(static_cast<float>(p.x), static_cast<float>(p.y), 0);
		InfoWrapper<Vec3>* params = new InfoWrapper<Vec3>(*vec);
		EMIT_M("mouse left up", "data", params);
		break;
		}
	case WM_RBUTTONDOWN:
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		POINT p = { x,y };
	//	ScreenToClient(hwnd, &p);
		Vec3 *vec = new Vec3(static_cast<float>(p.x), static_cast<float>(p.y), 0);
		InfoWrapper<Vec3>* params = new InfoWrapper<Vec3>(*vec);
		EMIT_M("mouse right down", "data", params);
		break;
		}
	case WM_RBUTTONUP:
		{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		POINT p = { x,y };
		Vec3 *vec = new Vec3(static_cast<float>(p.x), static_cast<float>(p.y), 0);
		InfoWrapper<Vec3>* params = new InfoWrapper<Vec3>(*vec);
		EMIT_M("mouse right up", "data", params);
		break;
		}
	case WM_PAINT: {
		IYogManager* manager = get_manager("module manager");
		IYogModule* render_module = dynamic_cast<IYogModule*>(manager->GetTargetFromName("renderer"));
		ConsoleLogger::get_instance()->log("rendering", YOG_INFO);
		if (render_module)
			render_module->OnModuleUpdate();
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void YogWindow::ResolveModuleDependency(){

	YogDebugger::LogInfo("%s:%s", "try yo find dependency ", "D3DEnv");

}

void YogWindow::OnModuleInit(){
	ConsoleLogger::get_instance()->log("Yog Window initialized!", YOG_DEBUG);

}

void YogWindow::OnModuleUpdate(){
	MSG msg = {nullptr};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void YogWindow::OnModuleRelease(){}

void YogWindow::dock_to(HWND hwnd){
	SetParent(this->MainWindow(), hwnd);
}
