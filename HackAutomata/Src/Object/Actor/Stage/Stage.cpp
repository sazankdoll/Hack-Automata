#include "../../../Manager/Generic/ResourceManager.h"
#include "../../../Object/Collision/CollisionController.h"
#include "../../../Utility/UtilityMath.h"
#include "../../Collider/ColliderModel.h"

#include "Stage.h"

Stage::Stage(void)
{}

void Stage::Load(void)
{
	transform_.modelId = ResourceManager::GetInstance().LoadHandleId(ResourceManager::SRC::MODEL_STAGE);
}
void Stage::Update(void)
{}

void Stage::Draw(void)
{
	ActorBase::Draw();
}


