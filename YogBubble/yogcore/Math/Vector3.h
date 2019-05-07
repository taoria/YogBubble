#pragma once
#include "../IYog.h"
class Vec3 :public IYog
{
public:
	float x;
	float y;
	float z;
	Vec3(XMFLOAT3 xmfloat3);
	Vec3(float x, float y, float z);
	Vec3();
	~Vec3();
	UINT GetId() override;
	void SetId(UINT id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	Vec3& operator = (XMFLOAT3);
	bool operator == (XMFLOAT3 xmfloat3);
	bool operator == (Vec3 vec);
	Vec3& Norm();
	float Magnitude() const;
};

