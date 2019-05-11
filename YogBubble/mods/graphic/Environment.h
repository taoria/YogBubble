#pragma once

#include "../../stdafx.h"
#include "../../yogcore/Module/IYogModule.h"
#include "../../tools/d12x.h"
#include "YogShader.h"
#include <SpriteBatch.h>
#include "IndexBuffer.h"
#include "constantBuffer.h"
#include "graphic.h"
#include "D3DCamera.h"
#include "VertexBuffer.h"
#include "YogModel.h"

//#include "VertexBuffer.h"

class __declspec(dllexport) Environment : public IYogModule
{
public:
	YogVertexShader* m_yogVertexShader;
	YogPixelShader* m_yogPixelShader;
	std::vector<YogModel*> yogModels;
	ConstantBuffer<VS_CB_DATA> vs_cb_data;
	ConstantBuffer<PS_CB_DATA> ps_cb_data;
	ComPtr<ID3D11RasterizerState> m_rasterizerState;
	std::unique_ptr<SpriteBatch> spriteBatch;
	std::unique_ptr<SpriteFont> spriteFont;
	D3DCamera camera;
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<ID3D11ShaderResourceView> myTexture;
	ComPtr<ID3D11ShaderResourceView> demoTexture;
	void InitDebugController();
	float width;
	float height;
	Environment();

	~Environment();


	void GetDefaultAdapters();

	void InitD3DEnv(HWND hWnd);
	void InitGui(HWND hWnd);
	void YogCreateRenderTarget();

	ComPtr<IDXGISwapChain> GetSwapChain();
	
	ComPtr<ID3D11Device> GetDirectDevice();
	YID GetId() override;
	std::string GetName() override;
	void env_end();
	void env_start();
	void ResolveModuleDependency() override;

	// void on_module_init() override;
	// void on_module_load() override;
	// void on_module_release() override;
protected:
	ComPtr<IDXGIFactory4> m_dxgi_factory_;
#ifdef D3D12


	ComPtr<IDXGISwapChain3> m_swap_chain_;

	ComPtr<ID3D12Device> m_device_;
	ComPtr<ID3D12RootSignature> m_root_signature_;
	ComPtr<ID3D12Debug> m_debug_controller_;
	ComPtr<ID3D12InfoQueue> m_debug_infos;
	ComPtr<ID3D12Fence> m_fence_;
	ComPtr<ID3D12CommandAllocator> m_command_allocator_;
	ComPtr<ID3D12GraphicsCommandList> m_command_list_;
	UINT m_frame_index  = 0;
	UINT64 m_fence_value=0;
	ComPtr<ID3D12Fence> m_fence;
	HANDLE m_fence_event;
	ComPtr<ID3D12Resource> m_vertex_buffer_;
	ComPtr<ID3D12PipelineState> m_pipeline_state;
	D3D12_VERTEX_BUFFER_VIEW m_vertex_buffer_view_;
	CD3DX12_VIEWPORT m_viewport;
	CD3DX12_RECT m_scissor_rect;



	ComPtr<ID3D12CommandQueue> m_cmd_queue_;


	ComPtr<ID3D12DescriptorHeap> m_rtv_heap_;

	std::vector<ComPtr<ID3D12Resource>> m_render_target_views_;
#else

	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	ComPtr<IDXGISwapChain> m_swapChain;

	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	ComPtr<ID3D11RasterizerState> m_rasterState;
	ComPtr<ID3D11SamplerState> m_samplerState;

	ComPtr<ID3D11BlendState> m_blendState;
	bool InitializeShader();
	ComPtr<ID3D10Blob> m_vertexShader;
	std::vector<ComPtr<IDXGIAdapter>> adapters;

#endif
	void CreateRtvHeaps();
	void YogCreateD3DDevice();
	void YogCreateCommandQueue();
	void InitializeD3DEnv(HWND h_window);
	void InitializeSamplerState();
	void LogAdapters();
	void LoadInfo();
	void YogInitDxgiFactory();

	UINT n_rtv_descriptor_size_ = 0U;
	UINT n_frame_back_buffer_count = 2U;

public:
	void SetId(YID id) override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
	void OnModuleInit() override;
	void OnModuleUpdate() override;
	void OnModuleRelease() override;
	void OnKeyDown(IEvent* info);
};
