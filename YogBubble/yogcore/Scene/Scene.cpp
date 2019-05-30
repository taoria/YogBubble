#include "Scene.h"
#include <fstream>
#include "../Component/ComponentSystem.h"
#include "../Entity/TransformComponent.h"
#include "../Graphic/ModelComponent.h"
#include "../../tools/thirdparty/json/json.h"
#include "../Resource/ModelManager.h"
#include <sstream>
Scene::Scene(){
} 


Scene::~Scene()
{
}
Json::Value VecToJson(Vec3 &v3){
	Json::Value object;
	object.append(v3.x);
	object.append(v3.y);
	object.append(v3.z);
	return object;
}
Json::Value  ToJson(IComponent *t){
	Json::Value object;
	std::string res= t->GetName();
	if(t->GetName()=="TransformComponent"){
		TransformComponent *temp = dynamic_cast<TransformComponent*>(t);
		object["position"] = VecToJson(temp->position);
		object["rotation"] = VecToJson(temp->rotation);
		object["scale"] = VecToJson(temp->scale);
		object["ComponentName"] = "TransformComponent";
	}
	if (t->GetName() == "ModelComponent") {
		ModelComponent *temp = dynamic_cast<ModelComponent*>(t);
		object["address"] = (temp->modelName).c_str();
		object["ComponentName"] = "ModelComponent";
	}
	return object;;
}
IComponent* GetComponentFromJson(Json::Value value){
	if(value.isMember("ComponentName")==false){
		LOG_N_F(YOG_ERROR, "%s", "Error format component");
		return nullptr;
	}
	if(value["ComponentName"]=="TransformComponent" ){
		TransformComponent * transformComponent = new TransformComponent;
		transformComponent->position =Vec3( value["position"][0].asFloat(),value["position"][1].asFloat(),value["position"][2].asFloat() );
		transformComponent->rotation = Vec3(value["rotation"][0].asFloat(), value["rotation"][1].asFloat(), value["rotation"][2].asFloat());
		transformComponent->scale = Vec3(value["scale"][0].asFloat(), value["scale"][1].asFloat(), value["scale"][2].asFloat());
		return transformComponent;
	}
	if (value["ComponentName"] == "ModelComponent") {
		ModelComponent * modelComponent = new ModelComponent;
		ModelManager::GetInstance()->AddReference(modelComponent, value["address"].asString());
		return modelComponent;
	}
	return nullptr;
}
bool Scene::Save(std::string sceneName){
	Json::Reader reader;
	Json::Value sceenRoot;
	ComponentSystem *componentSystem = dynamic_cast<ComponentSystem*>(get_manager("component system"));
	Json::Value entities;
	for(auto entity: gameEntities){
		Json::Value singleEntity;
		auto v = componentSystem->GetComponentList(entity);
		for (auto coms : v) {
			Json::Value value = ToJson(coms);
			singleEntity["components"].append(value);
		}
		entities.append(singleEntity);
	}
	sceenRoot["entities"] = entities;
	Json::FastWriter writer;

	std::string strWrite = writer.write(sceenRoot);
	//LOG_N_F(YOG_DEBUG, "Json is %s", strWrite.c_str());
	std::ofstream ofs;
	ofs.open(sceneName);
	ofs << strWrite;
	ofs.close();
	return true;

}
bool Scene::Load(std::string sceneName){
	Json::Reader reader;
	Json::Value sceenRoot;
	//os.open(scen)
	std::ifstream ifs;
	std::stringstream buffer;
	try {
		ifs.open(sceneName);
		buffer << ifs.rdbuf();
	}catch (...){
		return false;
	}
	ifs.close();
	auto str = buffer.str();
	CleanScene();
	if(reader.parse(str,sceenRoot)){
		Json::Value entityList = sceenRoot["entities"];
		for(auto entity: entityList){
			Entity* gameEntity = new Entity;
			for (auto com : entity["components"]){
				IComponent *component = GetComponentFromJson(com);
				gameEntity->AddComponent(component);
			}
			gameEntities.push_back(gameEntity);
		}
	}
	return false;
}

void Scene::SceneAddEntity(Entity* entity){
	gameEntities.push_back(entity);
}

YID Scene::GetId(){
	return 0;
}

void Scene::SetId(YID id){
}

std::string Scene::GetName(){
	return "Scene";
}

void Scene::SetName(std::string){
}

void Scene::CleanScene(){
	for(Entity* v :gameEntities){
		delete v;
	}
	gameEntities.clear();
}
