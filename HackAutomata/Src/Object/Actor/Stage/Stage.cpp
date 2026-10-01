#include "Stage.h"
#include "../Component/MeshComponent.h"
#include "../../../Manager/Generic/ResourceManager.h"

Stage::Stage(void)
{}

void Stage::Load(void)
{
	MeshComponent* meshComp = AddComponent<MeshComponent>();

	if (meshComp != nullptr)
	{
		meshComp->LoadModel(ResourceManager::SRC::MODEL_STAGE);
		meshComp->SetIsVisible(true);
	}
}

void Stage::Init(void)
{
	
	transform_.InitTransform(STAGE_SCALE, Quaternion::Identity(), Quaternion::Identity(), { 0.0f, 0.0f, 0.0f });
	ActorBase::Init();
}

void Stage::Update(void)
{
	ActorBase::Update();
}

void Stage::Draw(void)
{
	ActorBase::Draw();
}