#pragma once
#include "../IYogObject.h"
#include "../../tools/helper.h"
#include "../Math/Vec3.h"
#include "../Manager/YogManager.h"
//#include "../Component/IComponent.h"

struct IComponent;
class YOG_DLL_EXPORT Entity :public IYogObject{
protected:
	void SetId(YID id) override;
	YID id;
public:
	UINT GetId() override;
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;


	IComponent* GetComponent(std::string name);
	template<typename T>
	T* GetComponent();

	void AddComponent(IComponent *component);
	template<typename T>
	void AddComponent();
	Entity();
	Vec3& GetPosition();
	Vec3& GetRotation();
	Vec3& GetScale();
	bool operator <(const Entity& other);
};
template <typename T>
T* Entity::GetComponent(){
	std::string str = typeid(T).name();

	T* res = reinterpret_cast<T*>(GetComponent(str));
	if(res==nullptr){
		LOG_F(YOG_ERROR, "no such Component %s in Entity %d", str.c_str(), this->GetId());
	}
	return res;
}

template <typename T>
void Entity::AddComponent(){
	std::string str = typeid(T).name();
	T* res = new T;
	AddComponent(res);
}


