#include "FollowCameraComponent.h"
#include "../Object/Actor/ActorBase.h"
#include "../Object/Common/Transform.h"
#include "../Manager/Generic/KeyConfInputManager.h"
#include "../Utility/UtilityMath.h"
#include <algorithm>

FollowCameraComponent::FollowCameraComponent(ActorBase* _owner)
	: Component(_owner)
	, followTransform_(nullptr)
	, targetPos_(UtilityMath::VECTOR_ZERO)
	, angles_(UtilityMath::VECTOR_ZERO)
	, rotY_(Quaternion::Identity())
{}

void FollowCameraComponent::Init(void)
{
	angles_ = UtilityMath::VECTOR_ZERO;
	targetPos_ = UtilityMath::VECTOR_ZERO;
	rotY_ = Quaternion::Identity();
}

void FollowCameraComponent::Update(void)
{
	if (owner_ == nullptr) { return; }

	// 1. マウス・ゲームパッド入力によるカメラ回転処理
	ProcessRot();

	// 2. 追従対象とカメラの位置・角度の同期
	SyncFollow();
}

void FollowCameraComponent::SetBeforeDraw(void)
{
	if (owner_ == nullptr) { return; }

	// 画面クリップ距離を設定
	SetCameraNearFar(VIEW_NEAR, VIEW_FAR);

	// DXライブラリへカメラの位置・注視点・上方向ベクトルを設定
	SetCameraPositionAndTargetAndUpVec(
		owner_->GetTransform().pos,
		targetPos_,
		owner_->GetTransform().GetUp()
	);
}

void FollowCameraComponent::ProcessRot(void)
{
	auto& inputManager = KeyConfInputManager::GetInstance();

	// --- マウスによる回転操作 ---
	Vector2F mouseMove = inputManager.GetMouseVelocityAndFixCenter();
	if (!UtilityMath::EqualsVZero(mouseMove))
	{
		angles_.x += (mouseMove.y * ROT_POW_MOUSE);
		angles_.y += (mouseMove.x * ROT_POW_MOUSE);
	}

	// --- ゲームパッド（右スティック）による回転操作 ---
	Vector2F rightStick = inputManager.GetRIghtStick();
	if (!UtilityMath::EqualsVZero(rightStick))
	{
		angles_.y += (rightStick.x * ROT_POW_RAD);
		angles_.x += (rightStick.y * ROT_POW_RAD);
	}

	// X軸（上下）の回転角度を制限
	angles_.x = std::clamp(angles_.x, -LIMIT_X_DOWN, LIMIT_X_UP);
}

void FollowCameraComponent::SyncFollow(void)
{
	// Y軸および全体の回転クォータニオンを計算
	rotY_ = Quaternion::AngleAxis(angles_.y, UtilityMath::AXIS_Y);
	Quaternion totalRot = rotY_.Mult(Quaternion::AngleAxis(angles_.x, UtilityMath::AXIS_X));

	Transform& ownerTransform = owner_->GetTransform();
	ownerTransform.quaRot = totalRot;

	// 追従対象の基準位置を取得
	VECTOR basePos = UtilityMath::VECTOR_ZERO;
	if (followTransform_ != nullptr)
	{
		basePos = followTransform_->pos;
	}

	// 注視点を計算（基準位置 + 相対注視点）
	VECTOR targetLocal = totalRot.PosAxis(FOLLOW_TARGET_LOCAL_POS);
	targetPos_ = VAdd(basePos, targetLocal);

	// カメラの位置を計算（基準位置 + 相対カメラ位置）
	VECTOR camLocal = totalRot.PosAxis(FOLLOW_LOCAL_POS);
	ownerTransform.pos = VAdd(basePos, camLocal);
}