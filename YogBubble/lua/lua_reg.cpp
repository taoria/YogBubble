#include <lua.hpp>
#include "lua_reg.h"
#include <LuaBridge/LuaBridge.h>
#include "../yogcore/Entity/Entity.h"
#include "../yogcore/Entity/TransformComponent.h"
#include "../yogcore/Resource/ModelManager.h"
#include "../yogcore/Graphic/ModelComponent.h"
#include <algorithm>
#include "../tools/Data/Input.h"
#include "../tools/Data/Data.h"
#include "../mods/graphic/GFX.h"
#include "../yogcore/physics/RigidBody.h"
struct LuaModel;

struct LuaEntity:public Entity{
	LuaEntity():Entity(){
		AddComponent<TransformComponent>();
		AddComponent<ModelComponent>();
	}
	virtual void SetModel(std::string modelName, lua_State* L){
		ModelManager* modelManager = ModelManager::GetInstance();
		auto com = this->GetComponent<ModelComponent>();
		modelManager->AddReference(com, modelName);
	}
	virtual int GetPos(lua_State *L){
		auto com = this->GetComponent<TransformComponent>();
		lua_pushnumber(L, com->position.x);
		lua_pushnumber(L, com->position.y);
		lua_pushnumber(L, com->position.z);
		return 3;
		
	}
	virtual void SetPos(float x,float y,float z, lua_State* L){
		auto com = this->GetComponent<TransformComponent>();
		com->position = Vec3(x, y, z);
	}
	virtual void SetScale(float x,float y,float z){
		auto com = this->GetComponent<TransformComponent>();
		com->scale = Vec3(x, y, z);
	}
	virtual void SetRotation(float x, float y, float z) {
		auto com = this->GetComponent<TransformComponent>();
		com->rotation = Vec3(x, y, z);
	}
	virtual void LookAtPos(float x,float y,float z, lua_State* L){
		auto com = this->GetComponent<TransformComponent>();
		com->LookAtPos(Vec3(x, y, z));
	}
	virtual Vec3 GetForward(){
		return this->GetForward();
	}
	virtual void SetVelocity(float x,float y,float z, lua_State* L){
		auto  res = GetComponent<RigidBody>();
		if(res==nullptr){
			AddComponent<RigidBody>();
			res = GetComponent<RigidBody>();
		}
		res->velocity = Vec3(x, y, z);

	}
	virtual void GetVelocity(lua_State* L) {
		auto  com = GetComponent<RigidBody>();
		if (com == nullptr) {
			lua_pushnumber(L,0);
			lua_pushnumber(L, 0);
			lua_pushnumber(L,0);
		}else{
			lua_pushnumber(L, com->velocity.x);
			lua_pushnumber(L, com->velocity.y);
			lua_pushnumber(L, com->velocity.z);
		}

	}
	//virtual void SetModel(LuaModel *luaModel, lua_State*L);
};
struct LuaCamera :public LuaEntity {
	LuaCamera():LuaEntity(){
		AddComponent<CameraComponent>();
	}
	void CameraAttatchedToGraphicCamera(D3DCamera* yogCamera) {
		yogCamera->Initialize(this);

	}
	virtual void SetMainCamera() {
		IYogManager*  i_manager = get_manager("module manager");
		GFX*  gfx = dynamic_cast<GFX*>(i_manager->GetTargetFromName("renderer"));
		CameraAttatchedToGraphicCamera(gfx->GetGfxCamera());
	}

};
struct LuaModel{
	std::string modelName;
	LuaModel(std::string name,std::string model){
		ModelManager* modelManager = ModelManager::GetInstance();
		modelManager->RegisterModel(name, model);
		modelName = name;
	}
	std::string GetModelName() const{
		return modelName;
	}
};
struct LuaInput{
	static  bool LuaKeyCodeDown(std::string key, lua_State* L);
	static  bool LeftButtonDown();
	static   bool RightButtonDown() ;
	static   int MouseDelta() ;
};
struct LuaData {
	static  float DeltaTime();
};
 bool LuaInput::LuaKeyCodeDown(std::string key, lua_State* L){
	if(key.length()!=1){
		std::transform(key.begin(), key.end(), key.begin(), ::tolower);
		if (key=="ctrl"){
			return Input::KeyCodeDown(KeyCode::CTRL);
		}
		//TO DO HERE
		LOG_N_F(YOG_ERROR, "wrong format of a input keycode");
		return false;

	}else{
		char input = key.at(0);
		input = toupper(input);
		KeyCode keyCode(input);
		return Input::KeyCodeDown(keyCode);
	}
}

bool LuaInput::LeftButtonDown()  {
	return Input::MouseLeftPressed;
}

bool LuaInput::RightButtonDown()  {
	return Input::MouseRightPressed;
}

int LuaInput::MouseDelta()  {
	return Input::MouseDelta;
}

float LuaData::DeltaTime(){
	return Data::TimerData::deltaTime;
}

// void LuaEntity::SetModel(LuaModel* luaModel, lua_State* L) {
// 	SetModel(luaModel->modelName, L);
// }

static const luaL_Reg RegisterEntity[] = {
	{"new",LuaCreateNewEntity},
	{"set_pos",LuaSetTransformPos},
	{"get_pos",LuaGetTransformPos},
	{"reg_model",LuaRegisterModel}
};
using namespace luabridge;
int luaopen_entity_libs(lua_State* L){
	luabridge::getGlobalNamespace(L)
		.beginNamespace("Yog")
		.beginClass<LuaEntity>("Entity")
		.addConstructor<void(*)()>()
		.addFunction("set_pos", &LuaEntity::SetPos)
		.addFunction("set_model", &LuaEntity::SetModel)
		.addFunction("set_scale", &LuaEntity::SetScale)
		.addFunction("set_rotation", &LuaEntity::SetRotation)
		.addFunction("look_at_pos", &LuaEntity::LookAtPos)
		.addFunction("get_pos", &LuaEntity::GetPos)
		.addFunction("set_velocity", &LuaEntity::SetVelocity)
		.addFunction("get_velocity", &LuaEntity::GetVelocity)
		.endClass()
		.deriveClass<LuaCamera, LuaEntity>("Camera").addConstructor<void(*)()>().addFunction("set_main", &LuaCamera::SetMainCamera).endClass().endNamespace();
		//addProperty("get_forward", &LuaEntity::GetForward);
	getGlobalNamespace(L).beginNamespace("Yog")
	.beginClass<LuaModel>("Model")
	.addConstructor<void(*)(std::string, std::string)>()
	.addProperty("ref_name", &LuaModel::GetModelName);
	getGlobalNamespace(L).beginNamespace("Yog")
		.beginClass<LuaInput>("Input").addStaticFunction("keyboard", &LuaInput::LuaKeyCodeDown).
		addStaticProperty("left_button", &LuaInput::LeftButtonDown).
		addStaticProperty("right_button", &LuaInput::RightButtonDown).addStaticProperty("mouse_delta", &LuaInput::MouseDelta);
	getGlobalNamespace(L).beginNamespace("Yog").beginClass<LuaInput>("Time").addStaticProperty("delta_time", &LuaData::DeltaTime);

	return 1;
}