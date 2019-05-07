#include "../stdafx.h"
#include "yog.h"
#include "Manager/YogManager.h"

yog::yog(){
	yog_init();
}
yog::~yog(){
}

yog::yog(std::string args){
	yog_pillar = new YogPillar;
}

void yog::yog_init(){
	//main thread
	yog_pillar = new YogPillar;
	yog_pillar->PillarRun();
}


