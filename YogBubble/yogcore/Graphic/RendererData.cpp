#include <vector>
#include "../Entity/GameEntity.h"
#include "RendererData.h"
using namespace std;
RendererData* RendererData::data =nullptr;
RendererData* RendererData::GetInstance(){
	if(data==nullptr){
		data = new RendererData;
	}
	return data;
}
