#include "Vec3.h"


Vec3::Vec3(XMFLOAT3 xmfloat3){
	x = xmfloat3.x;
	y = xmfloat3.y;
	z = xmfloat3.z;
}
Vec3::Vec3(float xx, float yy, float zz):x(xx),y(yy),z(zz){
}

UINT Vec3::GetId() { return 0; }

void Vec3::SetId(UINT id){}

std::string Vec3::GetName() { return "vector"; }

void Vec3::SetName(std::string){}
Vec3& Vec3::operator=(XMFLOAT3 vec){
	this->x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

bool Vec3::operator==(XMFLOAT3 xmfloat3){
	return x == xmfloat3.x && y == xmfloat3.y && z == xmfloat3.z;
}

bool Vec3::operator==(Vec3  float3){
	return x == float3.x && y == float3.y && z == float3.z;
}

Vec3& Vec3::Norm(){
	if(x==0&&y==0&&z==0){
		
	}else{
		const float div = Magnitude();
		return *(new Vec3(x / div, y / div, z / div));
	}
}
float Vec3::Magnitude() const{
	return sqrt((x*x + y * y + z * z));
}


Vec3::Vec3()
{
}


Vec3::~Vec3()
{
}
