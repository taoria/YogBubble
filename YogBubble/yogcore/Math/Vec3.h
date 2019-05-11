#pragma once
#include "../IYog.h"
class YOG_DLL_EXPORT Vec3 :public IYog
{
public:
	float x;
	float y;
	float z;
	Vec3(XMFLOAT3 xmfloat3);
	Vec3(XMVECTOR xv);
	Vec3(float x, float y=0, float z=0);
	Vec3();
	~Vec3();
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	Vec3& operator = (XMFLOAT3);
	Vec3& operator = (XMVECTOR);
	bool operator == (XMFLOAT3 xmfloat3);
	bool operator == (Vec3 vec);
	Vec3& operator + (Vec3 vec);
	Vec3& operator - (Vec3 vec);
	Vec3& operator +=(Vec3 vec);
	Vec3& operator -=(Vec3 vec);
	Vec3& operator * (float scale) ;
	Vec3& Norm();
	operator XMFLOAT3();
	operator XMVECTOR();
	float Magnitude() const;
};


