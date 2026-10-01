#include "Camera.h"
#include "../Utility/UtilityMath.h"

Camera::Camera(void)
	: ActorBase()
	, mode_(MODE::POINT)
	, pointCameraComp_(nullptr)
	, followCameraComp_(nullptr)
{
	// 2種類のカメラコンポーネントを自身にアタッチ
	pointCameraComp_ = AddComponent<PointCameraComponent>();
	followCameraComp_ = AddComponent<FollowCameraComponent>();
}

void Camera::Init(void)
{
	ActorBase::Init();
	mode_ = MODE::POINT;
}

void Camera::Update(void)
{
	ActorBase::Update();
}

void Camera::SetBeforeDraw(void)
{
	// モードに応じて呼び分ける
	switch (mode_)
	{
	case MODE::POINT:
		if (pointCameraComp_ != nullptr)
		{
			pointCameraComp_->SetBeforeDraw();
		}
		break;

	case MODE::FOLLOW:
		if (followCameraComp_ != nullptr)
		{
			followCameraComp_->SetBeforeDraw();
		}
		break;
	}
}

void Camera::SetFollow(const Transform* _follow)
{
	if (followCameraComp_ != nullptr)
	{
		followCameraComp_->SetFollow(_follow);
	}
}

void Camera::SetPointCameraParam(const VECTOR& _pos, const VECTOR& _targetPos)
{
	if (pointCameraComp_ != nullptr)
	{
		pointCameraComp_->SetPosition(_pos);
		pointCameraComp_->SetTargetPos(_targetPos);
	}
}

VECTOR Camera::GetTargetPos(void) const
{
	if (mode_ == MODE::POINT && pointCameraComp_ != nullptr)
	{
		return pointCameraComp_->GetTargetPos();
	}
	if (mode_ == MODE::FOLLOW && followCameraComp_ != nullptr)
	{
		return followCameraComp_->GetTargetPos();
	}
	return UtilityMath::VECTOR_ZERO;
}

VECTOR Camera::GetForward(void) const
{
	return UtilityMath::VNormalize(VSub(GetTargetPos(), transform_.pos));
}