#include "YogPhysics.h"
#include "../../yogcore/physics/Physics.h"
#include "../../yogcore/Entity/TransformComponent.h"
#include "../../yogcore/yog.h"
#include "../../yogcore/Event/EventSystem.h"
#include "../../tools/Data/Data.h"
void YogPhysics::OnModuleInit() {

}
void YogPhysics::CheckCollision(ICollider* a,ICollider *b){
	if(a->GetName()=="BallCollider"&&b->GetName()=="BallCollider"){
		auto ta = a->entity->GetComponent<TransformComponent>();
		auto tb = b->entity->GetComponent<TransformComponent>();
		if(ta&&tb){
			auto ca = ta->position + static_cast<BallCollider*>(a)->position;
			auto cb = tb->position + static_cast<BallCollider*>(b)->position;
			Vec3 res = ca - cb;
			float rad = res.Magnitude();
			if(rad< dynamic_cast<BallCollider*>(a)->radius+ dynamic_cast<BallCollider*>(b)->radius){
				IEvent* arg = new YEvent;
				arg->SetName("on collision");
				arg->push("first", a);
				arg->push("second", b);
				auto eventSystem = dynamic_cast<EventSystem*>(get_manager("event system"));
				eventSystem->EmitInfo(arg);
			}
		}

	}
}
void YogPhysics::OnModuleUpdate(){
	auto begin = Physics::colliders.begin();
	auto end = Physics::colliders.end();
	for (; begin != end;++begin) {
		for(auto next =begin;next!=end;++next){
			if(begin!=next){
				CheckCollision(*begin, *next);
			}
		}
	}
	auto vbegin = Physics::bodies.begin();
	auto vend = Physics::bodies.end();
	for(;vbegin!=vend;++vbegin){
		if ((*vbegin)->entity){
			(*vbegin)->GetEntity()->GetComponent<TransformComponent>()->position += (*vbegin)->velocity*(Data::TimerData::deltaTime/10);
		}
	}
}

void YogPhysics::OnModuleRelease(){

}
