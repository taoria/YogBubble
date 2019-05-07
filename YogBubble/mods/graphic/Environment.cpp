#include "Environment.h"
#include <iostream>
#include "../../tools/d12x.h"
#include "../../tools/helper.h"
#include "graphic.h"
#include "../../yogcore/Manager/YogManager.h"
#include "../../yogcore/Event/EventSystem.h"
#include "../ui/imgui.h"
#include "../ui/imgui_impl_win32.h"
#include "../ui/imgui_impl_dx11.h"

void ThrowIfFailed(HRESULT create_dxgi_factory){
	if (FAILED(create_dxgi_factory)){
		throw new std::exception;
	}
}

void Environment::DrawTestScene(){

	UINT stride = sizeof(Dot);
	UINT offset = 0;

	this->m_deviceContext->IASetVertexBuffers(0, 1, this->m_vertexBuffer.GetAddressOf(), &stride, &offset);
	this->m_deviceContext->IASetIndexBuffer(this->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	this->m_deviceContext->IASetVertexBuffers(0, 1, this->m_vertexBuffer.GetAddressOf(), &stride, &offset);
	this->m_deviceContext->DrawIndexed(this->indexBuffer.BufferSize(),0,0);



	
}
void Environment::TestScene(){
// 	Vertex triangleVertices[] = {
// 	{ { 0.0f, 0.25f , 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
// 	{ { 0.25f, -0.25f , 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
// 	{ { -0.25f, -0.25f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
// { { 0.0f, 0.1f , .0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
// { { 0.1f, -0.1f , .0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
// { { -0.1f, -0.1f, .0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }
// 	};
	Dot v[] ={
		Dot{{-0.5f,-0.5f,0},{0.0f,1.0f}}, //Bottom left
		Dot{{-0.5f,0.5f,0},{0.0f,0.0f}}, //Top left
		Dot{{0.5f,0.5f,0},{1.0f,0.0f}}, //Top Right
		Dot{{0.5f,-0.5f,0},{1.0f,1.0f}} //bottom right
	};
	DWORD indices[] = {
		0,1,2,
		0,2,3
	};
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = (sizeof(Dot))*(ARRAYSIZE(v));
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
	vertexBufferData.pSysMem = v;
	HRESULT hr = this->m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData,this->m_vertexBuffer.GetAddressOf());
	if(FAILED(hr)){
		YogDebugger::DebugError(hr);
	}

	hr = this->indexBuffer.Initialize(m_device.Get(), indices, ARRAYSIZE(indices));
//	hr = this->m_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData2, this->m_vertexBuffer2.GetAddressOf());
	if (FAILED(hr)) {
		YogDebugger::DebugError(hr);
	}


}

void Environment::InitDebugController(){

	//D3D12GetDebugInterface(IID_PPV_ARGS(m_debug_controller_.GetAddressOf()));
}

Environment::Environment(){

	width = 1024;
	height = 768;

}

void Environment::YogInitDxgiFactory(){
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(&m_dxgi_factory_));
	YogDebugger::ThrowIfFailed(hr);
}

void Environment::SetId(YID id){ }

void Environment::SetName(std::string){}

void Environment::OnInit(){
	
}

void Environment::OnRelease(){}

void Environment::OnModuleInit(){

	YogInitDxgiFactory();

	LogAdapters();

	InitDebugController();

	YogCreateD3DDevice();


	YogCreateCommandQueue();
}

void Environment::OnModuleUpdate(){
	
}

void Environment::OnModuleRelease(){
	
}

void Environment::OnKeyDown(IEvent *info){
	
}

bool Environment::InitializeShader(){

	m_yogVertexShader = new YogVertexShader;
	m_yogVertexShader->InitializeShader(this);
	m_yogPixelShader = new YogPixelShader;
	m_yogPixelShader->InitializeShader(this);
	TestScene();
	return true;
}

void Environment::CreateRtvHeaps(){
#ifdef D3D12
	D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {};
	rtv_heap_desc.NumDescriptors = n_frame_back_buffer_count;
	rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtv_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	YogDebugger::ThrowIfFailed(m_device_->CreateDescriptorHeap(&rtv_heap_desc, IID_PPV_ARGS(&m_rtv_heap_)));
	n_rtv_descriptor_size_ = m_device_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
#endif
}

Environment::~Environment(){}

void Environment::GetDefaultAdapters(){}


void Environment::YogCreateD3DDevice(){
#ifdef D3D12
	YogDebugger::ThrowIfFailed(D3D12CreateDevice(
			(*adapters)[0].Get(),
	 		D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_device_)
		));
