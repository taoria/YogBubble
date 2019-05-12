#pragma once
#include "../IYog.h"
#include "../Entity/Entity.h"
//����������ģ����Դ��ģ��������Ϣ.
class YOG_DLL_EXPORT ModelResource :public IYog
{

public:
	std::string m_resourceAddress;
	std::vector<Entity*> m_users;
	ModelResource();
	~ModelResource();
	YID GetId() override;
	void SetId(YID id) override;
	std::string GetName() override;
	void SetName(std::string) override;
};

