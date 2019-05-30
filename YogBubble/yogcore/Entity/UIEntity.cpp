#include "UIEntity.h"
#include "../UI/UIComponent.h"

UIEntity::UIEntity(){
	AddComponent<UIComponent>();
}
