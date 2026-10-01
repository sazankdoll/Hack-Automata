#include "PointCameraComponent.h"
#include "../Object/Actor/ActorBase.h"

PointCameraComponent::PointCameraComponent(ActorBase* _owner)
	: Component(_owner)
	, pointPos_(VGet(0.0f, 200.0f, -500.0f))	// デフォルト初期座標
	, targetPos_(UtilityMath::VECTOR_ZERO)		// デフォルト注視点（原点）
{}

void PointCameraComponent::Init(void)
{
	pointPos_ = VGet(0.0f, 200.0f, -500.0f);
	targetPos_ = UtilityMath::VECTOR_ZERO;
}

void PointCameraComponent::Update(void)
{
	if (owner_ == nullptr) { return; }

	// 所有者アクターの位置に定点座標を反映
	owner_->GetTransform().pos = pointPos_;
}

void PointCameraComponent::SetBeforeDraw(void)
{
	if (owner_ == nullptr) { return; }

	// クリップ距離の設定
	SetCameraNearFar(VIEW_NEAR, VIEW_FAR);

	// DXライブラリへカメラの位置・注視点・上方向ベクトルを設定
	SetCameraPositionAndTargetAndUpVec(
		owner_->GetTransform().pos,
		targetPos_,
		owner_->GetTransform().GetUp()
	);
}