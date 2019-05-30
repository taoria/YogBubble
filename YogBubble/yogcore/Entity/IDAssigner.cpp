#include "IDAssigner.h"
IDAssigner*  IDAssigner::globalIdAssigner= nullptr;
IDAssigner* IDAssigner::GetInstance(){
	if(globalIdAssigner==nullptr){
		IDAssigner::globalIdAssigner = new IDAssigner;
	}
	return globalIdAssigner;
}

UINT64 IDAssigner::AssignId(IDType idType){
	switch (idType){
	case ID_ENTITY:{
		return (this->currentId)++;
		break;
	}
	case ID_COMPONENT:{
		return (currentId++) << 32;
		break;
	}
	}
	return 0;
}
