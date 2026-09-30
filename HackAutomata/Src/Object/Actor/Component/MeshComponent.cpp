#include <DxLib.h>

#include "../ActorBase.h"
#include "MeshComponent.h"


MeshComponent::MeshComponent(ActorBase* _owner)
	: Component(_owner)
	, modelId_(-1)
	, isVisible_(true)
{}

void MeshComponent::LoadModel(ResourceManager::SRC _src)
{
	// リソースマネージャーからモデルハンドルを取得
	modelId_ = ResourceManager::GetInstance().LoadHandleId(_src);
}

void MeshComponent::Init(void)
{}

void MeshComponent::Update(void)
{
	if (owner_ == nullptr || modelId_ == -1) { return; }

	// 所有アクターのTransform（位置・回転・スケール）を取得してモデルに適用する
	const Transform& transform = owner_->GetTransform();

	// 位置の設定
	MV1SetPosition(modelId_, transform.pos);

	// スケールの設定
	MV1SetScale(modelId_, VGet(transform.scl.x, transform.scl.y, transform.scl.z));

	// 回転の設定（Quaternionから行列への変換等、使用している数学ライブラリに合わせて適用）
	// 例: MV1SetRotationZYX(modelId_, transform.rot);
}

void MeshComponent::Draw(void)
{
	// 描画フラグがfalse、またはモデルが未読み込みの場合は描画しない
	if (!isVisible_ || modelId_ == -1) { return; }

	// 3Dモデルの描画
	MV1DrawModel(modelId_);
}

void MeshComponent::Release(void)
{
	// ResourceManager側で一括解放する場合はここでのDeleteModelは不要
}