#endif
}

void Environment::YogCreateCommandQueue(){
	//命令队列
	// D3D12_COMMAND_QUEUE_DESC queueDesc = {};
#ifdef D3D12
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	ComPtr<ID3D12CommandQueue> cmd_queue;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	YogDebugger::ThrowIfFailed( m_device_->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_cmd_queue_)));
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

#endif
}

void Environment::InitializeD3DEnv(HWND h_window){

	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
	// Describe and create the swap chain.
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

	swapChainDesc.BufferCount = 2;

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.BufferDesc.Height = this->height;
	swapChainDesc.BufferDesc.Width = this->width;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.OutputWindow = h_window;
	swapChainDesc.Windowed = true;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	HRESULT hr;
	ComPtr<IDXGISwapChain1> swap_chain;
	UINT creationFlags = 0;
	#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif
	hr = D3D11CreateDeviceAndSwapChain(
		adapters[0].Get(),
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		creationFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&swapChainDesc,
		this->m_swapChain.GetAddressOf(),
		this->m_device.GetAddressOf(),
		NULL,
		this->m_deviceContext.GetAddressOf());
	if(FAILED(hr)){
		YogDebugger::DebugError(hr);
		return;
	}
	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfFailed(this->m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

	
	ThrowIfFailed(this->m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, this->m_renderTargetView.GetAddressOf()));



	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MaxDepth = 1;
	viewport.MinDepth = 0;
	this->m_deviceContext->RSSetViewports(1, &viewport);

	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	//rasterizerDesc.FrontCounterClockwise = TRUE;
	hr = this->m_device->CreateRasterizerState(&rasterizerDesc, m_rasterizerState.GetAddressOf());

	D3D11_TEXTURE2D_DESC depthStencilDesc ;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

//	ID3D11Texture2D * depthStencil = NULL;
	hr = this->m_device->CreateTexture2D(&depthStencilDesc, NULL,m_depthStencilBuffer.GetAddressOf());
	if (FAILED(hr)) {
		YogDebugger::DebugError(L"failed create depth stencil buffer :", hr);
	}
	hr = this->m_device->CreateDepthStencilView(this->m_depthStencilBuffer.Get(), nullptr, this->m_depthStencilView.GetAddressOf());
	if(FAILED(hr)){
		YogDebugger::DebugError(L"failed create depth stencil view :",hr);
	}

	this->m_deviceContext->OMSetRenderTargets(1, this->m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {};
	depthStencilStateDesc.DepthEnable = true;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	hr = m_device->CreateDepthStencilState(&depthStencilStateDesc,this->m_depthStencilState.GetAddressOf());

	spriteBatch = std::make_unique<SpriteBatch>(m_deviceContext.Get());
	spriteFont = std::make_unique<SpriteFont>(m_device.Get(), L"D:\\YogBuild\\brush_script_mt.spritefont");

	InitializeSamplerState();

	hr = CreateWICTextureFromFile(this->m_device.Get(), L"D:\\YogBuild\\test.png", nullptr, this->myTexture.GetAddressOf());
	if(FAILED(hr)){
		LOG_F(YOG_ERROR, "Failed to load resources %s error code  %X", "test.png", hr);
		return;
	}

	constantBuffer.Initialize(m_device.Get(), m_deviceContext.Get());

	camera.SetPosition(0, 0, -2);
	camera.SetProjectionValues(90.0f, width / height, 0.1, 1000);
}
void Environment::InitializeSamplerState(){
	HRESULT hr;
	D3D11_SAMPLER_DESC samplerStateDesc = {};
	samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerStateDesc.MinLOD = 0;
	samplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = this->m_device->CreateSamplerState(&samplerStateDesc, m_samplerState.GetAddressOf());
}
void Environment::LogAdapters(){

	UINT i = 0;
	ComPtr<IDXGIAdapter> adapter = nullptr;
	while (m_dxgi_factory_->EnumAdapters(i, &adapter) != DXGI_ERROR_NOT_FOUND){
		DXGI_ADAPTER_DESC desc;
		adapter->GetDesc(&desc);
		std::wstring wstr = L"Adapter info:\n";
		wstr += desc.Description;
		//YogDebug::debug_message(wstr);
		adapters.push_back(adapter);
		++i;
	}
}

void Environment::LoadInfo(){
#ifdef D3D12
	ComPtr<ID3DBlob> signature;
	ComPtr<ID3DBlob> error;
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	
	ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
	ThrowIfFailed(m_device_->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_root_signature_)));
	float m_aspect_ratio = 1;
	ComPtr<ID3DBlob> vertexShader;
	ComPtr<ID3DBlob> pixelShader;

