#include <vector>
#include "../Entity/GameEntity.h"
#include "RendererData.h"
#include "../Entity/Light.h"
using namespace std;
RendererData* RendererData::data =nullptr;
Entity* RendererData::defaultLight = new Light;
RendererData* RendererData::GetInstance(){
	if(data==nullptr){
		data = new RendererData;
	}
	return data;
}

Entity* RendererData::GetDefaultLight(){
	return defaultLight;
}

void RendererData::EraseData(ModelComponent* model){

}
