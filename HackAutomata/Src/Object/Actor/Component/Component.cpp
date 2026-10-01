#include "Component.h"

Component::Component(ActorBase* _owner)
	: owner_(_owner)
	, isEnable_(true)
{}