// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3d11.lib")
#ifdef WIN32
#endif
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d11.h>
#include <vector>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"
//#include <d3dx12.h>
using namespace Microsoft::WRL;
using namespace DirectX;
#pragma warning( disable: 4251 )
#pragma warning( disable: 4996 )
#ifdef YOGBUBBLE_EXPORTS
#define YOG_DLL_EXPORT __declspec(dllexport)
#else
#define YOG_DLL_EXPORT __declspec(dllimport)
#endif

// 在此处引用程序需要的其他标头
