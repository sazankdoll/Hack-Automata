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

void Stage::InitTransform(void)
{
	transform_.InitTransform(10.0f, Quaternion::Identity(), Quaternion::Identity(), { 0.0f, 0.0f, 0.0f });
}

void Stage::InitCollider(void)
{
	ColliderModel* colModel = new ColliderModel(ColliderBase::TAG::STAGE, &transform_);
	ownColliders_[static_cast<int>(ColliderBase::TAG::STAGE)].push_back(colModel);

	colModel->SetTriger(true);

	CollisionController::GetInstance().RegisterActor(this);
}

void Stage::InitAnimation(void)
{}

void Stage::InitPost(void)
{}

void Stage::Update(void)
{}

void Stage::Draw(void)
{
	ActorBase::Draw();
}


