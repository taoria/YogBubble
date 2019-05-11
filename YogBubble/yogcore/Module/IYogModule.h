#pragma once
#include "../IYog.h"
#include "../IYogObject.h"
interface  YOG_DLL_EXPORT IYogModule:public IYogObject{

	virtual void ResolveModuleDependency()=0;
	virtual void OnModuleInit()=0;
	virtual void OnModuleUpdate()=0;
	virtual void OnModuleRelease()=0;
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
	void OnInit() override;
	void OnRelease() override;
	//virtual IYog& operator = (IYog& i_yog);
};

inline YID IYogModule::GetId() {
	return 0;
}

inline void IYogModule::SetId(YID id){

}

inline std::string IYogModule::GetName() {
	return "";
}

inline void IYogModule::SetName(std::string) {
	
}

inline void IYogModule::OnInit() {
}

inline void IYogModule::OnRelease() {
}

