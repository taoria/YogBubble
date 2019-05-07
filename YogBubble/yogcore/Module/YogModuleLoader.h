#pragma once
#include "IModuleLoader.h"

class YogModuleLoader: public IModuleLoader
{
public:

	YogModuleLoader();
	~YogModuleLoader();
	IYogModule* load_mod(std::string loading_info) override;
	void SetId(YID id) override;
	void SetName(std::string) override;
};

