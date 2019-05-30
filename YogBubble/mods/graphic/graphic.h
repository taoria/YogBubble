#pragma once
#include "../../stdafx.h"

struct Vertex {
	XMFLOAT3 pos;
	XMFLOAT4 color;
};
struct Dot
{
	XMFLOAT3 pos;
	XMFLOAT2 tex;
	XMFLOAT3 nom;
};
struct Vertex2 {
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 tex0;
	XMFLOAT2 tex1;
};
struct VS_CB_DATA{
	XMMATRIX wvpMatrix;
	XMMATRIX worldMatrix;
};
struct PS_CB_LIGHT{
	XMFLOAT3 color = XMFLOAT3(1,1,1);
	float lightStrength = 1.0f;
	XMFLOAT3 dynamicColor = XMFLOAT3(1, 1, 1);
	XMFLOAT3 dynamicPosition = XMFLOAT3(1, 1, 1);
	float dynamicLightStrength = 1.0f;
};