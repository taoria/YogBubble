#pragma once
#include "../../stdafx.h"
enum IDType
{
	ID_ENTITY,
	ID_COMPONENT
};
class IDAssigner
{
protected:
	static IDAssigner * globalIdAssigner;
	UINT64 currentId;

public:
	static IDAssigner* GetInstance();
	UINT64 AssignId(IDType idType);
};

#define NEW_ENTITY_ID (IDAssigner::GetInstance()->AssignId(ID_ENTITY))
#define NEW_COMPONENT_ID (IDAssigner::GetInstance()->AssignId(ID_COMPONENT))