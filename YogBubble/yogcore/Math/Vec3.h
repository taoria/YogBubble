#pragma once
#include "../IYog.h"
class Vec3 :public IYog,public XMFLOAT3
{
public:
	Vec3(XMFLOAT3 xmfloat3);
	Vec3(float x, float y=0, float z=0);
	Vec3();
	~Vec3();
	UINT GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	Vec3& operator = (XMFLOAT3);
	bool operator == (XMFLOAT3 xmfloat3);
	bool operator == (Vec3 vec);
	Vec3& operator + (Vec3 vec);
	Vec3& operator - (Vec3 vec);
	Vec3& operator +=(Vec3 vec);
	Vec3& operator -=(Vec3 vec);
	Vec3& operator * (float scale) ;
	Vec3& Norm();
	float Magnitude() const;
};


