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
	YID GetId() override;
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
	std::string GameName();

	IComponent* GetComponent(std::string name);
	template<typename T>
	T* GetComponent();
	bool transformUpdate = true;
	void AddComponent(IComponent *component);
	template<typename T>
	void AddComponent();
	~Entity();
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
		return nullptr;
	}
	return res;
}

template <typename T>
void Entity::AddComponent(){
	T* res = new T;
	AddComponent(res);
}



