#pragma once
#include "../Common/Transform.h"
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include "Component/Component.h"
#include "../Collider/ColliderBase.h"

class Component;
class TimeManager;

/// @brief コンポーネント指向におけるゲームオブジェクト基底クラス
class ActorBase
{
public:

	/// @brief コンストラクタ
	ActorBase(void);

	/// @brief デストラクタ
	virtual ~ActorBase(void);

	/// @brief リソースの読み込み
	virtual void Load(void);

	/// @brief 初期化処理
	virtual void Init(void);

	/// @brief 更新処理
	virtual void Update(void);

	/// @brief 描画処理
	virtual void Draw(void);

	/// @brief 解放処理
	virtual void Release(void);

	/// @brief コンポーネントの追加
	template <typename T, typename... Args>
	T* AddComponent(Args&&... _args)
	{
		T* newComponent = new T(this, std::forward<Args>(_args)...);
		components_.push_back(newComponent);
		return newComponent;
	}

	/// @brief 特定のコンポーネントを取得する
	template <typename T>
	T* GetComponent(void) const
	{
		for (auto* component : components_)
		{
			T* casted = dynamic_cast<T*>(component);
			if (casted != nullptr)
			{
				return casted;
			}
		}
		return nullptr;
	}

	/// @brief 所有している全てのコライダーコンポーネントを取得する
	/// @return コライダーコンポーネントのポインタリスト
	std::vector<ColliderBase*> GetColliders(void) const
	{
		std::vector<ColliderBase*> colliders;
		for (auto* component : components_)
		{
			auto* collider = dynamic_cast<ColliderBase*>(component);
			if (collider != nullptr)
			{
				colliders.push_back(collider);
			}
		}
		return colliders;
	}

	/// @brief 前フレームで当たった相手コライダーのリストを取得
	/// @return 当たったコライダーのリスト
	const std::vector<const ColliderBase*>& GetHitCollider(void) const { return hitColliders_; }

	/// @brief 当たったコライダーを追加する
	/// @param _collider 衝突した相手のコライダー
	void AddHitCollider(const ColliderBase* _collider) { hitColliders_.push_back(_collider); }

	/// @brief 当たったコライダーの履歴をクリアする
	void ClearHitCollider(void) { hitColliders_.clear(); }

	/// @brief Transform情報の取得(const)
	const Transform& GetTransform(void) const { return transform_; }

	/// @brief Transform情報の取得
	Transform& GetTransform(void) { return transform_; }

	/// @brief 生存状態の取得
	bool GetIsActive(void) const { return isActive_; }

	/// @brief 生存状態の設定
	void SetIsActive(bool _isActive) { isActive_ = _isActive; }

protected:

	TimeManager& timeManager_;		// タイムマネージャーの参照
	Transform transform_;			// 位置・回転・スケール情報
	std::vector<Component*> components_;	// 所有するコンポーネント配列
	std::vector<const ColliderBase*> hitColliders_; // 当たった相手コライダーの履歴
	bool isActive_;					// アクターの有効フラグ
};