#if defined(_DEBUG)
	// Enable better shader debugging with the graphics debugging tools.
	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	UINT compileFlags = 0;
#endif
	Vertex triangleVertices[] = {
		{ { 0.0f, 0.25f * m_aspect_ratio, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ { 0.25f, -0.25f * m_aspect_ratio, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
		{ { -0.25f, -0.25f * m_aspect_ratio, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
	};
	const UINT vertexBufferSize = sizeof(triangleVertices);
	ThrowIfFailed(D3DCompileFromFile(YogHelper::get_asset_path(L"shaders.hlsl").c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileFlags, 0, &vertexShader, nullptr));
	ThrowIfFailed(D3DCompileFromFile(YogHelper::get_asset_path(L"shaders.hlsl").c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileFlags, 0, &pixelShader, nullptr));

	const UINT vertex_buffer_size = sizeof(triangleVertices);

	ThrowIfFailed(m_device_->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(vertex_buffer_size),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_vertex_buffer_)));

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
	// Note: using upload heaps to transfer static data like vert buffers is not 
	// recommended. Every time the GPU needs it, the upload heap will be marshalled 
	// over. Please read up on Default Heap usage. An upload heap is used here for 
	// code simplicity and because there are very few verts to actually transfer.



	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
	psoDesc.pRootSignature = m_root_signature_.Get();
	psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
	psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = FALSE;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	ThrowIfFailed(m_device_->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipeline_state)));
	

	// Copy the triangle data to the vertex buffer.
	UINT8* pVertexDataBegin;
	CD3DX12_RANGE readRange(0, 0);        // We do not intend to read from this resource on the CPU.
	ThrowIfFailed(m_vertex_buffer_->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
	memcpy(pVertexDataBegin, triangleVertices, sizeof(triangleVertices));
	m_vertex_buffer_->Unmap(0, nullptr);

	// Initialize the vertex buffer view.
	m_vertex_buffer_view_.BufferLocation = m_vertex_buffer_->GetGPUVirtualAddress();
	m_vertex_buffer_view_.StrideInBytes = sizeof(Vertex);
	m_vertex_buffer_view_.SizeInBytes = vertexBufferSize;
#endif
}

void Environment::InitD3DEnv(HWND hWnd){

#ifdef D3D12
	//创建交换链

	//创建描述符堆
	create_rtv_heaps();
	//

	//RTV创建描述符
	load_info();
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(m_rtv_heap_->GetCPUDescriptorHandleForHeapStart());

	for(UINT i = 0;i<n_frame_back_buffer_count;i++) {
		YogDebugger::ThrowIfFailed(m_swap_chain_->GetBuffer(i, IID_PPV_ARGS(&m_render_target_views_[i])));

		m_device_->CreateRenderTargetView(m_render_target_views_[i].Get(), nullptr, rtv_handle);

		rtv_handle.Offset(1, n_rtv_descriptor_size_);
	}
	
	CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	ComPtr<ID3DBlob> signature;
	ComPtr<ID3DBlob> error;

	YogDebugger::ThrowIfFailed(D3D12SerializeRootSignature(&rootSignatureDesc
		, D3D_ROOT_SIGNATURE_VERSION_1
		, &signature, &error));

	YogDebugger::ThrowIfFailed(m_device_->CreateRootSignature(0
		, signature->GetBufferPointer()
		, signature->GetBufferSize()
		, IID_PPV_ARGS(&m_root_signature_)));
	m_device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_command_allocator_));

	m_device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_command_allocator_.Get(), m_pipeline_state.Get(), IID_PPV_ARGS(&m_command_list_));

	m_device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));

	m_fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
#endif

	YogInitDxgiFactory();
	LogAdapters();
	InitializeD3DEnv(hWnd);
	InitializeShader();
	InitGui(hWnd);
}

void Environment::InitGui(HWND hWnd){
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(this->m_device.Get(), this->m_deviceContext.Get());
	ImGui::StyleColorsLight();
	
}

ComPtr<IDXGISwapChain> Environment::GetSwapChain(){
#ifdef D3D12
	if(this->m_swap_chain_) {
		return this->m_swap_chain_;
	}else {
		YogDebugger::debug_error(L"can't find the swap chain ,maybe it's not initialized");
	}
	return nullptr;
#endif
	return nullptr;
}

