#pragma once
#include "../../yogcore/Module/IYogModule.h"
#include "../../yogcore/physics/Collider.h"

class YogPhysics:public IYogModule{

public:
	void ResolveModuleDependency() override;
	void OnModuleInit() override;
	void CheckCollision(ICollider* a, ICollider* b);
	void CheckCollision();
	void OnModuleUpdate() override;
	void OnModuleRelease() override;
};

inline void YogPhysics::ResolveModuleDependency(){
}


