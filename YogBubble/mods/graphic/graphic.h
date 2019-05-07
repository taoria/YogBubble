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
};
struct Vertex2 {
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT2 tex0;
	XMFLOAT2 tex1;
};
struct VS_CB_DATA{
	XMMATRIX mat;
};