ComPtr<ID3D11Device> Environment::GetDirectDevice(){
#ifdef D3D12
	return this->m_device_;
#endif
	return this->m_device;
}

UINT Environment::GetId(){
	return 0;
}

std::string Environment::GetName(){
	return "";
}

void Environment::env_end(){
#ifdef D3D12
	const UINT64 fence = m_fence_value;
	ThrowIfFailed(m_cmd_queue_->Signal(m_fence.Get(), fence));
	m_fence_value++;

	// Wait until the previous frame is finished.
	if (m_fence->GetCompletedValue() < fence)
	{
		ThrowIfFailed(m_fence->SetEventOnCompletion(fence, m_fence_event));
		WaitForSingleObject(m_fence_event, INFINITE);
	}

	m_frame_index = m_swap_chain_->GetCurrentBackBufferIndex();
#endif
}

void Environment::env_start(){
#ifdef D3D12
	m_command_allocator_->Reset();
	m_command_list_->Reset(m_command_allocator_.Get(),m_pipeline_state.Get());
	m_command_list_->SetGraphicsRootSignature(m_root_signature_.Get());


	m_command_list_->RSSetViewports(1, &m_viewport);
	m_command_list_->RSSetScissorRects(1, &m_scissor_rect);


	CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(m_rtv_heap_->GetCPUDescriptorHandleForHeapStart(), m_frame_index, n_rtv_descriptor_size_);

	CD3DX12_RESOURCE_BARRIER barriers[] = {
	CD3DX12_RESOURCE_BARRIER::Transition(
	m_render_target_views_[m_frame_index].Get(), D3D12_RESOURCE_STATE_PRESENT,
	D3D12_RESOURCE_STATE_RENDER_TARGET,0,D3D12_RESOURCE_BARRIER_FLAG_NONE),
	CD3DX12_RESOURCE_BARRIER::Transition(
	m_render_target_views_[m_frame_index].Get(),
	D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT,0,D3D12_RESOURCE_BARRIER_FLAG_NONE)
	};

	const float clearColor[] = { 0.2f, 0.2f, 0.4f, 1.0f };
	m_command_list_->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);
	m_command_list_->ClearRenderTargetView(rtv_handle, clearColor, 0, nullptr);
	m_command_list_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_command_list_->IASetVertexBuffers(0, 1, &m_vertex_buffer_view_);
	m_command_list_->DrawInstanced(3, 1, 0, 0);

	m_command_list_->Close();
	ID3D12CommandList* pp_command_lists[] = { m_command_list_.Get() };
	m_cmd_queue_->ExecuteCommandLists(_countof(pp_command_lists),pp_command_lists);

	m_swap_chain_->Present(1, 0);

#endif
	const float clearColor[] = { 0.2f, 0.2f, 0.4f, 1.0f };
	//this->m_deviceContext->OMSetRenderTargets(1, this->m_renderTargetView.GetAddressOf(), nullptr);
	this->m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
	this->m_deviceContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	this->m_deviceContext->IASetInputLayout(this->m_yogVertexShader->m_inputLayout.Get());
	this->m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_deviceContext->VSSetShader(m_yogVertexShader->m_vertexShader.Get(), nullptr, 0);
	this->m_deviceContext->PSSetShader(m_yogPixelShader->m_pixelShader.Get(), nullptr, 0);
	this->m_deviceContext->RSSetState(m_rasterizerState.Get());
	this->m_deviceContext->PSSetSamplers(0, 1, m_samplerState.GetAddressOf());
	this->m_deviceContext->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	this->m_deviceContext->PSSetShaderResources(0, 1, this->myTexture.GetAddressOf());
	XMMATRIX world = XMMatrixIdentity();
	constantBuffer.data.mat = world * camera.GetViewMatrix()*camera.GetProjectionMatrix();
	constantBuffer.data.mat = XMMatrixTranspose(constantBuffer.data.mat);
	constantBuffer.ApplyChanges(m_deviceContext.Get());
	this->m_deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	DrawTestScene();

	spriteBatch->Begin();
	spriteFont->DrawString(spriteBatch.get(), L"Yog Engine Version 0.1", XMFLOAT2(0, 0), DirectX::Colors::Aqua, 0.0f);
	spriteBatch->End();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Test");
		ImGui::Text("this is example text");
	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	this->m_swapChain->Present(1, NULL);


}
void Environment::ResolveModuleDependency(){
	
}

