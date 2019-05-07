#include "Vec3.h"
#include "../../tools/helper.h"


Vec3::Vec3(XMFLOAT3 xmfloat3){
	x = xmfloat3.x;
	y = xmfloat3.y;
	z = xmfloat3.z;
}
Vec3::Vec3(float xx, float yy, float zz):XMFLOAT3(xx,yy,zz){
}

UINT Vec3::GetId() { return 0; }

void Vec3::SetId(YID id){}

std::string Vec3::GetName() { return "vector"; }

void Vec3::SetName(std::string){}
Vec3& Vec3::operator=(XMFLOAT3 vec){
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	return *this;
}

bool Vec3::operator==(XMFLOAT3 xmfloat3){
	return x == xmfloat3.x && y == xmfloat3.y && z == xmfloat3.z;
}

bool Vec3::operator==(Vec3  float3){
	return x == float3.x && y == float3.y && z == float3.z;
}

Vec3& Vec3::operator+(Vec3 vec){
	Vec3 *vec3 = new Vec3(*this);
	vec3->x += vec.x;
	vec3->y += vec.y;
	vec3->z += vec.z;
	return *vec3;
}

Vec3& Vec3::operator-(Vec3 vec){
	Vec3 *vec3 = new Vec3(*this);
	vec3->x -= vec.x;
	vec3->y -= vec.y;
	vec3->z -= vec.z;
	return *vec3;
}

Vec3& Vec3::operator+=(Vec3 vec){
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

Vec3& Vec3::operator-=(Vec3 vec){
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

Vec3& Vec3::operator*(float scale){
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

Vec3& Vec3::Norm(){
	if(x==0&&y==0&&z==0){
		LOG_F(YOG_ERROR, "zero vector can't be normalized ");
		return *this;
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
