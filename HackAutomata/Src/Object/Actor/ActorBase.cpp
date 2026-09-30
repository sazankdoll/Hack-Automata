#include "ActorBase.h"
#include "Component/Component.h"
#include "../../Manager/System/TimeManager.h"

ActorBase::ActorBase(void)
	: timeManager_(TimeManager::GetInstance())
	, transform_(Transform())
	, isActive_(true)
{
}

ActorBase::~ActorBase(void)
{
	Release();
}

void ActorBase::Load(void)
{
	// 派生クラスまたは個別設定で必要な場合オーバーライド
}

void ActorBase::Init(void)
{
	// 保持している全コンポーネントの初期化
	for (auto* component : components_)
	{
		if (component != nullptr)
		{
			component->Init();
		}
	}
}

void ActorBase::Update(void)
{
	if (!isActive_) { return; }

	// 保持している全コンポーネントの更新
	for (auto* component : components_)
	{
		if (component != nullptr && component->GetEnable())
		{
			component->Update();
		}
	}
}

void ActorBase::Draw(void)
{
	if (!isActive_) { return; }

	// 保持している全コンポーネントの描画
	for (auto* component : components_)
	{
		if (component != nullptr && component->GetEnable())
		{
			component->Draw();
		}
	}
}

void ActorBase::Release(void)
{
	// 所有している全コンポーネントの解放と破棄
	for (auto* component : components_)
	{
		if (component != nullptr)
		{
			component->Release();
			delete component;
		}
	}
	components_.clear();
}